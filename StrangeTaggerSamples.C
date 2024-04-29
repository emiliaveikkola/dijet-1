#define StrangeTaggerSamples_cxx
#include "StrangeTaggerSamples.h"
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

void StrangeTaggerSamples::Loop()
{
//   In a ROOT session, you can do:
//      root> .L StrangeTagger.C
//      root> StrangeTagger t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   //TDirectory *curdir = gDirectory;
   TFile *fout1 = new TFile("output_stag_csample.root", "RECREATE");
   TFile *fout2 = new TFile("output_stag_udsample.root", "RECREATE");
   TTree *cTree = fChain->CloneTree(0); // Clone the structure of the tree but don't copy the entries yet
   TTree *udTree = fChain->CloneTree(0); // Clone the structure of the tree but don't copy the entries yet


   //curdir->cd();
   Long64_t nentries = fChain->GetEntries();
   Long64_t nbytes = 0, nb = 0;
   auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
   std::cout << std::ctime(&now) << std::endl<< flush;  
   cout << "Processing " << nentries << " events" << endl << flush;
   TStopwatch t;
   t.Start();
   const int nlap = 1000;
   const int nlap2 = 80000;
   //nentries = 100000;




   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      TChain* chain = dynamic_cast<TChain*>(fChain);
      TFile* currentFile = chain->GetFile();

      // if (Cut(ientry) < 0) continue;

      if (jentry%nlap==0) {
         cout << "." << flush;
      }
      if (jentry%nlap2==0 && jentry!=0) {
         double time = t.RealTime();
      if (time>0) cout << Form("\n\%1.0f ev/s\n",nlap2/time) << flush;
         t.Reset();
         t.Start();
      }

    if (ctag1 < 0.2 || ctag2 < 0.2) {
        cTree->Fill();

    }

    //if (ctag1 < 0.8 && ctag2 < 0.8) {
    //    udTree->Fill();
   // }




   }
    fout1->cd(); // Ensure you are in the correct directory
    cTree->Write(); // Write the skimmed tree to file
    fout1->Close();
    //fout2->cd(); // Ensure you are in the correct directory
    //udTree->Write(); // Write the skimmed tree to file
    //fout2->Close();
      exit(0);
   }
