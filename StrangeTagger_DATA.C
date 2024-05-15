#define StrangeTagger_DATA_cxx
#include "StrangeTagger_DATA.h"
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


int DetermineJetType(double x, double y) {
    if (x > 0.43 || y > 0.43) return 1;
    if (x < 0.06 && y < 0.06) return 2;
    return 3;
}



void StrangeTagger_DATA::Loop()
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
   TFile *fout = new TFile("output_stag_DATA.root","recreate");

   // Create a 2D histogram
   TH2D *hJetFlavours = new TH2D("hJetFlavours", ";Jet1 Flavour;Jet2 Flavour; N",3,1,4,3,1,4);
   TH1D *hJetPairs_DATA = new TH1D("hJetPairs_DATA", ";Jet pair;N",3,1,4);

   TH2D *hMassFlavorPairs_reco = new TH2D("hMassFlavorPairs_reco", ";Jet pair;Mass (GeV); N", 3, 1, 4, 200, 0, 200);

   TH1D *h_cs_reco = new TH1D("h_cs_reco", ";Mass;N",200,0,200);
   TH1D *h_ud_reco = new TH1D("h_ud_reco", ";Mass;N",200,0,200);
   TH1D *h_x_reco = new TH1D("h_x_reco", ";Mass;N",200,0,200);

   TH1D *hAverageMasses_reco = new TH1D("hAverageMasses_reco", ";Jet pair;Average Mass (GeV)", 3, 1, 4);

   TH1D *h_cs = new TH1D("h_cs", "; All in X;N", 1,1,2);
   TH1D *h_ud = new TH1D("h_ud", "; All in X;N", 1,2,3);
   TH1D *h_x = new TH1D("h_x", "; All in X;N", 1,3,4);

 

   hJetPairs_DATA->GetXaxis()->SetBinLabel(1, "cs");
   hJetPairs_DATA->GetXaxis()->SetBinLabel(2, "ud");
   hJetPairs_DATA->GetXaxis()->SetBinLabel(3, "x");

   TLorentzVector p4recojet1, p4recojet2;
  
  
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

         int binIndex = DetermineJetType(ctag1, ctag2);
   
         p4recojet1.SetPtEtaPhiM(pt1, eta1, phi1, m1);
         p4recojet2.SetPtEtaPhiM(pt2, eta2, phi2, m2);

         double recomass = (p4recojet1 + p4recojet2).M();

         // scaling for reco jets


         if (fitProb > 0.2){
            if (binIndex == 1){
               h_cs->Fill(1);
            }
            if (binIndex == 2){
                  h_ud->Fill(2);
            }
            if (binIndex == 3){
               h_x->Fill(3);
            }
         }
/////// FITPROB > 0.2 ///////////
         if (fitProb > 0.2){
            if (recomass > 30) {
               hJetFlavours->Fill(binIndex, binIndex);
               //hJetPairs_DATA->Fill(binIndex);
            }

            if (recomass > 30) {
               hMassFlavorPairs_reco->Fill(binIndex,recomass);
               if (binIndex == 1) {h_cs_reco->Fill(recomass,weight);}
               if (binIndex == 2) {h_ud_reco->Fill(recomass,weight);}
               if (binIndex == 3) {h_x_reco->Fill(recomass,weight);}          
            }
         } //fitProb > 0.2
      } // jentry

      hJetPairs_DATA->SetBinContent(1, h_cs->GetEntries());
      hJetPairs_DATA->SetBinContent(2, h_ud->GetEntries());
      hJetPairs_DATA->SetBinContent(3, h_x->GetEntries());

      // Calculate the mean for each histogram and set it in the average masses histogram

      hAverageMasses_reco->SetBinContent(1, h_cs_reco->GetMean());
      hAverageMasses_reco->SetBinContent(2, h_ud_reco->GetMean());
      hAverageMasses_reco->SetBinContent(3, h_x_reco->GetMean());

      hAverageMasses_reco->SetBinError(1, h_cs_reco->GetMeanError());
      hAverageMasses_reco->SetBinError(2, h_ud_reco->GetMeanError());
      hAverageMasses_reco->SetBinError(3, h_x_reco->GetMeanError());

      fout->Write();
      fout->Close();
      exit(0);
   }
