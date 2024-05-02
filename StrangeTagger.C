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


   int DetermineXJetType(int x, int y) {
    if (x == 3 && y == -4 || x == -3 && y == 4 ||
    x == 4 && y == -3 || x == -4 && y == 3) return 1;
    
    if (x == 3 && y == 4 || x == 4 && y == 3) return 2;

    if (x == -3 && y == -4 || x == -4 && y == -3) return 3;



    if (x == 3 && y == -1 || x == -3 && y == 1 ||
    x == 1 && y == -3 || x == -1 && y == 3) return 4;

    if (x == 3 && y == 1 || x == 1 && y == 3) return 5;

   if (x == -4 && y == -1 || x == -1 && y == -4) return 6;




   if (x == 3 && y == -2 || x == -3 && y == 2 ||
    x == 2 && y == -3 || x == -2 && y == 3) return 7;

   if (x == 3 && y == 2 || x == 2 && y == 3) return 8;

   if (x == -3 && y == -2 || x == -2 && y == -3) return 9;


   

   if (x == 4 && y == -2 || x == -4 && y == 2 ||
    x == 2 && y == -4 || x == -2 && y == 4) return 10;

   if (x == 4 && y == 2 || x == 2 && y == 4) return 11;

   if (x == -4 && y == -2 || x == -2 && y == -4) return 12;




   if (x == 3 && y == -5 || x == -3 && y == 5 ||
    x == 5 && y == -3 || x == -5 && y == 3) return 13;
   
   if (x == 3 && y == 5 || x == 5 && y == 3) return 14;

   if (x == -3 && y == -5 || x == -5 && y == -3) return 15;



   if (x == 5 && y == -4 || x == -5 && y == 4 ||
    x == 4 && y == -5 || x == -4 && y == 5) return 16;

   if (x == 5 && y == 4 || x == 4 && y == 5) return 17;

   if (x == -5 && y == -4 || x == -4 && y == -5) return 18;



   if (x == 3 && y == 21 || x == 21 && y == 3) return 19;

   if (x == -3 && y == 21 || x == 21 && y == -3) return 20;


   if (x == 4 && y == 21 || x == 21 && y == 4) return 21;

   if (x == -4 && y == 21 || x == 21 && y == -4) return 22;


   if (x == 1 && y == -2 || x == -1 && y == 2 ||
    x == 2 && y == -1 || x == -1 && y == 4) return 23;

   if (x == 1 && y == 2 || x == 2 && y == 1) return 24;

   if (x == -1 && y == -2 || x == -2 && y == -1) return 25;


   if (x == 2 && y == -5 || x == -2 && y == 5 ||
    x == 5 && y == -2 || x == -2 && y == 3) return 26;

   if (x == 2 && y == 5 || x == 5 && y == 2) return 27;

   if (x == -2 && y == -5 || x == -5 && y == -2) return 28;


   if (x == 5 && y == -1 || x == -5 && y == 1 ||
    x == 1 && y == -5 || x == -1 && y == 5) return 29;

   if (x == 5 && y == 1 || x == 1 && y == 5) return 30;

   if (x == -5 && y == -1 || x == -1 && y == -5) return 31;



   if (x == 2 && y == 21 || x == 21 && y == 2) return 32;

   if (x == -2 && y == 21 || x == 21 && y == -2) return 33;



   if (x == 1 && y == 21 || x == 21 && y == 1) return 34;

   if (x == -1 && y == 21 || x == 21 && y == -1) return 35;

   if (x == 21 && y == 21) return 50;

   return 100;
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
   TFile *fout = new TFile("output_stag3.root","recreate");

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

   TH1D *h_cs_gen = new TH1D("h_cs_gen", ";Mass;N",200,0,1);
   TH1D *h_ud_gen = new TH1D("h_ud_gen", ";Mass;N",200,0,1);
   TH1D *h_cd_gen = new TH1D("h_cd_gen", ";Mass;N",200,0,1);
   TH1D *h_us_gen = new TH1D("h_us_gen", ";Mass;N",200,0,1);
   TH1D *h_cb_gen = new TH1D("h_cb_gen", ";Mass;N",200,0,1);
   TH1D *h_ub_gen = new TH1D("h_ub_gen", ";Mass;N",200,0,1);
   TH1D *h_x_gen = new TH1D("h_x_gen", ";Mass;N",200,0,1);

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

   TH1D *h_cs = new TH1D("h_cs", "; All in X;N", 1,0,1);

   TH1D *h_ud = new TH1D("h_ud", "; All in X;N", 1,1,2);
   TH1D *h_cd = new TH1D("h_cd", "; All in X;N", 1,2,3);
   TH1D *h_us = new TH1D("h_us", "; All in X;N", 1,3,4);
   TH1D *h_cb = new TH1D("h_cb", "; All in X;N", 1,4,5);
   TH1D *h_ub = new TH1D("h_ub", "; All in X;N", 1,5,6);
   TH1D *h_x = new TH1D("h_x", "; All in X;N", 1,6,7);

   TH1D *h_x_cs = new TH1D("h_x_cs", "; CS;N", 1,0,1);
   TH1D *h_x_antics = new TH1D("h_x_antics", "; CS;N", 1,0,1);
   TH1D *h_x_anticantis = new TH1D("h_x_anticantis", "; CS;N", 1,0,1);

   TH1D *h_x_sd = new TH1D("h_x_sd", "; SD;N", 1,0,1);
   TH1D *h_x_antisd = new TH1D("h_x_antisd", "; SD;N", 1,0,1);
   TH1D *h_x_antisantid = new TH1D("h_x_antisantid", "; SD;N", 1,0,1);

   TH1D *h_x_cd = new TH1D("h_x_cd", "; CD;N", 1,0,1);
   TH1D *h_x_anticd = new TH1D("h_x_anticd", "; CD;N", 1,0,1);
   TH1D *h_x_anticantid = new TH1D("h_x_anticantid", "; CD;N", 1,0,1);

   TH1D *h_x_su = new TH1D("h_x_su", "; SU;N", 1,0,1);
   TH1D *h_x_antisu = new TH1D("h_x_antisu", "; SU;N", 1,0,1);
   TH1D *h_x_antisantiu = new TH1D("h_x_antisantiu", "; SU;N", 1,0,1);

   TH1D *h_x_cu = new TH1D("h_x_cu", "; CU;N", 1,0,1);
   TH1D *h_x_anticu = new TH1D("h_x_anticu", "; CU;N", 1,0,1);
   TH1D *h_x_anticantiu = new TH1D("h_x_anticantiu", "; CU;N", 1,0,1);

   TH1D *h_x_sb = new TH1D("h_x_sb", "; SB;N", 1,0,1);
   TH1D *h_x_antisb = new TH1D("h_x_antisb", "; SB;N", 1,0,1);
   TH1D *h_x_antisantib = new TH1D("h_x_antisantib", "; SB;N", 1,0,1);

   TH1D *h_x_cb = new TH1D("h_x_cb", "; CB;N", 1,0,1);
   TH1D *h_x_anticb = new TH1D("h_x_anticb", "; CB;N", 1,0,1);
   TH1D *h_x_anticantib = new TH1D("h_x_anticantib", "; CB;N", 1,0,1);

   TH1D *h_x_sg = new TH1D("h_x_sg", "; SG;N", 1,0,1);
   TH1D *h_x_antisg = new TH1D("h_x_antisg", "; SG;N", 1,0,1);

   TH1D *h_x_cg = new TH1D("h_x_cg", "; CG;N", 1,0,1);
   TH1D *h_x_anticg = new TH1D("h_x_anticg", "; CG;N", 1,0,1);

   TH1D *h_x_ud = new TH1D("h_x_ud", "; UD;N", 1,1,2);
   TH1D *h_x_antiud = new TH1D("h_x_antiud", "; UD;N", 1,1,2);
   TH1D *h_x_antiuantid = new TH1D("h_x_antiuantid", "; UD;N", 1,1,2);

   TH1D *h_x_us = new TH1D("h_x_us", "; US;N", 1,1,2);
   TH1D *h_x_antius = new TH1D("h_x_antius", "; US;N", 1,1,2);
   TH1D *h_x_antiuantis = new TH1D("h_x_antiuantis", "; US;N", 1,1,2);

   TH1D *h_x_ds = new TH1D("h_x_ds", "; DS;N", 1,1,2);
   TH1D *h_x_antids = new TH1D("h_x_antids", "; DS;N", 1,1,2);
   TH1D *h_x_antidantis = new TH1D("h_x_antidantis", "; DS;N", 1,1,2);

   TH1D *h_x_uc = new TH1D("h_x_uc", "; UC;N", 1,1,2);
   TH1D *h_x_antiuc = new TH1D("h_x_antiuc", "; UC;N", 1,1,2);
   TH1D *h_x_antiuantic = new TH1D("h_x_antiuantic", "; UC;N", 1,1,2);

   TH1D *h_x_dc = new TH1D("h_x_dc", "; DC;N", 1,1,2);
   TH1D *h_x_antidc = new TH1D("h_x_antidc", "; DC;N", 1,1,2);
   TH1D *h_x_antidantic = new TH1D("h_x_antidantic", "; DC;N", 1,1,2);

   TH1D *h_x_ub = new TH1D("h_x_ub", "; UB;N", 1,1,2);
   TH1D *h_x_antiub = new TH1D("h_x_antiub", "; UB;N", 1,1,2);
   TH1D *h_x_antiuantib = new TH1D("h_x_antiuantib", "; UB;N", 1,1,2);

   TH1D *h_x_db = new TH1D("h_x_db", "; DB;N", 1,1,2);
   TH1D *h_x_antidb = new TH1D("h_x_antidb", "; DB;N", 1,1,2);
   TH1D *h_x_antidantib = new TH1D("h_x_antidantib", "; DB;N", 1,1,2);

   TH1D *h_x_ug = new TH1D("h_x_ug", "; UG;N", 1,1,2);
   TH1D *h_x_antiug = new TH1D("h_x_antiug", "; UG;N", 1,1,2);

   TH1D *h_x_dg = new TH1D("h_x_dg", "; DG;N", 1,1,2);
   TH1D *h_x_antidg = new TH1D("h_x_antidg", "; DG;N", 1,1,2);

   TH1D *h_x_x = new TH1D("h_x_x", "; X;N", 1,6,7);
   TH1D *h_x_gg = new TH1D("h_x_gg", "; X;N", 1,6,7);

 

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
int count_c_d = 0, count_c_antid = 0, count_c_u = 0, count_c_antiu = 0,
    count_c_s = 0, count_c_antis = 0, count_c_c = 0, count_c_antic = 0,
    count_c_b = 0, count_c_antib = 0, count_c_g = 0,
    count_antic_d = 0, count_antic_antid = 0, count_antic_u = 0, count_antic_antiu = 0,
    count_antic_s = 0, count_antic_antis = 0, count_antic_c = 0, count_antic_antic = 0,
    count_antic_b = 0, count_antic_antib = 0, count_antic_g = 0,
    count_s_d = 0, count_s_antid = 0, count_s_u = 0, count_s_antiu = 0,
    count_s_s = 0, count_s_antis = 0, count_s_c = 0, count_s_antic = 0,
    count_s_b = 0, count_s_antib = 0, count_s_g = 0,
    count_antis_d = 0, count_antis_antid = 0, count_antis_u = 0, count_antis_antiu = 0,
    count_antis_s = 0, count_antis_antis = 0, count_antis_c = 0, count_antis_antic = 0,
    count_antis_b = 0, count_antis_antib = 0, count_antis_g = 0,
    count_antid_d = 0, count_antid_antid = 0, count_antid_u = 0, count_antid_antiu = 0,
    count_antid_s = 0, count_antid_antis = 0, count_antid_c = 0, count_antid_antic = 0,
    count_antid_b = 0, count_antid_antib = 0, count_antid_g = 0,
    count_d_d = 0, count_d_antid = 0, count_d_u = 0, count_d_antiu = 0,
    count_d_s = 0, count_d_antis = 0, count_d_c = 0, count_d_antic = 0,
    count_d_b = 0, count_d_antib = 0, count_d_g = 0,
    count_antiu_d = 0, count_antiu_antid = 0, count_antiu_u = 0, count_antiu_antiu = 0,
    count_antiu_s = 0, count_antiu_antis = 0, count_antiu_c = 0, count_antiu_antic = 0,
    count_antiu_b = 0, count_antiu_antib = 0, count_antiu_g = 0,
    count_u_d = 0, count_u_antid = 0, count_u_u = 0, count_u_antiu = 0,
    count_u_s = 0, count_u_antis = 0, count_u_c = 0, count_u_antic = 0,
    count_u_b = 0, count_u_antib = 0, count_u_g = 0,
    count_antib_d = 0, count_antib_antid = 0, count_antib_u = 0, count_antib_antiu = 0,
    count_antib_s = 0, count_antib_antis = 0, count_antib_c = 0, count_antib_antic = 0,
    count_antib_b = 0, count_antib_antib = 0, count_antib_g = 0,
    count_b_d = 0, count_b_antid = 0, count_b_u = 0, count_b_antiu = 0,
    count_b_s = 0, count_b_antis = 0, count_b_c = 0, count_b_antic = 0,
    count_b_b = 0, count_b_antib = 0, count_b_g = 0,
    count_g_g = 0;

// Create vector of pairs
std::map<std::string, int&> counters = {
    {"count_c_d", count_c_d},
    {"count_c_antid", count_c_antid},
    {"count_c_u", count_c_u},
    {"count_c_antiu", count_c_antiu},
    {"count_c_s", count_c_s},
    {"count_c_antis", count_c_antis},
    {"count_c_c", count_c_c},
    {"count_c_antic", count_c_antic},
    {"count_c_b", count_c_b},
    {"count_c_antib", count_c_antib},
    {"count_c_g", count_c_g},

    {"count_antic_d", count_antic_d},
    {"count_antic_antid", count_antic_antid},
    {"count_antic_u", count_antic_u},
    {"count_antic_antiu", count_antic_antiu},
    {"count_antic_s", count_antic_s},
    {"count_antic_antis", count_antic_antis},
    {"count_antic_antic", count_antic_antic},
    {"count_antic_b", count_antic_b},
    {"count_antic_antib", count_antic_antib},
    {"count_antic_g", count_antic_g},

    {"count_s_d", count_s_d},
    {"count_s_antid", count_s_antid},
    {"count_s_u", count_s_u},
    {"count_s_antiu", count_s_antiu},
    {"count_s_s", count_s_s},
    {"count_s_antis", count_s_antis},
    {"count_s_b", count_s_b},
    {"count_s_antib", count_s_antib},
    {"count_s_g", count_s_g},

    {"count_antis_d", count_antis_d},
    {"count_antis_antid", count_antis_antid},
    {"count_antis_u", count_antis_u},
    {"count_antis_antiu", count_antis_antiu},
    {"count_antis_antis", count_antis_antis},
    {"count_antis_b", count_antis_b},
    {"count_antis_antib", count_antis_antib},
    {"count_antis_g", count_antis_g},

    {"count_d_d", count_d_d},
    {"count_d_antid", count_d_antid},
    {"count_d_u", count_d_u},
    {"count_d_antiu", count_d_antiu},
    {"count_d_b", count_d_b},
    {"count_d_antib", count_d_antib},
    {"count_d_g", count_d_g},

    {"count_antid_antid", count_antid_antid},
    {"count_antid_u", count_antid_u},
    {"count_antid_antiu", count_antid_antiu},
    {"count_antid_b", count_antid_b},
    {"count_antid_antib", count_antid_antib},
    {"count_antid_g", count_antid_g},

    {"count_u_u", count_u_u},
    {"count_u_antiu", count_u_antiu},
    {"count_u_b", count_u_b},
    {"count_u_antib", count_u_antib},
    {"count_u_g", count_u_g},

    {"count_antiu_antiu", count_antiu_antiu},
    {"count_antiu_b", count_antiu_b},
    {"count_antiu_antib", count_antiu_antib},
    {"count_antiu_g", count_antiu_g},

    {"count_b_b", count_b_b},
    {"count_b_antib", count_b_antib},
    {"count_b_g", count_b_g},

    {"count_antib_antib", count_antib_antib},
    {"count_antib_g", count_antib_g},
    
    {"count_g_g", count_g_g}
};






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
            if (binIndex == 1){
               h_cs->Fill(0);
            }
            if(scaled_gen_pt1 >= 30 && scaled_gen_pt2 >= 30){ //scaled_reco_pt1 >= 30 && scaled_reco_pt2 >= 30 && 
               if (binIndex == 2){
                  h_ud->Fill(1);
               }
            }
            if (binIndex == 3){
               h_cd->Fill(2);
            }
            if (binIndex == 4){
               h_us->Fill(3);
            }
            if (binIndex == 5){
               h_cb->Fill(4);
            }
            if (binIndex == 6){
               h_ub->Fill(5);
            }
            if (binIndex == 7){
               h_x->Fill(6);
               int binXIndex = DetermineXJetType(flav1, flav2);
               if (binXIndex == 1) h_x_antics->Fill(0);
               if (binXIndex == 2) h_x_cs->Fill(0);
               if (binXIndex == 3) h_x_anticantis->Fill(0);

               if (binXIndex == 4) {h_x_antisd->Fill(0); h_x_antids->Fill(1);}
               if (binXIndex == 5) {h_x_sd->Fill(0); h_x_ds->Fill(1);}
               if (binXIndex == 6) {h_x_antisantid->Fill(0); h_x_antidantis->Fill(1);}

               if (binXIndex == 7) {h_x_anticd->Fill(0); h_x_antidc->Fill(1);}
               if (binXIndex == 8) {h_x_cd->Fill(0); h_x_dc->Fill(1);}
               if (binXIndex == 9) {h_x_anticantid->Fill(0); h_x_antidantic->Fill(1);}

               if (binXIndex == 10) {h_x_antisu->Fill(0); h_x_antius->Fill(1);}
               if (binXIndex == 11) {h_x_su->Fill(0); h_x_us->Fill(1);}
               if (binXIndex == 12) {h_x_antisantiu->Fill(0); h_x_antiuantis->Fill(1);}

               if (binXIndex == 13) {h_x_anticu->Fill(0); h_x_antiuc->Fill(1);}
               if (binXIndex == 14) {h_x_cu->Fill(0); h_x_uc->Fill(1);}
               if (binXIndex == 15) {h_x_anticantiu->Fill(0); h_x_antiuantic->Fill(1);}

               if (binXIndex == 16) h_x_antisb->Fill(0);
               if (binXIndex == 17) h_x_sb->Fill(0);
               if (binXIndex == 18) h_x_antisantib->Fill(0);

               if (binXIndex == 19) h_x_anticb->Fill(0);
               if (binXIndex == 20) h_x_cb->Fill(0);
               if (binXIndex == 21) h_x_anticantib->Fill(0);

               if (binXIndex == 22) h_x_sg->Fill(0);
               if (binXIndex == 23) h_x_antisg->Fill(0);

               if (binXIndex == 24) h_x_cg->Fill(0);
               if (binXIndex == 25) h_x_anticg->Fill(0);

               if (binXIndex == 26) h_x_antiud->Fill(1);
               if (binXIndex == 27) h_x_ud->Fill(1);
               if (binXIndex == 28) h_x_antiuantid->Fill(1);

               if (binXIndex == 29) h_x_antiub->Fill(1);
               if (binXIndex == 30) h_x_ub->Fill(1);
               if (binXIndex == 31) h_x_antiuantib->Fill(1);

               if (binXIndex == 32) h_x_antidb->Fill(1);
               if (binXIndex == 33) h_x_db->Fill(1);
               if (binXIndex == 34) h_x_antidantib->Fill(1);

               if (binXIndex == 35) h_x_ug->Fill(1);
               if (binXIndex == 36) h_x_antiug->Fill(1);

               if (binXIndex == 37) h_x_dg->Fill(1);
               if (binXIndex == 38) h_x_antidg->Fill(1);

               if (binXIndex == 50) h_x_gg->Fill(6);
               if (binXIndex == 100) h_x_x->Fill(6);

            }

            if (binIndex == 7){
               if (flav1 == 4 || flav2 == 4) {
                  if (flav1 == 1 || flav2 == 1) count_c_d++;
                  if (flav1 == -1 || flav2 == -1) count_c_antid++;
                  if (flav1 == 2 || flav2 == 2) count_c_u++;
                  if (flav1 == -2 || flav2 == -2) count_c_antiu++;
                  if (flav1 == 3 || flav2 == 3) count_c_s++;
                  if (flav1 == -3 || flav2 == -3) count_c_antis++;
                  if (flav1 == 4 && flav2 == 4) count_c_c++;
                  if (flav1 == -4 || flav2 == -4) count_c_antic++;
                  if (flav1 == 5 || flav2 == 5) count_c_b++;
                  if (flav1 == -5 || flav2 == -5) count_c_antib++;
                  if (flav1 == 21 || flav2 == 21) count_c_g++;
               }

               if (flav1 == -4 || flav2 == -4) {
                  if (flav1 == 1 || flav2 == 1) count_antic_d++;
                  if (flav1 == -1 || flav2 == -1) count_antic_antid++;
                  if (flav1 == 2 || flav2 == 2) count_antic_u++;
                  if (flav1 == -2 || flav2 == -2) count_antic_antiu++;
                  if (flav1 == 3 || flav2 == 3) count_antic_s++;
                  if (flav1 == -3 || flav2 == -3) count_antic_antis++;
                  //if (flav1 == 4 || flav2 == 4) count_antic_c++;
                  if (flav1 == -4 && flav2 == -4) count_antic_antic++;
                  if (flav1 == 5 || flav2 == 5) count_antic_b++;
                  if (flav1 == -5 || flav2 == -5) count_antic_antib++;
                  if (flav1 == 21 || flav2 == 21) count_antic_g++;
               }

               if (flav1 == 3 || flav2 == 3) {
                  if (flav1 == 1 || flav2 == 1) count_s_d++;
                  if (flav1 == -1 || flav2 == -1) count_s_antid++;
                  if (flav1 == 2 || flav2 == 2) count_s_u++;
                  if (flav1 == -2 || flav2 == -2) count_s_antiu++;
                  if (flav1 == 3 && flav2 == 3) count_s_s++;
                  if (flav1 == -3 || flav2 == -3) count_s_antis++;
                  //if (flav1 == 4 || flav2 == 4) count_s_c++;
                  //if (flav1 == -4 || flav2 == -4) count_s_antic++;
                  if (flav1 == 5 || flav2 == 5) count_s_b++;
                  if (flav1 == -5 || flav2 == -5) count_s_antib++;
                  if (flav1 == 21 || flav2 == 21) count_s_g++;
               }

               if (flav1 == -3 || flav2 == -3) {
                  if (flav1 == 1 || flav2 == 1) count_antis_d++;
                  if (flav1 == -1 || flav2 == -1) count_antis_antid++;
                  if (flav1 == 2 || flav2 == 2) count_antis_u++;
                  if (flav1 == -2 || flav2 == -2) count_antis_antiu++;
                  //if (flav1 == 3 || flav2 == 3) count_antis_s++;
                  if (flav1 == -3 && flav2 == -3) count_antis_antis++;
                  //if (flav1 == 4 || flav2 == 4) count_antis_c++;
                  //if (flav1 == -4 || flav2 == -4) count_antis_antic++;
                  if (flav1 == 5 || flav2 == 5) count_antis_b++;
                  if (flav1 == -5 || flav2 == -5) count_antis_antib++;
                  if (flav1 == 21 || flav2 == 21) count_antis_g++;
               }

               if (flav1 == 1 || flav2 == 1) {
                  if (flav1 == 1 && flav2 == 1) count_d_d++;
                  if (flav1 == -1 || flav2 == -1) count_d_antid++;
                  if (flav1 == 2 || flav2 == 2) count_d_u++;
                  if (flav1 == -2 || flav2 == -2) count_d_antiu++;
                  //if (flav1 == 3 || flav2 == 3) count_d_s++;
                  //if (flav1 == -3 || flav2 == -3) count_d_antis++;
                  //if (flav1 == 4 || flav2 == 4) count_d_c++;
                  //if (flav1 == -4 || flav2 == -4) count_d_antic++;
                  if (flav1 == 5 || flav2 == 5) count_d_b++;
                  if (flav1 == -5 || flav2 == -5) count_d_antib++;
                  if (flav1 == 21 || flav2 == 21) count_d_g++;
               }

               if (flav1 == -1 || flav2 == -1) {
                  //if (flav1 == 1 || flav2 == 1) count_antid_d++;
                  if (flav1 == -1 && flav2 == -1) count_antid_antid++;
                  if (flav1 == 2 || flav2 == 2) count_antid_u++;
                  if (flav1 == -2 || flav2 == -2) count_antid_antiu++;
                  //if (flav1 == 3 || flav2 == 3) count_antid_s++;
                  //if (flav1 == -3 || flav2 == -3) count_antid_antis++;
                  //if (flav1 == 4 || flav2 == 4) count_antid_c++;
                  //if (flav1 == -4 || flav2 == -4) count_antid_antic++;
                  if (flav1 == 5 || flav2 == 5) count_antid_b++;
                  if (flav1 == -5 || flav2 == -5) count_antid_antib++;
                  if (flav1 == 21 || flav2 == 21) count_antid_g++;
               }
               if (flav1 == 2 || flav2 == 2) {
                  //if (flav1 == 1 || flav2 == 1) count_u_d++;
                  //if (flav1 == -1 || flav2 == -1) count_u_antid++;
                  if (flav1 == 2 && flav2 == 2) count_u_u++;
                  if (flav1 == -2 || flav2 == -2) count_u_antiu++;
                  //if (flav1 == 3 || flav2 == 3) count_u_s++;
                  //if (flav1 == -3 || flav2 == -3) count_u_antis++;
                  //if (flav1 == 4 || flav2 == 4) count_u_c++;
                  //if (flav1 == -4 || flav2 == -4) count_u_antic++;
                  if (flav1 == 5 || flav2 == 5) count_u_b++;
                  if (flav1 == -5 || flav2 == -5) count_u_antib++;
                  if (flav1 == 21 || flav2 == 21) count_u_g++;
               }
               if (flav1 == -2 || flav2 == -2) {
                  //if (flav1 == 1 || flav2 == 1) count_antiu_d++;
                  //if (flav1 == -1 || flav2 == -1) count_antiu_antid++;
                 //if (flav1 == 2 || flav2 == 2) count_antiu_u++;
                  if (flav1 == -2 && flav2 == -2) count_antiu_antiu++;
                  //if (flav1 == 3 || flav2 == 3) count_antiu_s++;
                  //if (flav1 == -3 || flav2 == -3) count_antiu_antis++;
                  //if (flav1 == 4 || flav2 == 4) count_antiu_c++;
                  //if (flav1 == -4 || flav2 == -4) count_antiu_antic++;
                  if (flav1 == 5 || flav2 == 5) count_antiu_b++;
                  if (flav1 == -5 || flav2 == -5) count_antiu_antib++;
                  if (flav1 == 21 || flav2 == 21) count_antiu_g++;
               }

               if (flav1 == 5 || flav2 == 5) {
                  //if (flav1 == 1 || flav2 == 1) count_b_d++;
                  //if (flav1 == -1 || flav2 == -1) count_b_antid++;
                  //if (flav1 == 2 || flav2 == 2) count_b_u++;
                  //if (flav1 == -2 || flav2 == -2) count_b_antiu++;
                  //if (flav1 == 3 || flav2 == 3) count_b_s++;
                  //if (flav1 == -3 || flav2 == -3) count_b_antis++;
                  //if (flav1 == 4 || flav2 == 4) count_b_c++;
                  //if (flav1 == -4 || flav2 == -4) count_b_antic++;
                  if (flav1 == 5 && flav2 == 5) count_b_b++;
                  if (flav1 == -5 || flav2 == -5) count_b_antib++;
                  if (flav1 == 21 || flav2 == 21) count_b_g++;
               }
               if (flav1 == -5 || flav2 == -5) {
                  //if (flav1 == 1 || flav2 == 1) count_antib_d++;
                  //if (flav1 == -1 || flav2 == -1) count_antib_antid++;
                  //if (flav1 == 2 || flav2 == 2) count_antib_u++;
                  //if (flav1 == -2 || flav2 == -2) count_antib_antiu++;
                  //if (flav1 == 3 || flav2 == 3) count_antib_s++;
                  //if (flav1 == -3 || flav2 == -3) count_antib_antis++;
                  //if (flav1 == 4 || flav2 == 4) count_antib_c++;
                  //if (flav1 == -4 || flav2 == -4) count_antib_antic++;
                  //if (flav1 == 5 || flav2 == 5) count_antib_b++;
                  if (flav1 == -5 && flav2 == -5) count_antib_antib++;
                  if (flav1 == 21 || flav2 == 21) count_antib_g++;
               }

               if (flav1 == 21 && flav2 == 21) count_g_g++;
            }
         }
