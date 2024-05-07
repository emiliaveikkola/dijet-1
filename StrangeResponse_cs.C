#define StrangeResponse_cs_cxx
#include "StrangeResponse_cs.h"
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

   // Assuming udstag, ctag, btag, and gtag are member variables of StrangeResponse_cs
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

void StrangeResponse_cs::Loop()
{
//   In a ROOT session, you can do:
//      root> .L StrangeResponse_cs.C
//      root> StrangeResponse_cs t
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
   TFile *fout = new TFile("output_stag_cs_response.root","recreate");

   // Create a 2D cs_histogram
   TH1D *cs_hJetPairs = new TH1D("cs_hJetPairs", ";Jet pair;N",7,1,8);

   TH1D *cs_hJetPairs_scaled = new TH1D("cs_hJetPairs_scaled", ";Jet pair;N",7,1,8);

   TH1D *cs_h_cs = new TH1D("cs_h_cs", "; All in X;N", 1,0,1);
   TH1D *cs_h_ud = new TH1D("cs_h_ud", "; All in X;N", 1,1,2);
   TH1D *cs_h_cd = new TH1D("cs_h_cd", "; All in X;N", 1,2,3);
   TH1D *cs_h_us = new TH1D("cs_h_us", "; All in X;N", 1,3,4);
   TH1D *cs_h_cb = new TH1D("cs_h_cb", "; All in X;N", 1,4,5);
   TH1D *cs_h_ub = new TH1D("cs_h_ub", "; All in X;N", 1,5,6);
   TH1D *cs_h_x = new TH1D("cs_h_x", "; All in X;N", 1,6,7);

   TH1D *cs_h_x_cs = new TH1D("cs_h_x_cs", "; CS;N", 1,0,1);
   TH1D *cs_h_x_antics = new TH1D("cs_h_x_antics", "; CS;N", 1,0,1);
   TH1D *cs_h_x_anticantis = new TH1D("cs_h_x_anticantis", "; CS;N", 1,0,1);

   TH1D *cs_h_x_sd = new TH1D("cs_h_x_sd", "; SD;N", 1,0,1);
   TH1D *cs_h_x_antisd = new TH1D("cs_h_x_antisd", "; SD;N", 1,0,1);
   TH1D *cs_h_x_antisantid = new TH1D("cs_h_x_antisantid", "; SD;N", 1,0,1);

   TH1D *cs_h_x_cd = new TH1D("cs_h_x_cd", "; CD;N", 1,0,1);
   TH1D *cs_h_x_anticd = new TH1D("cs_h_x_anticd", "; CD;N", 1,0,1);
   TH1D *cs_h_x_anticantid = new TH1D("cs_h_x_anticantid", "; CD;N", 1,0,1);

   TH1D *cs_h_x_su = new TH1D("cs_h_x_su", "; SU;N", 1,0,1);
   TH1D *cs_h_x_antisu = new TH1D("cs_h_x_antisu", "; SU;N", 1,0,1);
   TH1D *cs_h_x_antisantiu = new TH1D("cs_h_x_antisantiu", "; SU;N", 1,0,1);

   TH1D *cs_h_x_cu = new TH1D("cs_h_x_cu", "; CU;N", 1,0,1);
   TH1D *cs_h_x_anticu = new TH1D("cs_h_x_anticu", "; CU;N", 1,0,1);
   TH1D *cs_h_x_anticantiu = new TH1D("cs_h_x_anticantiu", "; CU;N", 1,0,1);

   TH1D *cs_h_x_sb = new TH1D("cs_h_x_sb", "; SB;N", 1,0,1);
   TH1D *cs_h_x_antisb = new TH1D("cs_h_x_antisb", "; SB;N", 1,0,1);
   TH1D *cs_h_x_antisantib = new TH1D("cs_h_x_antisantib", "; SB;N", 1,0,1);

   TH1D *cs_h_x_cb = new TH1D("cs_h_x_cb", "; CB;N", 1,0,1);
   TH1D *cs_h_x_anticb = new TH1D("cs_h_x_anticb", "; CB;N", 1,0,1);
   TH1D *cs_h_x_anticantib = new TH1D("cs_h_x_anticantib", "; CB;N", 1,0,1);

   TH1D *cs_h_x_sg = new TH1D("cs_h_x_sg", "; SG;N", 1,0,1);
   TH1D *cs_h_x_antisg = new TH1D("cs_h_x_antisg", "; SG;N", 1,0,1);

   TH1D *cs_h_x_cg = new TH1D("cs_h_x_cg", "; CG;N", 1,0,1);
   TH1D *cs_h_x_anticg = new TH1D("cs_h_x_anticg", "; CG;N", 1,0,1);

   TH1D *cs_h_x_ud = new TH1D("cs_h_x_ud", "; UD;N", 1,1,2);
   TH1D *cs_h_x_antiud = new TH1D("cs_h_x_antiud", "; UD;N", 1,1,2);
   TH1D *cs_h_x_antiuantid = new TH1D("cs_h_x_antiuantid", "; UD;N", 1,1,2);

   TH1D *cs_h_x_us = new TH1D("cs_h_x_us", "; US;N", 1,1,2);
   TH1D *cs_h_x_antius = new TH1D("cs_h_x_antius", "; US;N", 1,1,2);
   TH1D *cs_h_x_antiuantis = new TH1D("cs_h_x_antiuantis", "; US;N", 1,1,2);

   TH1D *cs_h_x_ds = new TH1D("cs_h_x_ds", "; DS;N", 1,1,2);
   TH1D *cs_h_x_antids = new TH1D("cs_h_x_antids", "; DS;N", 1,1,2);
   TH1D *cs_h_x_antidantis = new TH1D("cs_h_x_antidantis", "; DS;N", 1,1,2);

   TH1D *cs_h_x_uc = new TH1D("cs_h_x_uc", "; UC;N", 1,1,2);
   TH1D *cs_h_x_antiuc = new TH1D("cs_h_x_antiuc", "; UC;N", 1,1,2);
   TH1D *cs_h_x_antiuantic = new TH1D("cs_h_x_antiuantic", "; UC;N", 1,1,2);

   TH1D *cs_h_x_dc = new TH1D("cs_h_x_dc", "; DC;N", 1,1,2);
   TH1D *cs_h_x_antidc = new TH1D("cs_h_x_antidc", "; DC;N", 1,1,2);
   TH1D *cs_h_x_antidantic = new TH1D("cs_h_x_antidantic", "; DC;N", 1,1,2);

   TH1D *cs_h_x_ub = new TH1D("cs_h_x_ub", "; UB;N", 1,1,2);
   TH1D *cs_h_x_antiub = new TH1D("cs_h_x_antiub", "; UB;N", 1,1,2);
   TH1D *cs_h_x_antiuantib = new TH1D("cs_h_x_antiuantib", "; UB;N", 1,1,2);

   TH1D *cs_h_x_db = new TH1D("cs_h_x_db", "; DB;N", 1,1,2);
   TH1D *cs_h_x_antidb = new TH1D("cs_h_x_antidb", "; DB;N", 1,1,2);
   TH1D *cs_h_x_antidantib = new TH1D("cs_h_x_antidantib", "; DB;N", 1,1,2);

   TH1D *cs_h_x_ug = new TH1D("cs_h_x_ug", "; UG;N", 1,1,2);
   TH1D *cs_h_x_antiug = new TH1D("cs_h_x_antiug", "; UG;N", 1,1,2);

   TH1D *cs_h_x_dg = new TH1D("cs_h_x_dg", "; DG;N", 1,1,2);
   TH1D *cs_h_x_antidg = new TH1D("cs_h_x_antidg", "; DG;N", 1,1,2);

   TH1D *cs_h_x_x = new TH1D("cs_h_x_x", "; X;N", 1,6,7);
   TH1D *cs_h_x_gg = new TH1D("cs_h_x_gg", "; X;N", 1,6,7);

    TProfile *h_cs_resp = new TProfile("h_cs_resp", ";p_{T,gen} (GeV);"
			                       "p_{T,reco}/p_{T,gen}",100,0,50);

 

   cs_hJetPairs->GetXaxis()->SetBinLabel(1, "cs");
   cs_hJetPairs->GetXaxis()->SetBinLabel(2, "ud");
   cs_hJetPairs->GetXaxis()->SetBinLabel(3, "cd");
   cs_hJetPairs->GetXaxis()->SetBinLabel(4, "us");
   cs_hJetPairs->GetXaxis()->SetBinLabel(5, "cb");
   cs_hJetPairs->GetXaxis()->SetBinLabel(6, "ub");
   cs_hJetPairs->GetXaxis()->SetBinLabel(7, "x");

   /*hMassFlavorPairs->GetXaxis()->SetBinLabel(1, "cs");
   hMassFlavorPairs->GetXaxis()->SetBinLabel(2, "ud");
   hMassFlavorPairs->GetXaxis()->SetBinLabel(3, "cd");
   hMassFlavorPairs->GetXaxis()->SetBinLabel(4, "us");
   hMassFlavorPairs->GetXaxis()->SetBinLabel(5, "cb");
   hMassFlavorPairs->GetXaxis()->SetBinLabel(6, "ub");
   hMassFlavorPairs->GetXaxis()->SetBinLabel(7, "x");
   */

   //TH2D *cs_hJetFlavourTags = new TH2D("cs_hJetFlavourTags", ";Jet1 Flavour;Jet2 Flavour",4,1,4,4,1,4);
   

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

        double res = (p4recojet1 + p4recojet2).Pt() / (p4genjet1 + p4genjet2).Pt();
        double gen_pt = (p4genjet1 + p4genjet2).Pt();
        double reco_pt = (p4recojet1 + p4recojet2).Pt();

         if (fitProb > 0.2){
            if (binIndex == 1){
               cs_h_cs->Fill(0);
            }
            if(scaled_gen_pt1 >= 30 && scaled_gen_pt2 >= 30){ //scaled_reco_pt1 >= 30 && scaled_reco_pt2 >= 30 && 
               if (binIndex == 2){
                  cs_h_ud->Fill(1);
               }
            }
            if (binIndex == 3){
               cs_h_cd->Fill(2);
            }
            if (binIndex == 4){
               cs_h_us->Fill(3);
            }
            if (binIndex == 5){
               cs_h_cb->Fill(4);
            }
            if (binIndex == 6){
               cs_h_ub->Fill(5);
            }
            if (binIndex == 7){
               cs_h_x->Fill(6);
               int binXIndex = DetermineXJetType(flav1, flav2);
               if (binXIndex == 1) cs_h_x_antics->Fill(0);
               if (binXIndex == 2) cs_h_x_cs->Fill(0);
               if (binXIndex == 3) cs_h_x_anticantis->Fill(0);

               if (binXIndex == 4) {cs_h_x_antisd->Fill(0); cs_h_x_antids->Fill(1);}
               if (binXIndex == 5) {cs_h_x_sd->Fill(0); cs_h_x_ds->Fill(1);}
               if (binXIndex == 6) {cs_h_x_antisantid->Fill(0); cs_h_x_antidantis->Fill(1);}

               if (binXIndex == 7) {cs_h_x_anticd->Fill(0); cs_h_x_antidc->Fill(1);}
               if (binXIndex == 8) {cs_h_x_cd->Fill(0); cs_h_x_dc->Fill(1);}
               if (binXIndex == 9) {cs_h_x_anticantid->Fill(0); cs_h_x_antidantic->Fill(1);}

               if (binXIndex == 10) {cs_h_x_antisu->Fill(0); cs_h_x_antius->Fill(1);}
               if (binXIndex == 11) {cs_h_x_su->Fill(0); cs_h_x_us->Fill(1);}
               if (binXIndex == 12) {cs_h_x_antisantiu->Fill(0); cs_h_x_antiuantis->Fill(1);}

               if (binXIndex == 13) {cs_h_x_anticu->Fill(0); cs_h_x_antiuc->Fill(1);}
               if (binXIndex == 14) {cs_h_x_cu->Fill(0); cs_h_x_uc->Fill(1);}
               if (binXIndex == 15) {cs_h_x_anticantiu->Fill(0); cs_h_x_antiuantic->Fill(1);}

               if (binXIndex == 16) cs_h_x_antisb->Fill(0);
               if (binXIndex == 17) cs_h_x_sb->Fill(0);
               if (binXIndex == 18) cs_h_x_antisantib->Fill(0);

               if (binXIndex == 19) cs_h_x_anticb->Fill(0);
               if (binXIndex == 20) cs_h_x_cb->Fill(0);
               if (binXIndex == 21) cs_h_x_anticantib->Fill(0);

               if (binXIndex == 22) cs_h_x_sg->Fill(0);
               if (binXIndex == 23) cs_h_x_antisg->Fill(0);

               if (binXIndex == 24) cs_h_x_cg->Fill(0);
               if (binXIndex == 25) cs_h_x_anticg->Fill(0);

               if (binXIndex == 26) cs_h_x_antiud->Fill(1);
               if (binXIndex == 27) cs_h_x_ud->Fill(1);
               if (binXIndex == 28) cs_h_x_antiuantid->Fill(1);

               if (binXIndex == 29) cs_h_x_antiub->Fill(1);
               if (binXIndex == 30) cs_h_x_ub->Fill(1);
               if (binXIndex == 31) cs_h_x_antiuantib->Fill(1);

               if (binXIndex == 32) cs_h_x_antidb->Fill(1);
               if (binXIndex == 33) cs_h_x_db->Fill(1);
               if (binXIndex == 34) cs_h_x_antidantib->Fill(1);

               if (binXIndex == 35) cs_h_x_ug->Fill(1);
               if (binXIndex == 36) cs_h_x_antiug->Fill(1);

               if (binXIndex == 37) cs_h_x_dg->Fill(1);
               if (binXIndex == 38) cs_h_x_antidg->Fill(1);

               if (binXIndex == 50) cs_h_x_gg->Fill(6);
               if (binXIndex == 100) cs_h_x_x->Fill(6);

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
            //charm and strange response
            if (binIndex == 1) h_cs_resp->Fill(gen_pt, res, weight);
         } // fitProb > 0.2
      } // jentry

      cs_hJetPairs->SetBinContent(1, cs_h_cs->GetEntries());
      cs_hJetPairs->SetBinContent(2, cs_h_ud->GetEntries());
      cs_hJetPairs->SetBinContent(3, cs_h_cd->GetEntries());
      cs_hJetPairs->SetBinContent(4, cs_h_us->GetEntries());
      cs_hJetPairs->SetBinContent(5, cs_h_ub->GetEntries());
      cs_hJetPairs->SetBinContent(6, cs_h_cb->GetEntries());
      cs_hJetPairs->SetBinContent(7, cs_h_x->GetEntries());

      cs_hJetPairs_scaled->SetBinContent(1, cs_h_cs->GetEntries()/0.5722);
      cs_hJetPairs_scaled->SetBinContent(2, cs_h_ud->GetEntries()/0.70812);
      cs_hJetPairs_scaled->SetBinContent(3, cs_h_cd->GetEntries());
      cs_hJetPairs_scaled->SetBinContent(4, cs_h_us->GetEntries());
      cs_hJetPairs_scaled->SetBinContent(5, cs_h_ub->GetEntries());
      cs_hJetPairs_scaled->SetBinContent(6, cs_h_cb->GetEntries());
      cs_hJetPairs_scaled->SetBinContent(7, cs_h_x->GetEntries());

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
