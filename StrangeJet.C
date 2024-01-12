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
  TH1D *h_dus = new TH1D("h_dus",";PtCand;N", nxbins, xbins);
  TH1D *h_d2 = new TH1D("h_d2",";PtCand, energy ratio;N", nxbins, xbins);
  TH1D *h_u2 = new TH1D("h_u2",";PtCand, energy ratio;N", nxbins, xbins);
  TH1D *h_s2 = new TH1D("h_s2",";PtCand, energy ratio;N", nxbins, xbins);
  TH1D *h_dus2 = new TH1D("h_dus2",";PtCand, energy;N", nxbins, xbins);

  TH1D *h_dusall = new TH1D("h_dusall",";PtCand, all S,U,D jets;N", nxbins, xbins);

  TH1D *h_d3 = new TH1D("h_d3",";PtCand, ratio nh;N", nxbins, xbins);
  TH1D *h_u3 = new TH1D("h_u3",";PtCand, ratio nh;N", nxbins, xbins);
  TH1D *h_s3 = new TH1D("h_s3",";PtCand, ratio nh;N", nxbins, xbins);
  TH1D *h_dus3 = new TH1D("h_dus3",";PtCand, nh;N", nxbins, xbins);
  TH1D *h_d4 = new TH1D("h_d4",";PtCand, energy ratio nh;N", nxbins, xbins);
  TH1D *h_u4 = new TH1D("h_u4",";PtCand, energy ratio nh;N", nxbins, xbins);
  TH1D *h_s4 = new TH1D("h_s4",";PtCand, energy ratio nh;N", nxbins, xbins);
  TH1D *h_dus4 = new TH1D("h_dus4",";PtCand, energy nh;N", nxbins, xbins);

  TH1D *h_d5 = new TH1D("h_d5",";PtCand, ratio nh + photon;N", nxbins, xbins);
  TH1D *h_u5 = new TH1D("h_u5",";PtCand, ratio nh + photon;N", nxbins, xbins);
  TH1D *h_s5 = new TH1D("h_s5",";PtCand, ratio nh + photon;N", nxbins, xbins);
  TH1D *h_dus5 = new TH1D("h_dus5",";PtCand, nh + photon;N", nxbins, xbins);
  TH1D *h_d6 = new TH1D("h_d6",";PtCand, energy ratio nh + photon;N", nxbins, xbins);
  TH1D *h_u6 = new TH1D("h_u6",";PtCand, energy ratio nh + photon;N", nxbins, xbins);
  TH1D *h_s6 = new TH1D("h_s6",";PtCand, energy ratio nh + photon;N", nxbins, xbins);
  TH1D *h_dus6 = new TH1D("h_dus6",";PtCand, energy nh + photon;N", nxbins, xbins);

  TH1D *h_k0l = new TH1D("h_k0l",";PtCand, ratio K^0_L;N", nxbins, xbins);
  TH1D *h_k0s = new TH1D("h_k0s",";PtCand, ratio K^0_S;N", nxbins, xbins);
  TH1D *h_kp = new TH1D("h_kp",";PtCand, ratio K^+;N", nxbins, xbins);
  TH1D *h_k0 = new TH1D("h_kp",";PtCand, ratio K^0;N", nxbins, xbins);
  TH1D *h_lambda = new TH1D("h_lambda",";PtCand, ratio Lambda;N", nxbins, xbins);
  TH1D *h_sigma0 = new TH1D("h_sigma0",";PtCand, ratio Sigma^0;N", nxbins, xbins);

  TH1D *h_k0l2 = new TH1D("h_k0l2",";PtCand, ratio K^0_L;N", nxbins, xbins);
  TH1D *h_k0s2 = new TH1D("h_k0s2",";PtCand, ratio K^0_S;N", nxbins, xbins);
  TH1D *h_kp2 = new TH1D("h_kp2",";PtCand, ratio K^+;N", nxbins, xbins);
  TH1D *h_k02 = new TH1D("h_kp2",";PtCand, ratio K^0;N", nxbins, xbins);
  TH1D *h_lambda2 = new TH1D("h_lambda2",";PtCand, ratio Lambda;N", nxbins, xbins);
  TH1D *h_sigma02 = new TH1D("h_sigma02",";PtCand, ratio Sigma^0;N", nxbins, xbins);
  
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

 /*    for (int k = 0; k != nPhoton; ++k) {
  int iPhoton = Photon_jetIdx[k];
  int iPhotonPart = Photon_genPartIdx[k];
  bool isPhoton = (GenJet_partonFlavour[i] == 22);

  if (i == iPhoton) {
    double pt_ph = Photon_pt[iPhoton];
    if (fabs(Photon_eta[iPhoton]) < 1.3 && pt_ph > 60 && pt_ph < 100 && isPhoton) {
      h_p->Fill(Photon_pt[iPhoton]);
    }
  }

      }*/
      for (int j = 0; j != nGenJetGenPartCand; ++j) {
	int iJet = GenJetGenPartCand_jetIdx[j];
	int iCand = GenJetGenPartCand_GenPartCandIdx[j];
	bool isSjet = (abs(GenJet_partonFlavour[i]) == 3);
	bool isDjet = (abs(GenJet_partonFlavour[i]) == 1);
	bool isUjet = (abs(GenJet_partonFlavour[i]) == 2 );
  bool isPhoton = (GenPartCand_pdgId[i] == 22);
  bool isKaonp = (GenPartCand_pdgId[i] == 321);
  bool isKaon0 = (GenPartCand_pdgId[i] == 311);
  bool isKaonL = (GenPartCand_pdgId[i] == 130);
  bool isKaonS = (GenPartCand_pdgId[i] == 310);
  bool isLambda = (GenPartCand_pdgId[i] == 3122);
  bool isSigma = (GenPartCand_pdgId[i] == 3212);


	if (i == iJet) {
	  // cout << "Cand" << iCand << ":" << GenPartCand_pt[iCand] << ", " ;
	  double pt = GenJet_pt[iJet];
    double p2 = sqrt(pow(GenPartCand_pt[iCand],2)+pow(GenPartCand_mass[iCand],2));
	  if (fabs(GenJet_eta[iJet]) < 1.3 && pt > 60 && pt < 100) {

// All DUS jets
      if (isSjet || isUjet || isDjet) {
            h_dusall->Fill(GenPartCand_pt[iCand]);
      }

// Neutral hadrons
      if (GenPartCand_charge[iCand] == 0){

        if (isSjet || isUjet || isDjet) {
          h_dus3->Fill(GenPartCand_pt[iCand]);
          h_dus4->Fill(p2);
        }

        if (isSjet) {
          h_s3->Fill(GenPartCand_pt[iCand]);
          h_s4->Fill(p2);

          if (isKaonL) {
            h_k0l->Fill(GenPartCand_pt[iCand]);
          }

          if (isKaonS) {
            h_k0s->Fill(GenPartCand_pt[iCand]);
          }

          if (isKaonp) {
            h_kp->Fill(GenPartCand_pt[iCand]);
          }

          if (isKaon0) {
            h_k0->Fill(GenPartCand_pt[iCand]);
          }

          if (isSigma) {
            h_sigma0->Fill(GenPartCand_pt[iCand]); 
          }

          if (isLambda) {
            h_lambda->Fill(GenPartCand_pt[iCand]); 
          }
        }

        if (isDjet) {
          h_d3->Fill(GenPartCand_pt[iCand]);
          h_d4->Fill(p2);

          if (isKaonL) {
            h_k0l2->Fill(GenPartCand_pt[iCand]);
          }

          if (isKaonS) {
            h_k0s2->Fill(GenPartCand_pt[iCand]);
          }

          if (isKaonp) {
            h_kp2->Fill(GenPartCand_pt[iCand]);
          }

          if (isKaon0) {
            h_k02->Fill(GenPartCand_pt[iCand]);
          }

          if (isSigma) {
            h_sigma02->Fill(GenPartCand_pt[iCand]); 
          }

          if (isLambda) {
            h_lambda2->Fill(GenPartCand_pt[iCand]); 
          }
        }


        if (isUjet) {
          h_u3->Fill(GenPartCand_pt[iCand]);
          h_u4->Fill(p2);

          if (isKaonL) {
            h_k0l2->Fill(GenPartCand_pt[iCand]);
          }

          if (isKaonS) {
            h_k0s2->Fill(GenPartCand_pt[iCand]);
          }

          if (isKaonp) {
            h_kp2->Fill(GenPartCand_pt[iCand]);
          }

          if (isKaon0) {
            h_k02->Fill(GenPartCand_pt[iCand]);
          }

          if (isSigma) {
            h_sigma02->Fill(GenPartCand_pt[iCand]); 
          }

          if (isLambda) {
            h_lambda2->Fill(GenPartCand_pt[iCand]); 
          }
        }


      }

/* // Neutral hadrons and photons
      if (GenPartCand_charge[iCand] == 0 && isPhoton){

        if (isSjet || isUjet || isDjet) {
          h_dus5->Fill(GenPartCand_pt[iCand]);
          h_dus6->Fill(p2);
        }
        if (isSjet) {
          h_s5->Fill(GenPartCand_pt[iCand]);
          h_s6->Fill(p2);
        }
        if (isDjet) {
          h_d5->Fill(GenPartCand_pt[iCand]);
          h_d6->Fill(p2);
        }
        if (isUjet) {
          h_u5->Fill(GenPartCand_pt[iCand]);
          h_u6->Fill(p2);
        }
      }*/

// Charged hadrons
      if (GenPartCand_charge[iCand] != 0){

        if (isSjet || isUjet || isDjet) {
          h_dus->Fill(GenPartCand_pt[iCand]);
          h_dus2->Fill(p2);
        }
        if (isSjet) {
          h_s->Fill(GenPartCand_pt[iCand]);
          h_s2->Fill(p2);

          if (isKaonL) {
            h_k0l->Fill(GenPartCand_pt[iCand]);
          }

          if (isKaonS) {
            h_k0s->Fill(GenPartCand_pt[iCand]);
          }

          if (isKaonp) {
            h_kp->Fill(GenPartCand_pt[iCand]);
          }

          if (isKaon0) {
            h_k0->Fill(GenPartCand_pt[iCand]);
          }

          if (isSigma) {
            h_sigma0->Fill(GenPartCand_pt[iCand]); 
          }

          if (isLambda) {
            h_lambda->Fill(GenPartCand_pt[iCand]); 
          }
        }

      if (isDjet) {
        h_d->Fill(GenPartCand_pt[iCand]);
        h_d2->Fill(p2);

        if (isKaonL) {
          h_k0l2->Fill(GenPartCand_pt[iCand]);
        }

        if (isKaonS) {
          h_k0s2->Fill(GenPartCand_pt[iCand]);
        }

         if (isKaonp) {
          h_kp2->Fill(GenPartCand_pt[iCand]);
        }

        if (isKaon0) {
          h_k02->Fill(GenPartCand_pt[iCand]);
        }

        if (isSigma) {
          h_sigma02->Fill(GenPartCand_pt[iCand]); 
        }

        if (isLambda) {
          h_lambda2->Fill(GenPartCand_pt[iCand]); 
        }
      }
      
      if (isUjet) {
        h_u->Fill(GenPartCand_pt[iCand]);
        h_u2->Fill(p2);
        if (isKaonL) {
          h_k0l2->Fill(GenPartCand_pt[iCand]);
        }

        if (isKaonS) {
          h_k0s2->Fill(GenPartCand_pt[iCand]);
        }

         if (isKaonp) {
          h_kp2->Fill(GenPartCand_pt[iCand]);
        }

        if (isKaon0) {
          h_k02->Fill(GenPartCand_pt[iCand]);
        }

        if (isSigma) {
          h_sigma02->Fill(GenPartCand_pt[iCand]); 
        }

        if (isLambda) {
          h_lambda2->Fill(GenPartCand_pt[iCand]); 
        }
      }
    }
    }
	}
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
}