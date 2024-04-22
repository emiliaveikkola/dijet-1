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

   TH1D *hJetPairs_scaled = new TH1D("hJetPairs_scaled", ";Jet pair;N",7,1,8);


   TH2D *hMassFlavorPairs_gen = new TH2D("hMassFlavorPairs_gen", ";Jet pair;Mass (GeV); N", 7, 1, 8, 200, 0, 200);
   TH2D *hMassFlavorPairs_reco = new TH2D("hMassFlavorPairs_reco", ";Jet pair;Mass (GeV); N", 7, 1, 8, 200, 0, 200);

   //without fitProb
   TH2D *hMassFlavorPairs_gen_wfp = new TH2D("hMassFlavorPairs_gen_wfp", ";Jet pair;Mass (GeV); N", 7, 1, 8, 200, 0, 200);
   TH2D *hMassFlavorPairs_reco_wfp = new TH2D("hMassFlavorPairs_reco_wfp", ";Jet pair;Mass (GeV); N", 7, 1, 8, 200, 0, 200);

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

   TH1D *h_cs_reco_scaled = new TH1D("h_cs_reco_scaled", ";Mass;N",200,0,200);
   TH1D *h_ud_reco_scaled = new TH1D("h_ud_reco_scaled", ";Mass;N",200,0,200);
   TH1D *h_cd_reco_scaled = new TH1D("h_cd_reco_scaled", ";Mass;N",200,0,200);
   TH1D *h_us_reco_scaled = new TH1D("h_us_reco_scaled", ";Mass;N",200,0,200);
   TH1D *h_cb_reco_scaled = new TH1D("h_cb_reco_scaled", ";Mass;N",200,0,200);
   TH1D *h_ub_reco_scaled = new TH1D("h_ub_reco_scaled", ";Mass;N",200,0,200);
   TH1D *h_x_reco_scaled = new TH1D("h_x_reco_scaled", ";Mass;N",200,0,200);

   TH1D *h_cs_gen_wfp = new TH1D("h_cs_gen_wfp", ";Mass;N",200,0,200);
   TH1D *h_ud_gen_wfp = new TH1D("h_ud_gen_wfp", ";Mass;N",200,0,200);
   TH1D *h_cd_gen_wfp = new TH1D("h_cd_gen_wfp", ";Mass;N",200,0,200);
   TH1D *h_us_gen_wfp = new TH1D("h_us_gen_wfp", ";Mass;N",200,0,200);
   TH1D *h_cb_gen_wfp = new TH1D("h_cb_gen_wfp", ";Mass;N",200,0,200);
   TH1D *h_ub_gen_wfp = new TH1D("h_ub_gen_wfp", ";Mass;N",200,0,200);
   TH1D *h_x_gen_wfp = new TH1D("h_x_gen_wfp", ";Mass;N",200,0,200);

   TH1D *h_cs_reco_wfp = new TH1D("h_cs_reco_wfp", ";Mass;N",200,0,200);
   TH1D *h_ud_reco_wfp = new TH1D("h_ud_reco_wfp", ";Mass;N",200,0,200);
   TH1D *h_cd_reco_wfp = new TH1D("h_cd_reco_wfp", ";Mass;N",200,0,200);
   TH1D *h_us_reco_wfp = new TH1D("h_us_reco_wfp", ";Mass;N",200,0,200);
   TH1D *h_cb_reco_wfp = new TH1D("h_cb_reco_wfp", ";Mass;N",200,0,200);
   TH1D *h_ub_reco_wfp = new TH1D("h_ub_reco_wfp", ";Mass;N",200,0,200);
   TH1D *h_x_reco_wfp = new TH1D("h_x_reco_wfp", ";Mass;N",200,0,200);

   TH1D *h_cs_reco_wfp_scaled = new TH1D("h_cs_reco_wfp_scaled", ";Mass;N",200,0,200);
   TH1D *h_ud_reco_wfp_scaled = new TH1D("h_ud_reco_wfp_scaled", ";Mass;N",200,0,200);
   TH1D *h_cd_reco_wfp_scaled = new TH1D("h_cd_reco_wfp_scaled", ";Mass;N",200,0,200);
   TH1D *h_us_reco_wfp_scaled = new TH1D("h_us_reco_wfp_scaled", ";Mass;N",200,0,200);
   TH1D *h_cb_reco_wfp_scaled = new TH1D("h_cb_reco_wfp_scaled", ";Mass;N",200,0,200);
   TH1D *h_ub_reco_wfp_scaled = new TH1D("h_ub_reco_wfp_scaled", ";Mass;N",200,0,200);
   TH1D *h_x_reco_wfp_scaled = new TH1D("h_x_reco_wfp_scaled", ";Mass;N",200,0,200);

   TH1D *hAverageMasses_gen = new TH1D("hAverageMasses_gen", ";Jet pair;Average Mass (GeV)", 7, 1, 8);
   TH1D *hAverageMasses_reco = new TH1D("hAverageMasses_reco", ";Jet pair;Average Mass (GeV)", 7, 1, 8);

   TH1D *hAverageMasses_reco_scaled = new TH1D("hAverageMasses_reco_scaled", ";Jet pair;Average Mass (GeV)", 7, 1, 8);

   TH1D *hAverageMasses_reco_wfp_scaled = new TH1D("hAverageMasses_reco_wfp_scaled", ";Jet pair;Average Mass (GeV)", 7, 1, 8);

   TH1D *hAverageMasses_gen_wfp = new TH1D("hAverageMasses_gen_wfp", ";Jet pair;Average Mass (GeV)", 7, 1, 8);
   TH1D *hAverageMasses_reco_wfp = new TH1D("hAverageMasses_reco_wfp", ";Jet pair;Average Mass (GeV)", 7, 1, 8);



   TH1D *h_c_s = new TH1D("h_c_s", ";p_{T,gen cs};N",500,0,500);
   TH1D *h_s_c = new TH1D("h_s_c", ";p_{T,gen sc};N",500,0,500);
   TH1D *h_c_x = new TH1D("h_c_x", ";p_{T,gen cx};N",500,0,500);
   TH1D *h_x_c = new TH1D("h_x_c", ";p_{T,gen xc};N",500,0,500);

   TH1D *h_s_x = new TH1D("h_s_x", ";p_{T,gen sx};N",500,0,500);
   TH1D *h_x_s = new TH1D("h_x_s", ";p_{T,gen xs};N",500,0,500);

   TProfile *h_cs_resp = new TProfile("h_cs_resp", ";p_{T,gen} (GeV);"
			                       "p_{T,reco}/p_{T,gen}",100,0,400);

 

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
   

   TLorentzVector p4genjet1, p4genjet2, p4recojet1, p4recojet2, p4recojet_scaled1, p4recojet_scaled2, p4recowfpjet_scaled1, p4recowfpjet_scaled2;
  
  
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

         int binIndex = DetermineJetType(flav1, flav2);

         p4genjet1.SetPtEtaPhiM(gen_pt1, gen_eta1, gen_phi1, gen_m1);
         p4genjet2.SetPtEtaPhiM(gen_pt2, gen_eta2, gen_phi2, gen_m2);
         p4recojet1.SetPtEtaPhiM(pt1, eta1, phi1, m1);
         p4recojet2.SetPtEtaPhiM(pt2, eta2, phi2, m2);

         double genmass = (p4genjet1 + p4genjet2).M();
         double recomass = (p4recojet1 + p4recojet2).M();

         // scaling for reco jets
         
         double scaled_reco_pt1 = pt1 * 0.98609735;
         double scaled_reco_pt2 = pt2 * 0.98609735;
         double scaled_gen_pt1 = pt1 * 0.99880491;
         double scaled_gen_pt2 = pt2 * 0.99880491;

         p4recojet_scaled1.SetPtEtaPhiM(scaled_reco_pt1, eta1, phi1, m1);
         p4recojet_scaled2.SetPtEtaPhiM(scaled_reco_pt2, eta2, phi2, m2);

         double recomass_scaled = (p4recojet_scaled1 + p4recojet_scaled2).M();

         if (fitProb > 0.2){
            if (recomass > 30 && genmass > 30) {
               hJetFlavours->Fill(min(abs(flav1),6), min(abs(flav2),6));
               hJetPairs->Fill(binIndex);
            }

            if (genmass > 30) {
               hMassFlavorPairs_gen->Fill(binIndex,genmass);
               if (binIndex == 1) {h_cs_gen->Fill(genmass);}
               if (binIndex == 2) {h_ud_gen->Fill(genmass);}
               if (binIndex == 3) {h_cd_gen->Fill(genmass);}          
               if (binIndex == 4) {h_us_gen->Fill(genmass);}
               if (binIndex == 5) {h_cb_gen->Fill(genmass);}
               if (binIndex == 6) {h_ub_gen->Fill(genmass);}
               if (binIndex == 7) {h_x_gen->Fill(genmass);}
            }

            if (recomass > 30) {
               hMassFlavorPairs_reco->Fill(binIndex,recomass);
               if (binIndex == 1) {h_cs_reco->Fill(recomass);}
               if (binIndex == 2) {h_ud_reco->Fill(recomass);}
               if (binIndex == 3) {h_cd_reco->Fill(recomass);}          
               if (binIndex == 4) {h_us_reco->Fill(recomass);}
               if (binIndex == 5) {h_cb_reco->Fill(recomass);}
               if (binIndex == 6) {h_ub_reco->Fill(recomass);}
               if (binIndex == 7) {h_x_reco->Fill(recomass);}
            }

            if (scaled_reco_pt1 >= 30 && scaled_reco_pt2 >= 30 && scaled_gen_pt1 >= 30 && scaled_gen_pt2 >= 30 ){
               if (binIndex == 2) {
                  hJetPairs_scaled->Fill(binIndex);
               }
            }
            
            if (recomass > 30 && genmass > 30) {
               if (binIndex != 2) hJetPairs_scaled->Fill(binIndex);
            }


            
            if (recomass > 30) {
               if (binIndex == 1) {h_cs_reco_scaled->Fill(recomass);}
               if ((flav1 == 1 || flav2 == 1) || (flav1 == 2 || flav2 == 2)){
                  if (binIndex == 3) {h_cd_reco_scaled->Fill(recomass);}          
                  if (binIndex == 4) {h_us_reco_scaled->Fill(recomass);}
                  if (binIndex == 5) {h_cb_reco_scaled->Fill(recomass);}
                  if (binIndex == 6) {h_ub_reco_scaled->Fill(recomass);}
                  if (binIndex == 7) {h_x_reco_scaled->Fill(recomass);}
               } // ud jets
            } //recomass > 30

            if (scaled_reco_pt1 >= 30 && scaled_reco_pt2 >= 30 ){
               if (binIndex == 2) {h_ud_reco_scaled->Fill(recomass_scaled);}
               if ((flav1 != 1 && flav2 != 1) && (flav1 != 2 && flav2 != 2)){
                  if (binIndex == 3) {h_cd_reco_scaled->Fill(recomass_scaled);}          
                  if (binIndex == 4) {h_us_reco_scaled->Fill(recomass_scaled);}
                  if (binIndex == 5) {h_cb_reco_scaled->Fill(recomass_scaled);}
                  if (binIndex == 6) {h_ub_reco_scaled->Fill(recomass_scaled);}
                  if (binIndex == 7) {h_x_reco_scaled->Fill(recomass_scaled);}
               } // not ud jets
            }  // reco scaled pt >= 30




            // one is charm tagged
            double res = (p4recojet1 + p4recojet2).Pt() / (p4genjet1 + p4genjet2).Pt();
            double gen_pt = (p4genjet1 + p4genjet2).Pt();
            double reco_pt = (p4recojet1 + p4recojet2).Pt();
            if (flav1 == 4 || flav2 == 4){
               if (flav1 == 3 && flav2 == 4) h_s_c->Fill(gen_pt);
               if (flav1 == 4 && flav2 == 3) h_c_s->Fill(gen_pt);
               if (flav1 == 4 && flav2 != 3) h_c_x->Fill(gen_pt);
               if (flav1 != 3 && flav2 == 4) h_x_c->Fill(gen_pt);
            }
            // neither is charm tagged
            if (flav1 != 4 && flav2 != 4){
               if (flav1 == 3) h_s_x->Fill(gen_pt);
               if (flav2 == 3) h_x_s->Fill(gen_pt);
            }
            //charm and strange response
            if (binIndex == 1) h_cs_resp->Fill(gen_pt, res, weight);
         } //fitProb > 0.2


         // without fitProb

         // scaling for reco jets
         
         double scaled_recowfp_pt1 = pt1 * 0.97316344;
         double scaled_recowfp_pt2 = pt2 * 0.97316344;

         p4recowfpjet_scaled1.SetPtEtaPhiM(scaled_recowfp_pt1, eta1, phi1, m1);
         p4recowfpjet_scaled2.SetPtEtaPhiM(scaled_recowfp_pt2, eta2, phi2, m2);

         double recowfpmass_scaled = (p4recowfpjet_scaled1 + p4recowfpjet_scaled2).M();
                     
         hMassFlavorPairs_gen_wfp->Fill(binIndex,genmass);
         hMassFlavorPairs_reco_wfp->Fill(binIndex,recomass);

         if (genmass > 30) {
            if (binIndex == 1) {h_cs_gen_wfp->Fill(genmass);}
            if (binIndex == 2) {h_ud_gen_wfp->Fill(genmass);}
            if (binIndex == 3) {h_cd_gen_wfp->Fill(genmass);}          
            if (binIndex == 4) {h_us_gen_wfp->Fill(genmass);}
            if (binIndex == 5) {h_cb_gen_wfp->Fill(genmass);}
            if (binIndex == 6) {h_ub_gen_wfp->Fill(genmass);}
            if (binIndex == 7) {h_x_gen_wfp->Fill(genmass);}
         }
         if (recomass > 30) {
            if (binIndex == 1) {h_cs_reco_wfp->Fill(recomass);}
            if (binIndex == 2) {h_ud_reco_wfp->Fill(recomass);}
            if (binIndex == 3) {h_cd_reco_wfp->Fill(recomass);}          
            if (binIndex == 4) {h_us_reco_wfp->Fill(recomass);}
            if (binIndex == 5) {h_cb_reco_wfp->Fill(recomass);}
            if (binIndex == 6) {h_ub_reco_wfp->Fill(recomass);}
            if (binIndex == 7) {h_x_reco_wfp->Fill(recomass);}
         }

         if (recomass > 30) {
            if (binIndex == 1) {h_cs_reco_wfp_scaled->Fill(recomass);}
            if ((flav1 == 1 || flav2 == 1) || (flav1 == 2 || flav2 == 2)){
               if (binIndex == 3) {h_cd_reco_wfp_scaled->Fill(recomass);}          
               if (binIndex == 4) {h_us_reco_wfp_scaled->Fill(recomass);}
               if (binIndex == 5) {h_cb_reco_wfp_scaled->Fill(recomass);}
               if (binIndex == 6) {h_ub_reco_wfp_scaled->Fill(recomass);}
               if (binIndex == 7) {h_x_reco_wfp_scaled->Fill(recomass);}
            } // ud jets
         } //recomass > 30

            if (scaled_recowfp_pt1 >= 30 && scaled_recowfp_pt2 >= 30 ){
               if (binIndex == 2) {h_ud_reco_wfp_scaled->Fill(recowfpmass_scaled);}
               if ((flav1 != 1 && flav2 != 1) && (flav1 != 2 && flav2 != 2)){
                  if (binIndex == 3) {h_cd_reco_wfp_scaled->Fill(recowfpmass_scaled);}          
                  if (binIndex == 4) {h_us_reco_wfp_scaled->Fill(recowfpmass_scaled);}
                  if (binIndex == 5) {h_cb_reco_wfp_scaled->Fill(recowfpmass_scaled);}
                  if (binIndex == 6) {h_ub_reco_wfp_scaled->Fill(recowfpmass_scaled);}
                  if (binIndex == 7) {h_x_reco_wfp_scaled->Fill(recowfpmass_scaled);}
               } // not ud jets
            }  // reco scaled pt >= 30
      } // jentry

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

      // reco scaled

      hAverageMasses_reco_scaled->SetBinContent(1, h_cs_reco_scaled->GetMean());
      hAverageMasses_reco_scaled->SetBinContent(2, h_ud_reco_scaled->GetMean());
      hAverageMasses_reco_scaled->SetBinContent(3, h_cd_reco_scaled->GetMean());
      hAverageMasses_reco_scaled->SetBinContent(4, h_us_reco_scaled->GetMean());
      hAverageMasses_reco_scaled->SetBinContent(5, h_cb_reco_scaled->GetMean());
      hAverageMasses_reco_scaled->SetBinContent(6, h_ub_reco_scaled->GetMean());
      hAverageMasses_reco_scaled->SetBinContent(7, h_x_reco_scaled->GetMean());

      hAverageMasses_reco_scaled->SetBinError(1, h_cs_reco_scaled->GetMeanError());
      hAverageMasses_reco_scaled->SetBinError(2, h_ud_reco_scaled->GetMeanError());
      hAverageMasses_reco_scaled->SetBinError(3, h_cd_reco_scaled->GetMeanError());
      hAverageMasses_reco_scaled->SetBinError(4, h_us_reco_scaled->GetMeanError());
      hAverageMasses_reco_scaled->SetBinError(5, h_cb_reco_scaled->GetMeanError());
      hAverageMasses_reco_scaled->SetBinError(6, h_ub_reco_scaled->GetMeanError());
      hAverageMasses_reco_scaled->SetBinError(7, h_x_reco_scaled->GetMeanError());

      // without fitProb

      hAverageMasses_gen_wfp->SetBinContent(1, h_cs_gen_wfp->GetMean());
      hAverageMasses_gen_wfp->SetBinContent(2, h_ud_gen_wfp->GetMean());
      hAverageMasses_gen_wfp->SetBinContent(3, h_cd_gen_wfp->GetMean());
      hAverageMasses_gen_wfp->SetBinContent(4, h_us_gen_wfp->GetMean());
      hAverageMasses_gen_wfp->SetBinContent(5, h_cb_gen_wfp->GetMean());
      hAverageMasses_gen_wfp->SetBinContent(6, h_ub_gen_wfp->GetMean());
      hAverageMasses_gen_wfp->SetBinContent(7, h_x_gen_wfp->GetMean());

      hAverageMasses_gen_wfp->SetBinError(1, h_cs_gen_wfp->GetMeanError());
      hAverageMasses_gen_wfp->SetBinError(2, h_ud_gen_wfp->GetMeanError());
      hAverageMasses_gen_wfp->SetBinError(3, h_cd_gen_wfp->GetMeanError());
      hAverageMasses_gen_wfp->SetBinError(4, h_us_gen_wfp->GetMeanError());
      hAverageMasses_gen_wfp->SetBinError(5, h_cb_gen_wfp->GetMeanError());
      hAverageMasses_gen_wfp->SetBinError(6, h_ub_gen_wfp->GetMeanError());
      hAverageMasses_gen_wfp->SetBinError(7, h_x_gen_wfp->GetMeanError());

      hAverageMasses_reco_wfp->SetBinContent(1, h_cs_reco_wfp->GetMean());
      hAverageMasses_reco_wfp->SetBinContent(2, h_ud_reco_wfp->GetMean());
      hAverageMasses_reco_wfp->SetBinContent(3, h_cd_reco_wfp->GetMean());
      hAverageMasses_reco_wfp->SetBinContent(4, h_us_reco_wfp->GetMean());
      hAverageMasses_reco_wfp->SetBinContent(5, h_cb_reco_wfp->GetMean());
      hAverageMasses_reco_wfp->SetBinContent(6, h_ub_reco_wfp->GetMean());
      hAverageMasses_reco_wfp->SetBinContent(7, h_x_reco_wfp->GetMean());

      hAverageMasses_reco_wfp->SetBinError(1, h_cs_reco_wfp->GetMeanError());
      hAverageMasses_reco_wfp->SetBinError(2, h_ud_reco_wfp->GetMeanError());
      hAverageMasses_reco_wfp->SetBinError(3, h_cd_reco_wfp->GetMeanError());
      hAverageMasses_reco_wfp->SetBinError(4, h_us_reco_wfp->GetMeanError());
      hAverageMasses_reco_wfp->SetBinError(5, h_cb_reco_wfp->GetMeanError());
      hAverageMasses_reco_wfp->SetBinError(6, h_ub_reco_wfp->GetMeanError());
      hAverageMasses_reco_wfp->SetBinError(7, h_x_reco_wfp->GetMeanError());


      hAverageMasses_reco_wfp_scaled->SetBinContent(1, h_cs_reco_wfp_scaled->GetMean());
      hAverageMasses_reco_wfp_scaled->SetBinContent(2, h_ud_reco_wfp_scaled->GetMean());
      hAverageMasses_reco_wfp_scaled->SetBinContent(3, h_cd_reco_wfp_scaled->GetMean());
      hAverageMasses_reco_wfp_scaled->SetBinContent(4, h_us_reco_wfp_scaled->GetMean());
      hAverageMasses_reco_wfp_scaled->SetBinContent(5, h_cb_reco_wfp_scaled->GetMean());
      hAverageMasses_reco_wfp_scaled->SetBinContent(6, h_ub_reco_wfp_scaled->GetMean());
      hAverageMasses_reco_wfp_scaled->SetBinContent(7, h_x_reco_wfp_scaled->GetMean());

      hAverageMasses_reco_wfp_scaled->SetBinError(1, h_cs_reco_wfp_scaled->GetMeanError());
      hAverageMasses_reco_wfp_scaled->SetBinError(2, h_ud_reco_wfp_scaled->GetMeanError());
      hAverageMasses_reco_wfp_scaled->SetBinError(3, h_cd_reco_wfp_scaled->GetMeanError());
      hAverageMasses_reco_wfp_scaled->SetBinError(4, h_us_reco_wfp_scaled->GetMeanError());
      hAverageMasses_reco_wfp_scaled->SetBinError(5, h_cb_reco_wfp_scaled->GetMeanError());
      hAverageMasses_reco_wfp_scaled->SetBinError(6, h_ub_reco_wfp_scaled->GetMeanError());
      hAverageMasses_reco_wfp_scaled->SetBinError(7, h_x_reco_wfp_scaled->GetMeanError());

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
