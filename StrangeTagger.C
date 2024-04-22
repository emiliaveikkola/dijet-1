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
   TH2D *hJetFlavours = new TH2D("hJetFlavours", ";Jet1 Flavour;Jet2 Flavour; N",7,0,7,7,0,7);
   TH1D *hJetPairs = new TH1D("hJetPairs", ";Jet pair;N",7,1,8);

   TH2D *hMassFlavorPairs_gen = new TH2D("hMassFlavorPairs_gen", ";Jet pair;Mass (GeV); N", 7, 1, 8, 200, 0, 200);
   TH2D *hMassFlavorPairs_reco = new TH2D("hMassFlavorPairs_reco", ";Jet pair;Mass (GeV); N", 7, 1, 8, 200, 0, 200);

   TH1D *hAverageMass_loop_gen = new TH1D("hAverageMass_loop_gen", ";Jet pair;Average Mass (GeV)", 7, 1, 8);

   TH1D *h_cs_gen = new TH1D("h_cs_gen", ";Mass;N",200,0,200);
   TH1D *h_ud_gen = new TH1D("h_ud_gen", ";Mass;N",200,0,200);
   TH1D *h_cd_gen = new TH1D("h_cd_gen", ";Mass;N",200,0,200);
   TH1D *h_us_gen = new TH1D("h_us_gen", ";Mass;N",200,0,200);
   TH1D *h_cb_gen = new TH1D("h_cb_gen", ";Mass;N",200,0,200);
   TH1D *h_ub_gen = new TH1D("h_ub_gen", ";Mass;N",200,0,200);
   TH1D *h_x_gen = new TH1D("h_x_gen", ";Mass;N",200,0,200);

   TH1D *h_cs_reco = new TH1D("h_cs_reco", ";Mass;N",200,0,200);
   TH1D *h_ud_reco = new TH1D("h_ud_reco", ";Mass;N",200,0,200);
   TH1D *h_cd_reco = new TH1D("h_cd_reco", ";Mass;N",200,0,200);
   TH1D *h_us_reco = new TH1D("h_us_reco", ";Mass;N",200,0,200);
   TH1D *h_cb_reco = new TH1D("h_cb_reco", ";Mass;N",200,0,200);
   TH1D *h_ub_reco = new TH1D("h_ub_reco", ";Mass;N",200,0,200);
   TH1D *h_x_reco = new TH1D("h_x_reco", ";Mass;N",200,0,200);

   TH1D *hAverageMasses_gen = new TH1D("hAverageMasses_gen", ";Jet pair;Average Mass (GeV)", 7, 1, 8);
   TH1D *hAverageMasses_reco = new TH1D("hAverageMasses_reco", ";Jet pair;Average Mass (GeV)", 7, 1, 8);


   hJetPairs->GetXaxis()->SetBinLabel(1, "cs");
   hJetPairs->GetXaxis()->SetBinLabel(2, "ud");
   hJetPairs->GetXaxis()->SetBinLabel(3, "cd");
   hJetPairs->GetXaxis()->SetBinLabel(4, "us");
   hJetPairs->GetXaxis()->SetBinLabel(5, "cb");
   hJetPairs->GetXaxis()->SetBinLabel(6, "ub");
   hJetPairs->GetXaxis()->SetBinLabel(7, "x");

   /*hMassFlavorPairs->GetXaxis()->SetBinLabel(1, "cs");
   hMassFlavorPairs->GetXaxis()->SetBinLabel(2, "ud");
   hMassFlavorPairs->GetXaxis()->SetBinLabel(3, "cd");
   hMassFlavorPairs->GetXaxis()->SetBinLabel(4, "us");
   hMassFlavorPairs->GetXaxis()->SetBinLabel(5, "cb");
   hMassFlavorPairs->GetXaxis()->SetBinLabel(6, "ub");
   hMassFlavorPairs->GetXaxis()->SetBinLabel(7, "x");
   */

   //TH2D *hJetFlavourTags = new TH2D("hJetFlavourTags", ";Jet1 Flavour;Jet2 Flavour",4,1,4,4,1,4);
   

   TLorentzVector p4genjet1, p4genjet2, p4recojet1, p4recojet2;
  
  
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
            p4genjet1.SetPtEtaPhiM(gen_pt1, gen_eta1,gen_phi1, gen_m1);
            p4genjet2.SetPtEtaPhiM(gen_pt2, gen_eta2,gen_phi2, gen_m2);
            p4recojet1.SetPtEtaPhiM(pt1, eta1, phi1, m1);
            p4recojet2.SetPtEtaPhiM(pt2, eta2, phi2, m2);

            hJetFlavours->Fill(min(abs(flav1),6), min(abs(flav2),6));

            int binIndex = DetermineJetType(flav1, flav2);
            float genmass = (p4genjet1 + p4genjet2).M();
            float recomass = (p4recojet1 + p4recojet2).M();

            hJetPairs->Fill(binIndex);
            hMassFlavorPairs_gen->Fill(binIndex,genmass);
            hMassFlavorPairs_reco->Fill(binIndex,recomass);

            if (genmass > 30) {
               if (binIndex == 1) {h_cs_gen->Fill(genmass);}
               if (binIndex == 2) {h_ud_gen->Fill(genmass);}
               if (binIndex == 3) {h_cd_gen->Fill(genmass);}          
               if (binIndex == 4) {h_us_gen->Fill(genmass);}
               if (binIndex == 5) {h_cb_gen->Fill(genmass);}
               if (binIndex == 6) {h_ub_gen->Fill(genmass);}
               if (binIndex == 7) {h_x_gen->Fill(genmass);}
            }
            if (recomass > 30) {
               if (binIndex == 1) {h_cs_reco->Fill(recomass);}
               if (binIndex == 2) {h_ud_reco->Fill(recomass);}
               if (binIndex == 3) {h_cd_reco->Fill(recomass);}          
               if (binIndex == 4) {h_us_reco->Fill(recomass);}
               if (binIndex == 5) {h_cb_reco->Fill(recomass);}
               if (binIndex == 6) {h_ub_reco->Fill(recomass);}
               if (binIndex == 7) {h_x_reco->Fill(recomass);}
            }
         }
      }
      // Calculate the mean for each histogram and set it in the average masses histogram
      hAverageMasses_gen->SetBinContent(1, h_cs_gen->GetMean());
      hAverageMasses_gen->SetBinContent(2, h_ud_gen->GetMean());
      hAverageMasses_gen->SetBinContent(3, h_cd_gen->GetMean());
      hAverageMasses_gen->SetBinContent(4, h_us_gen->GetMean());
      hAverageMasses_gen->SetBinContent(5, h_cb_gen->GetMean());
      hAverageMasses_gen->SetBinContent(6, h_ub_gen->GetMean());
      hAverageMasses_gen->SetBinContent(7, h_x_gen->GetMean());

      hAverageMasses_gen->SetBinError(1, h_cs_gen->GetMeanError());
      hAverageMasses_gen->SetBinError(2, h_ud_gen->GetMeanError());
      hAverageMasses_gen->SetBinError(3, h_cd_gen->GetMeanError());
      hAverageMasses_gen->SetBinError(4, h_us_gen->GetMeanError());
      hAverageMasses_gen->SetBinError(5, h_cb_gen->GetMeanError());
      hAverageMasses_gen->SetBinError(6, h_ub_gen->GetMeanError());
      hAverageMasses_gen->SetBinError(7, h_x_gen->GetMeanError());

      hAverageMasses_reco->SetBinContent(1, h_cs_reco->GetMean());
      hAverageMasses_reco->SetBinContent(2, h_ud_reco->GetMean());
      hAverageMasses_reco->SetBinContent(3, h_cd_reco->GetMean());
      hAverageMasses_reco->SetBinContent(4, h_us_reco->GetMean());
      hAverageMasses_reco->SetBinContent(5, h_cb_reco->GetMean());
      hAverageMasses_reco->SetBinContent(6, h_ub_reco->GetMean());
      hAverageMasses_reco->SetBinContent(7, h_x_reco->GetMean());

      hAverageMasses_reco->SetBinError(1, h_cs_reco->GetMeanError());
      hAverageMasses_reco->SetBinError(2, h_ud_reco->GetMeanError());
      hAverageMasses_reco->SetBinError(3, h_cd_reco->GetMeanError());
      hAverageMasses_reco->SetBinError(4, h_us_reco->GetMeanError());
      hAverageMasses_reco->SetBinError(5, h_cb_reco->GetMeanError());
      hAverageMasses_reco->SetBinError(6, h_ub_reco->GetMeanError());
      hAverageMasses_reco->SetBinError(7, h_x_reco->GetMeanError());

      for (int i = 1; i <= 7; i++) {
         TH1D *hProj = hMassFlavorPairs_gen->ProjectionY("_py", i, i);
         double meanMass = hProj->GetMean();
         hAverageMass_loop_gen->SetBinContent(i, meanMass);
         delete hProj;  // Clean up to prevent memory leaks
      }
      fout->Write();
      fout->Close();
      exit(0);
   }
