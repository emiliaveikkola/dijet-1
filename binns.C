#include <TH1.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>

void binns() {
    // Open the ROOT file containing the histograms
    TFile *file = new TFile("output.root", "READ");
    // Retrieve the histogram
    TH1D *hist = (TH1D*)file->Get("h");

    // Calculate the total number of events in the histogram
    double totalEvents = hist->GetSumOfWeights();


    double binSum = 0;
    double binCenter = 0;

    // Loop through the histogram bins
    for (int bin = 1; bin <= hist->GetNbinsX(); ++bin) {
        // Add the current bin's content to the cumulative sum
        binSum += hist->GetBinContent(bin);

        // Check if the cumulative sum exceeds one-third of the total events
        if (binSum >  9* totalEvents / 10) {
            // Get the center of the current bin
            binCenter = hist->GetBinCenter(bin);
            // Break the loop as we found the required bin
            break;
        }
    }

    // Use binCenter for further analysis
    // For example, print it to the console
    std::cout << "The bin center: " << binCenter << std::endl;

    // Close the file
    file->Close();
}