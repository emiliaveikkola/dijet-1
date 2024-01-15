#include <iostream>
#include <TFile.h>
#include <TH1D.h>

void SumWeightedEnergies() {
    // Open a ROOT file containing your histograms
    TFile* file = TFile::Open("output.root", "READ");

    // Check if the file opened successfully
    if (!file) {
        std::cerr << "Error: Could not open the ROOT file." << std::endl;
        return;
    }

    // List of histogram names to sum
    const char* histogramNames[] = {"h_s", "h_s3", "h_s5","h_sall"};
    const int numHistograms = sizeof(histogramNames) / sizeof(histogramNames[0]);

    // Initialize a variable to store the total sum of weighted energies
    Double_t totalSumWeightedEnergies = 0.0;

    // Loop through all histograms
    for (int i = 0; i < numHistograms; ++i) {
        TH1D* energyHistogram = dynamic_cast<TH1D*>(file->Get(histogramNames[i]));

        // Check if the histogram exists in the file
        if (!energyHistogram) {
            std::cerr << "Error: Could not find the histogram '" << histogramNames[i] << "' in the ROOT file." << std::endl;
            continue;
        }

        // Initialize a variable to store the sum of weighted energies for this histogram
        Double_t sumWeightedEnergies = 0.0;

        // Loop over the bins of the histogram
        for (Int_t bin = 0; bin <= energyHistogram->GetNbinsX()+1; ++bin) {
            Double_t binContent = energyHistogram->GetBinContent(bin);
            Double_t binWeight = 1; // Assuming errors represent weights

            // Calculate the weighted energy for this bin and add it to the sum
            sumWeightedEnergies += binContent * binWeight;
        }

        // Add the sum of weighted energies for this histogram to the total
        totalSumWeightedEnergies += sumWeightedEnergies;

        // Print the result for this histogram
        std::cout << "Sum of weighted energies for '" << histogramNames[i] << "': " << sumWeightedEnergies << std::endl;
    }

    // Print the total sum of weighted energies
    std::cout << "Total sum of weighted energies: " << totalSumWeightedEnergies << std::endl;

    // Close the ROOT file
    file->Close();
}
