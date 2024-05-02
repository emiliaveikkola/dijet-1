#include <TH2.h>
#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <TLorentzVector.h>

#include <iostream>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <TLegend.h>
#include <TColor.h>
#include <TStopwatch.h>
#include "tdrstyle_mod22.C"

void StrangeTaggerSamples_cs()
{

float ctag1, ctag2;

    // Open the input file and check for errors
    TFile* input_file = TFile::Open("/Users/macbookpro/Downloads/data/W/Muo16_MC.root", "READ");
    if (!input_file || input_file->IsZombie()) {
        std::cerr << "Error opening input file." << std::endl;
        return; // Proper error handling
    }

    // Access the tree from the input file
    TTree* tree;
    input_file->GetObject("tree", tree);
    if (!tree) {
        std::cerr << "Tree not found in the input file." << std::endl;
        input_file->Close();
        return; // Proper error handling
    }
   
    // Set up the branches
    tree->SetBranchAddress("ctag1", &ctag1);
    tree->SetBranchAddress("ctag2", &ctag2);

    // Create output files and trees
    TFile* output_file_cs = new TFile("output_stag_cssample.root", "RECREATE");
    TTree* cs_tree = tree->CloneTree(0); // Clone tree structure without copying events

    Long64_t nentries = tree->GetEntries();
   Long64_t nbytes = 0, nb = 0;
   auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
   std::cout << std::ctime(&now) << std::endl<< flush;  
   cout << "Processing " << nentries << " events" << endl << flush;
   TStopwatch t;
   t.Start();
   const int nlap = 1000;
   const int nlap2 = 80000;

    // Event loop
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {

      if (jentry%nlap==0) {
         cout << "." << flush;
      }
      if (jentry%nlap2==0 && jentry!=0) {
         double time = t.RealTime();
      if (time>0) cout << Form("\n\%1.0f ev/s\n",nlap2/time) << flush;
         t.Reset();
         t.Start();
      }
      
        tree->GetEntry(jentry);

        // Condition to filter events
        if (ctag1 > 0.43 || ctag2 > 0.43) {
                cs_tree->Fill();
        }
    }

    // Write the output tree and close files
    output_file_cs->cd(); // Ensure you are in the correct directory
    cs_tree->Write();
    output_file_cs->Close();

    input_file->Close(); // Close the input file
}