/////// FITPROB > 0.2 ///////////
         if (fitProb > 0.2){
            if (recomass > 30 && genmass > 30) {
               hJetFlavours->Fill(min(abs(flav1),6), min(abs(flav2),6));
               //hJetPairs->Fill(binIndex);
            }

            if (genmass > 30) {
               hMassFlavorPairs_gen->Fill(binIndex,recomass/genmass);
               if (binIndex == 1) {h_cs_gen->Fill(recomass/genmass);}
               if (binIndex == 2) {h_ud_gen->Fill(recomass/genmass);}
               if (binIndex == 3) {h_cd_gen->Fill(recomass/genmass);}          
               if (binIndex == 4) {h_us_gen->Fill(recomass/genmass);}
               if (binIndex == 5) {h_cb_gen->Fill(recomass/genmass);}
               if (binIndex == 6) {h_ub_gen->Fill(recomass/genmass);}
               if (binIndex == 7) {h_x_gen->Fill(recomass/genmass);}
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
               /*
            if (scaled_reco_pt1 >= 30 && scaled_reco_pt2 >= 30 && scaled_gen_pt1 >= 30 && scaled_gen_pt2 >= 30 ){
               if (binIndex == 2) {
                  hJetPairs_scaled->Fill(binIndex);
               }
            }
            
            if (recomass > 30 && genmass > 30) {
               if (binIndex != 2) hJetPairs_scaled->Fill(binIndex);
            }
            */  
            

            
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

      hJetPairs->SetBinContent(1, h_cs->GetEntries());
      hJetPairs->SetBinContent(2, h_ud->GetEntries());
      hJetPairs->SetBinContent(3, h_cd->GetEntries());
      hJetPairs->SetBinContent(4, h_us->GetEntries());
      hJetPairs->SetBinContent(5, h_ub->GetEntries());
      hJetPairs->SetBinContent(6, h_cb->GetEntries());
      hJetPairs->SetBinContent(7, h_x->GetEntries());

      hJetPairs_scaled->SetBinContent(1, h_cs->GetEntries()/0.5722);
      hJetPairs_scaled->SetBinContent(2, h_ud->GetEntries()/0.70812);
      hJetPairs_scaled->SetBinContent(3, h_cd->GetEntries());
      hJetPairs_scaled->SetBinContent(4, h_us->GetEntries());
      hJetPairs_scaled->SetBinContent(5, h_ub->GetEntries());
      hJetPairs_scaled->SetBinContent(6, h_cb->GetEntries());
      hJetPairs_scaled->SetBinContent(7, h_x->GetEntries());

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

// Custom comparison function to sort by value
    auto compare = [](const auto& a, const auto& b) {
        return a.second > b.second;
    };

    // Sort the map by value
    std::vector<std::pair<std::string, int>> sorted_counters(counters.begin(), counters.end());
    std::sort(sorted_counters.begin(), sorted_counters.end(), compare);

    // Print the sorted counters
    for (const auto& counter : sorted_counters) {
        std::cout << counter.first << ": " << counter.second << std::endl;
    }



      fout->Write();
      fout->Close();
      exit(0);
   }
