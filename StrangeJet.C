#define StrangeJet_cxx
#include "StrangeJet.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <iostream>
#include <algorithm>
#include <TLegend.h>
#include <TColor.h>
#include "tdrstyle_mod22.C"


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

  int nSjet = 0;
  int nUjet = 0;
  int nDjet = 0;


  // Set custom binning
  Double_t xbins[] = {0.0, 0.04762, 0.09750, 0.14976, 0.20450, 0.26186, 0.32194, 0.38489, 0.45083, 0.51991,
		      0.59228, 0.66810, 0.74753, 0.83074, 0.91791, 1.00923, 1.10490, 1.20513, 1.31013, 1.42013,
		      1.53536, 1.65609, 1.78256, 1.91505, 2.05386, 2.19927, 2.35160, 2.51119, 2.67838, 2.85353,
		      3.03702, 3.22924, 3.43062, 3.64159, 3.86260, 4.09414, 4.33670, 4.59081, 4.85702, 5.13591,
		      5.42807, 5.73415, 6.05480, 6.39072, 6.74264, 7.11131, 7.49753, 7.90215, 8.32603, 8.77010,
		      9.23531, 9.72267, 10.23324, 10.76812, 11.32847, 11.91550, 12.53048, 13.17474, 13.84968,
		      14.55676, 15.29751, 16.07353, 16.88650, 17.73817, 18.63041, 19.56512, 20.54435, 21.57020,
		      22.64489, 23.77076, 24.95024, 26.18588, 27.48036, 28.83647, 30.25716, 31.74549, 33.30469,
		      34.93814, 36.64936, 38.44206, 40.32012, 42.28761, 44.34879, 46.50810, 48.77024, 51.14008,
		      53.62277, 56.22368, 58.94843, 61.80291, 64.79332, 67.92612, 71.20809, 74.64633, 78.24829,
		      82.02176, 85.97490, 90.11628, 94.45485, 100.0}; // Adjust the bin edges as needed
  int nxbins = sizeof(xbins) / sizeof(xbins[0]) - 1;

  //TH1D *h = new TH1D("h",";PtCand;N",1000,0,100);
  //TH1D *h2 = new TH1D("h2",";PtCand;N",1000,0,100);
  TH1D *h_d = new TH1D("h_d",";PtCand;N", nxbins, xbins);
  TH1D *h_u = new TH1D("h_u",";PtCand;N", nxbins, xbins);
  TH1D *h_s = new TH1D("h_s",";PtCand;N", nxbins, xbins);
  TH1D *h_d2 = new TH1D("h_d2",";PtCand;N", nxbins, xbins);
  TH1D *h_u2 = new TH1D("h_u2",";PtCand;N", nxbins, xbins);
  TH1D *h_s2 = new TH1D("h_s2",";PtCand;N", nxbins, xbins);   
     
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
	bool isDjet = (abs(GenJet_partonFlavour[i]) == 1);
	bool isUjet = (abs(GenJet_partonFlavour[i]) == 2 );

	if (i == iJet) {
	  // cout << "Cand" << iCand << ":" << GenPartCand_pt[iCand] << ", " ;
	  double pt = GenJet_pt[iJet];
	  if (fabs(GenJet_eta[iJet]) < 1.3 && pt > 60 && pt < 100) {
	    if (isSjet) {
			nSjet++;
	      h_s->Fill(GenPartCand_pt[iCand]);
	    }
	    if (isDjet) {
			nDjet++;
	      h_d->Fill(GenPartCand_pt[iCand]);
	    }
	    if (isUjet) {
			nUjet++;
	      h_u->Fill(GenPartCand_pt[iCand]);
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
    
    /* for (int i = 0; i != nJet; ++i) {
    //cout << "  GenJet " << i << ":" << GenJet_pt[i] << ", " << endl;
    for (int j = 0; j != nJetPFCand; ++j) {
    int iJet = JetPFCand_jetIdx[j];
    int iCand = JetPFCand_PFCandIdx[j];
    bool isSjet = (abs(Jet_partonFlavour[i]) == 3);
    bool isDjet = (abs(Jet_partonFlavour[i]) == 1);
    bool isUjet = (abs(Jet_partonFlavour[i]) == 2 );
    
    if (isDjet) {
    if (i == iJet) {
    // cout << "Cand" << iCand << ":" << GenPartCand_pt[iCand] << ", " ;
    double pt = Jet_pt[iJet];
    if (fabs(Jet_eta[iJet]) < 1.3 && pt > 60 && pt < 100) {
    h_d2->Fill(PFCand_pt[iCand]);
    }
    }
    }
    
    if (isUjet) {
    if (i == iJet) {
    // cout << "Cand" << iCand << ":" << GenPartCand_pt[iCand] << ", " ;
    double pt = Jet_pt[iJet];
    if (fabs(Jet_eta[iJet]) < 1.3 && pt > 60 && pt < 100) {
    h_u2->Fill(PFCand_pt[iCand]);
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
    } */
    //cout << endl;
    
  }
  //h->SetLineColor(kRed);
  // h->Draw();
  //h2->Draw("SAMES");
  
  /* h_d->SetLineColor(kRed);
     h_d->SetLineColor(kRed);
     h_ud2->SetLineColor(kBlue);
     h_s->SetLineColor(kGreen);
     h_s2->SetLineColor(kOrange); */


	 cout << nSjet << " " << nUjet << " " << nDjet << endl;

	h_u->Scale(1.0f/nUjet);
	h_s->Scale(1.0f/nSjet);
	h_d->Scale(1.0f/nDjet);


	// Get the mean and mean error for each histogram
	double meanD = h_d->GetMean();
	double meanErrorD = h_d->GetMeanError();

	double meanU = h_u->GetMean();
	double meanErrorU = h_u->GetMeanError();

	double meanS = h_s->GetMean();
	double meanErrorS = h_s->GetMeanError();

	// Print or use the means and mean errors as needed
	cout << "Mean D: " << meanD << " +/- " << meanErrorD << endl;
	cout << "Mean U: " << meanU << " +/- " << meanErrorU << endl;
	cout << "Mean S: " << meanS << " +/- " << meanErrorS << endl; 
  
  // Create a TCanvas
  TCanvas *canvas = new TCanvas("canvas", "Particle Candidates in Jets", 800, 600);
  //canvas->SetLogy();
  
  // Set line colors for each histogram
  h_d->SetLineColor(kRed);
  h_u->SetLineColor(kBlue);
  h_s->SetLineColor(kGreen);
  h_d2->SetLineColor(kPink);
  h_u2->SetLineColor(kViolet);
  h_s2->SetLineColor(kTeal);
  
  // Create a legend
  TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
  legend->SetTextSize(0.03);
  
  // Draw histograms with lines and add entries to the legend
  h_d->Draw("HE");
  legend->AddEntry(h_d, "D GenJets", "l");
  
  h_u->Draw("HESAME");
  legend->AddEntry(h_u, "U GenJets", "l");
  
  h_s->Draw("HESAME");
  legend->AddEntry(h_s, "S GenJets", "l");
  
  /* h_d2->Draw("LSAME");
     legend->AddEntry(h_d2, "D RecoJets", "l");
     
     h_u2->Draw("LSAME");
     legend->AddEntry(h_u2, "U RecoJets", "l");
     
     h_s2->Draw("LSAME");
     legend->AddEntry(h_s2, "S RecoJets", "l"); */
  
  // Draw the legend
  legend->Draw();
  
  // Show the canvas
  canvas->Draw();
}
