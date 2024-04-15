#include "TH2F.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "iostream"

void analyzeJetFlavors() {
    // Open the ROOT file and get the TTree
    TFile *file = TFile::Open("MUO16_MC.root");
    TTree *tree = (TTree*)file->Get("tree");

    // Define the jet flavors as strings for labeling the histogram bins
    const char* flavors[] = {"b", "c", "u", "d", "s", "g"};
    int nFlavors = sizeof(flavors)/sizeof(flavors[0]);

    // Create a 2D histogram
    TH2F *hJetFlavors = new TH2F("hJetFlavors", "Jet Flavor Correlations;Jet1 Flavor;Jet2 Flavor",
                                 nFlavors, 0, nFlavors, nFlavors, 0, nFlavors);

    // Set the bin labels
    for (int i = 1; i <= nFlavors; i++) {
        hJetFlavors->GetXaxis()->SetBinLabel(i, flavors[i-1]);
        hJetFlavors->GetYaxis()->SetBinLabel(i, flavors[i-1]);
    }

    // Variables to hold jet properties from the tree
    int flav1;
    int flav2;

    // Assuming similar naming for the second jet's branches
    tree->SetBranchAddress("flav1", &flav1);
    tree->SetBranchAddress("flav2", &flav2);

    // Loop over all entries in the TTree
    Long64_t nEntries = tree->GetEntries();
    for (Long64_t i = 0; i < nEntries; i++) {
        tree->GetEntry(i);

        // Fill the histogram
        // Assume jet flavors are stored as integers corresponding to their array index
        hJetFlavors->Fill(flav1, flav2);
    }

    // Write the histogram to a file
    TFile *outputFile = new TFile("output.root", "RECREATE");
    hJetFlavors->Write();
    outputFile->Close();

    // Close the input file
    file->Close();
}