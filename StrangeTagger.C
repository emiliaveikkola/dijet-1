#define StrangeTagger_cxx
#include "StrangeTagger.h"
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

   // Assuming udstag, ctag, btag, and gtag are member variables of StrangeTagger
   int DetermineJetType(int x, int y) {
    if (x == 3 && y == -4 || x == -3 && y == 4 ||
    x == 4 && y == -3 || x == -4 && y == 3) return 1;

    if (x == 1 && y == -2 || x == -1 && y == 2 ||
    x == 2 && y == -1 || x == -2 && y == 1) return 2;

    if (x == 1 && y == -4 || x == -1 && y == 4 ||
    x == 4 && y == -1 || x == -4 && y == 1) return 3;

    if (x == 3 && y == -2 || x == -3 && y == 2 ||
    x == 2 && y == -3 || x == -2 && y == 3) return 4;

   if (x == 5 && y == -4 || x == -5 && y == 4 ||
    x == 4 && y == -5 || x == -4 && y == 5) return 5;

   if (x == 2 && y == -5 || x == -2 && y == 5 ||
    x == 5 && y == -2 || x == -5 && y == 2) return 6;
   
   return 7;
       }

void StrangeTagger::Loop()
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

   TDirectory *curdir = gDirectory;
   TFile *fout = new TFile("output_stag.root","recreate");

   // Create a 2D histogram
   TH2D *hJetFlavours = new TH2D("hJetFlavours", ";Jet1 Flavour;Jet2 Flavour",7,0,7,7,0,7);
   TH1D *hJetPairs = new TH1D("hJetPairs", ";Jet pairs;N",7,1,8);

   hJetPairs->GetXaxis()->SetBinLabel(1, "cs");
   hJetPairs->GetXaxis()->SetBinLabel(2, "ud");
   hJetPairs->GetXaxis()->SetBinLabel(3, "cd");
   hJetPairs->GetXaxis()->SetBinLabel(4, "us");
   hJetPairs->GetXaxis()->SetBinLabel(5, "cb");
   hJetPairs->GetXaxis()->SetBinLabel(6, "ub");
   hJetPairs->GetXaxis()->SetBinLabel(7, "x");

   //TH2D *hJetFlavourTags = new TH2D("hJetFlavourTags", ";Jet1 Flavour;Jet2 Flavour",4,1,4,4,1,4);
   

   TLorentzVector p4jet1, p4jet2;
  
  
   curdir->cd();
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

         if (fitProb > 0.2){
            p4jet1.SetPtEtaPhiM(gen_pt1, gen_eta1,gen_phi1, gen_m1);
            p4jet2.SetPtEtaPhiM(gen_pt2, gen_eta2,gen_phi2, gen_m2);

            hJetFlavours->Fill(min(abs(flav1),6), min(abs(flav2),6));

            //tagging
            // Use the function to determine jet types
            //int jetType1 = DetermineJetType(flav1);
            //int jetType2 = DetermineJetType(flav2);

            //cout << "jetti1: "<< jetType1 <<", jetti2: "<< jetType2 << endl << flush;

            // Fill the histogram
            //if (jetType1 != 0 && jetType2 != 0) { // Ensure both jets have a determined type
             hJetPairs->Fill(DetermineJetType(flav1,flav2));
            //}  

            //if (jetType1 == 4 && jetType2 == 4) {
    //std::cout << "G-G event: " << jentry << std::endl;
    //hJetFlavourTags->Fill(jetType1, jetType2);
    
    // Immediately after filling, check the content again
    //std::cout << "Immediate bin content: " 
       //       << hJetFlavourTags->GetBinContent(4, 4) << std::endl;
//}
         }
      }
      //std::cout << "Contents of G-G bin: " 
         //<< hJetFlavourTags->GetBinContent(4, 4) << std::endl;
      fout->Write();
      fout->Close();
      exit(0);
   }
