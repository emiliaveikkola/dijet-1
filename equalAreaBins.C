#include <TH1.h>
#include <TFile.h>
#include <iostream>
#include <vector>

void equalAreaBins() {
    TFile *file = new TFile("output.root", "READ");
    TH1D *hist = (TH1D*)file->Get("h");

    double totalEvents = hist->GetSumOfWeights();
    std::vector<double> binEdges;
    double binSum = 0;

    for (int bin = 1; bin <= hist->GetNbinsX(); ++bin) {
        binSum += hist->GetBinContent(bin);
        // Check if the cumulative sum exceeds each fraction of the total events
        if (binSum >= totalEvents / 50 * binEdges.size()) {
            binEdges.push_back(hist->GetBinLowEdge(bin));
        }
    }

    // Ensure the last bin edge is included
    if (binEdges.back() != hist->GetXaxis()->GetXmax()) {
        binEdges.push_back(hist->GetXaxis()->GetXmax());
    }

    // Print the calculated bin edges
    std::cout << "Calculated bin edges for equal-area bins:" << std::endl;
    for (size_t i = 0; i < binEdges.size(); ++i) {
        std::cout << binEdges[i] << std::endl;
    }

    file->Close();
}