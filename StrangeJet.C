#define StrangeJet_cxx
#include "StrangeJet.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <iostream>
#include <TLegend.h>


void StrangeJet::Loop()
{
//   In a ROOT session, you can do:
//      root> .L StrangeJet.C
//      root> StrangeJet t
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
   
   cout << "Hello World!" << endl;

   //TH1D *h = new TH1D("h",";PtCand;N",1000,0,100);
   //TH1D *h2 = new TH1D("h2",";PtCand;N",1000,0,100);
   TH1D *h_ud = new TH1D("h_ud",";PtCand;N",1000,0,100);
   TH1D *h_ud2 = new TH1D("h_ud2",";PtCand;N",1000,0,100);
   TH1D *h_s = new TH1D("h_s",";PtCand;N",1000,0,100);
   TH1D *h_s2 = new TH1D("h_s2",";PtCand;N",1000,0,100);   
     
   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;


      //      cout << "Processing Event " << event << endl;


      for (int i = 0; i != nGenJet; ++i) {
	//cout << "  GenJet " << i << ":" << GenJet_pt[i] << ", " << endl;
	for (int j = 0; j != nGenJetGenPartCand; ++j) {
	  int iJet = GenJetGenPartCand_jetIdx[j];
	  int iCand = GenJetGenPartCand_GenPartCandIdx[j];
	  bool isSjet = (abs(GenJet_partonFlavour[i]) == 3);
          bool isUDjet = (abs(GenJet_partonFlavour[i]) == 1 || abs(GenJet_partonFlavour[i]) == 2 );

	  if (isSjet) {
	    if (i == iJet) {
	      // cout << "Cand" << iCand << ":" << GenPartCand_pt[iCand] << ", " ;
	      double pt = GenJet_pt[iJet];
	      if (fabs(GenJet_eta[iJet]) < 1.3 && pt > 60 && pt < 100) {
		h_s->Fill(GenPartCand_pt[iCand]);
	      }
	    }
	  }

	  if (isUDjet) {
	    if (i == iJet) {
	      // cout << "Cand" << iCand << ":" << GenPartCand_pt[iCand] << ", " ;
	      double pt = GenJet_pt[iJet];
	      if (fabs(GenJet_eta[iJet]) < 1.3 && pt > 60 && pt < 100) {
		h_ud->Fill(GenPartCand_pt[iCand]);
	      }
	    }
	  }

	  // if (i == iJet) {
	    // cout << "Cand" << iCand << ":" << GenPartCand_pt[iCand] << ", " ;
	    //double pt = GenJet_pt[iJet];
	    //if (fabs(GenJet_eta[iJet]) < 1.3 && pt > 60 && pt < 100) {
	  // h->Fill(GenPartCand_pt[iCand]);
	  //}
	  // }
	}
	//cout << endl;
      }
      //cout << endl;

      for (int i = 0; i != nJet; ++i) {
	//cout << "  GenJet " << i << ":" << GenJet_pt[i] << ", " << endl;
	for (int j = 0; j != nJetPFCand; ++j) {
	  int iJet = JetPFCand_jetIdx[j];
	  int iCand = JetPFCand_PFCandIdx[j];
	  bool isSjet = (abs(Jet_partonFlavour[i]) == 3);
	  bool isUDjet = (abs(Jet_partonFlavour[i]) == 1 || abs(Jet_partonFlavour[i]) == 2 );
	  if (isUDjet) {
	    if (i == iJet) {
	      // cout << "Cand" << iCand << ":" << GenPartCand_pt[iCand] << ", " ;
	      double pt = Jet_pt[iJet];
	      if (fabs(Jet_eta[iJet]) < 1.3 && pt > 60 && pt < 100) {
		h_ud2->Fill(PFCand_pt[iCand]);
	      }
	    }
	  }

	  if (isSjet) {
	    if (i == iJet) {
	      // cout << "Cand" << iCand << ":" << GenPartCand_pt[iCand] << ", " ;
	      double pt = Jet_pt[iJet];
	      if (fabs(Jet_eta[iJet]) < 1.3 && pt > 60 && pt < 100) {
		h_s2->Fill(PFCand_pt[iCand]);
	      }
	    }
	  }

	  //if (i == iJet) {
	    // cout << "Cand" << iCand << ":" << GenPartCand_pt[iCand] << ", " ;
	  // double pt = Jet_pt[iJet];
	  //if (fabs(Jet_eta[iJet]) < 1.3 && pt > 60 && pt < 100) {
	  //  h2->Fill(PFCand_pt[iCand]);
	  // }
	  // }
	  }
	//cout << endl;
	}
      //cout << endl;
   
   }
   //h->SetLineColor(kRed);
   // h->Draw();
   //h2->Draw("SAMES");

   h_ud->SetLineColor(kTeal);
h_ud2->SetLineColor(kAzure);
h_s->SetLineColor(kViolet);
h_s2->SetLineColor(kSlate);

     // Create a TCanvas
   TCanvas *canvas = new TCanvas("canvas", "Particle Candidates in Jets", 800, 600);

   // Create a legend
   TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
   legend->SetTextSize(0.03);

   // Draw histograms with lines and add entries to the legend
   h_ud->Draw("LSAME");
   legend->AddEntry(h_ud, "UD GenJets", "l");

   h_ud2->Draw("LSAME");
   legend->AddEntry(h_ud2, "UD RecoJets", "l");

   h_s->Draw("LSAME");
   legend->AddEntry(h_s, "S GenJets", "l");

   h_s2->Draw("LSAME");
   legend->AddEntry(h_s2, "S RecoJets", "l");

   // Draw the legend
   legend->Draw();

   // Show the canvas
   canvas->Draw();
}
