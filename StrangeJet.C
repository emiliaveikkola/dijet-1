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


  // Bins
  Double_t xbins[] = {0.11633, 0.17847, 0.24341, 0.31129, 0.38224, 0.45639, 0.53389, 0.61489, 0.69955, 0.78804, 0.88053, 0.97719, 1.07823, 1.18382, 1.29419, 1.40955, 1.53011, 1.65613, 1.78784, 1.92549, 2.06937, 2.21975, 2.37693, 2.5412, 2.7129, 2.89235, 3.07992, 3.27595, 3.48085, 3.695, 3.91883, 4.15277, 4.39728, 4.65284, 4.91995, 5.19912, 5.49091, 5.79588, 6.11463, 6.44778, 6.79598, 7.15992, 7.5403, 7.93787, 8.3534, 8.7877, 9.24163, 9.71606, 10.21193, 10.73021, 11.2719, 11.83807, 12.42982, 13.0483, 13.69473, 14.37037, 15.07653, 15.8146, 16.58602, 17.39229, 18.23499, 19.11576, 20.03633, 20.99849, 22.00413, 23.0552, 24.15376, 25.30195, 26.50203, 27.75632, 29.06729, 30.43749, 31.86959, 33.36641, 34.93085, 36.56597, 38.27498, 40.0612, 41.92812, 43.8794, 45.91884, 48.05043, 50.27832, 52.60688, 55.04064, 57.58437, 60.24303, 63.02181, 65.92614, 68.96169, 72.1344, 75.45046, 78.91634, 82.53882, 86.32497, 90.28218, 94.41819, 98.74107}; // Adjust the bin edges as needed
  int nxbins = sizeof(xbins) / sizeof(xbins[0]) - 1;

  TDirectory *curdir = gDirectory;
  TFile *fout = new TFile("output.root","recreate");
  
  //TH1D *h = new TH1D("h",";PtCand;N",1000,0,100);
  //TH1D *h2 = new TH1D("h2",";PtCand;N",1000,0,100);
  TH1D *h_d = new TH1D("h_d",";PtCand, ratio;N", nxbins, xbins);
  TH1D *h_u = new TH1D("h_u",";PtCand, ratio;N", nxbins, xbins);
  TH1D *h_s = new TH1D("h_s",";PtCand, ratio;N", nxbins, xbins);
  TH1D *h_dus = new TH1D("h_dus",";PtCand, ratio;N", nxbins, xbins);
  TH1D *h_d2 = new TH1D("h_d2",";PtCand, energy ratio;N", nxbins, xbins);
  TH1D *h_u2 = new TH1D("h_u2",";PtCand, energy ratio;N", nxbins, xbins);
  TH1D *h_s2 = new TH1D("h_s2",";PtCand, energy ratio;N", nxbins, xbins);
  TH1D *h_dus2 = new TH1D("h_dus2",";PtCand, energy ratio;N", nxbins, xbins);

  curdir->cd();   
     
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
    double p2 = sqrt(pow(GenPartCand_pt[iCand],2)+pow(GenPartCand_mass[iCand],2));
	  if (fabs(GenJet_eta[iJet]) < 1.3 && pt > 60 && pt < 100) {
      if (isSjet || isUjet || isDjet) {
        h_dus->Fill(GenPartCand_pt[iCand]);
        h_dus2->Fill(p2);
      }
      if (isSjet) {
        h_s->Fill(GenPartCand_pt[iCand]);
        h_s2->Fill(p2);
      }
      if (isDjet) {
        h_d->Fill(GenPartCand_pt[iCand]);
        h_d2->Fill(p2);
      }
      if (isUjet) {
        h_u->Fill(GenPartCand_pt[iCand]);
        h_u2->Fill(p2);
      }
    }
	}
	//h_s2 = h_s / h_dus;
  //h_u2 = h_u / h_dus;
  //h_d2 = h_d / h_dus;

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
  fout->Write();
  fout->Close();
  exit(0);
  //h->SetLineColor(kRed);
  // h->Draw();
  //h2->Draw("SAMES");
  
  /* h_d->SetLineColor(kRed);
     h_d->SetLineColor(kRed);
     h_ud2->SetLineColor(kBlue);
     h_s->SetLineColor(kGreen);
     h_s2->SetLineColor(kOrange); */

   int nUjet = h_u->GetEntries();
   int nDjet = h_d->GetEntries();
   int nSjet = h_s->GetEntries();

   cout << nSjet << " " << nUjet << " " << nDjet << endl;


  // Normalizing with number of jets
	h_u->Scale(1./nUjet);
	h_s->Scale(1./nSjet);
	h_d->Scale(1./nDjet);

  // Normalizing with the width of the x-axis
  h_u->Scale(1,"width");
	h_s->Scale(1,"width");
	h_d->Scale(1,"width");


	// The mean and mean error for each histogram
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
  TCanvas *canvas1 = new TCanvas("canvas1", "Particle Candidates in Jets", 800, 600);
  canvas1->SetLogy();
  canvas1->SetLogx();

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
  
  h_d2->Draw("LSAME");
     legend->AddEntry(h_d2, "D RecoJets", "l");
     
     h_u2->Draw("LSAME");
     legend->AddEntry(h_u2, "U RecoJets", "l");
     
     h_s2->Draw("LSAME");
     legend->AddEntry(h_s2, "S RecoJets", "l");
  
  // Draw the legend
  legend->Draw();
  
  // Show the canvas
  canvas1->Draw();

  // Normalizing with number of jets
	/*h_u->Scale(1./nUjet);
	h_s->Scale(1./nSjet);
	h_d->Scale(1./nDjet);

  // Normalizing with the width of the x-axis
  h_u->Scale(1,"width");
	h_s->Scale(1,"width");
	h_d->Scale(1,"width");

 TCanvas *canvas2 = new TCanvas("canvas2", "Particle Candidates in Jets2", 800, 600);
  canvas2->SetLogy();
  canvas2->SetLogx();

  // Set line colors for each histogram
  h_d2->SetLineColor(kRed);
  h_u2->SetLineColor(kBlue);
  h_s2->SetLineColor(kGreen);
  
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
  
   h_d2->Draw("LSAME");
     legend->AddEntry(h_d2, "D RecoJets", "l");
     
     h_u2->Draw("LSAME");
     legend->AddEntry(h_u2, "U RecoJets", "l");
     
     h_s2->Draw("LSAME");
     legend->AddEntry(h_s2, "S RecoJets", "l");
  
  // Draw the legend
  legend->Draw();
  
  // Show the canvas
  canvas->Draw();*/

  /*TCanvas *canvas = new tdrDiCanvas("camvas", "Name", canvas1, canvas2);*/
}
