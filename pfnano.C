#define pfnano_cxx
#include "pfnano.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "TStopwatch.h"
#include "TLorentzVector.h"
#include "TProfile.h"

#include <iostream>

#include "tdrstyle_mod22.C"

void pfnano::Loop()
{
//   In a ROOT session, you can do:
//      root> .L pfnano.C
//      root> pfnano t
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

   Long64_t nentries = fChain->GetEntries();//Fast();

   cout << "Processing " << nentries << " events" << endl << flush;
   TStopwatch t;
   t.Start();
   const int nlap = 1000;
   const int nlap2 = 80000;

   TLorentzVector p4j, p4c, p4l, p4r;

   //setTDRStyle();
   
   // Inclusive jets pT binning
   double vx[] =
     {15, 18, 21, 24, 28, 32, 37, 43, 49, 56, 64, 74, 84,
      97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468,
      507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248,
      1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500,
      2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713,
      4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000};
   double nx = sizeof(vx) / sizeof(vx[0]) - 1;
   // Wide version
   double vxw[] =
     {15, 21, 28, 37, 49, 64, 84, 114, 153, 196, 272, 330, 395, 468, 548, 686, 846, 1032, 1248, 1588, 2000, 2500, 3103, 3832, 4713, 5777, 7000};
   double nxw = sizeof(vxw) / sizeof(vxw[0]) - 1;
   // eXtra Wide version
   double vxx[] =
     {15, 28, 49, 84, 153, 272, 395, 548, 846, 1248, 2000, 3103, 4713, 7000};
   double nxx = sizeof(vxx) / sizeof(vxx[0]) - 1;

   TDirectory *curdir = gDirectory;
   TFile *fout =  new TFile("pfnano.root","RECREATE");
   
   TProfile *prq = new TProfile("prq",";p_{T,genjet};Response (ud)",nx,vx);
   TProfile *pru = new TProfile("pru",";p_{T,genjet};Response (u)",nx,vx);
   TProfile *prd = new TProfile("prd",";p_{T,genjet};Response (d)",nx,vx);
   TProfile *prs = new TProfile("prs",";p_{T,genjet};Response (s)",nx,vx);
   TProfile *prc = new TProfile("prc",";p_{T,genjet};Response (c)",nx,vx);
   TProfile *prb = new TProfile("prb",";p_{T,genjet};Response (b)",nx,vx);
   TProfile *prg = new TProfile("prg",";p_{T,genjet};Response (g)",nx,vx);

   TProfile *pcq = new TProfile("pcq",";p_{T,genjet};Response (ud)",nx,vx);
   TProfile *pcu = new TProfile("pcu",";p_{T,genjet};Response (u)",nx,vx);
   TProfile *pcd = new TProfile("pcd",";p_{T,genjet};Response (d)",nx,vx);
   TProfile *pcs = new TProfile("pcs",";p_{T,genjet};Response (s)",nx,vx);
   TProfile *pcc = new TProfile("pcc",";p_{T,genjet};Response (c)",nx,vx);
   TProfile *pcb = new TProfile("pcb",";p_{T,genjet};Response (b)",nx,vx);
   TProfile *pcg = new TProfile("pcg",";p_{T,genjet};Response (g)",nx,vx);

   // Bin width 1./4. of ECAL crystal (2pi/(72.*5))
   TH1D *hdrq = new TH1D("hdrq",";#DeltaR(ud-jet,cand);N_{cand}",200,0,0.8727);
   TH1D *hdru = new TH1D("hdru",";#DeltaR(u-jet,cand);N_{cand}",200,0,0.8727);
   TH1D *hdrd = new TH1D("hdrd",";#DeltaR(d-jet,cand);N_{cand}",200,0,0.8727);
   TH1D *hdrs = new TH1D("hdrs",";#DeltaR(s-jet,cand);N_{cand}",200,0,0.8727);
   TH1D *hdrc = new TH1D("hdrc",";#DeltaR(c-jet,cand);N_{cand}",200,0,0.8727);
   TH1D *hdrb = new TH1D("hdrb",";#DeltaR(b-jet,cand);N_{cand}",200,0,0.8727);
   TH1D *hdrg = new TH1D("hdrg",";#DeltaR(g-jet,cand);N_{cand}",200,0,0.8727);

   TH1D *hrwq = new TH1D("hrwq",";#DeltaR(ud-jet,cand);N_{cand}",200,0,0.8727);
   TH1D *hrwu = new TH1D("hrwu",";#DeltaR(u-jet,cand);N_{cand}",200,0,0.8727);
   TH1D *hrwd = new TH1D("hrwd",";#DeltaR(d-jet,cand);N_{cand}",200,0,0.8727);
   TH1D *hrws = new TH1D("hrws",";#DeltaR(s-jet,cand);N_{cand}",200,0,0.8727);
   TH1D *hrwc = new TH1D("hrwc",";#DeltaR(c-jet,cand);N_{cand}",200,0,0.8727);
   TH1D *hrwb = new TH1D("hrwb",";#DeltaR(b-jet,cand);N_{cand}",200,0,0.8727);
   TH1D *hrwg = new TH1D("hrwg",";#DeltaR(g-jet,cand);N_{cand}",200,0,0.8727);

   // Fraction of energy carried by the leading particle
   TH1D *hfq = new TH1D("hfq",";p_{T,lead}/p_{T,jet};N_{ud-jet}",100,0,1);
   TH1D *hfu = new TH1D("hfu",";p_{T,lead}/p_{T,jet};N_{u-jet}",100,0,1);
   TH1D *hfd = new TH1D("hfd",";p_{T,lead}/p_{T,jet};N_{d-jet}",100,0,1);
   TH1D *hfs = new TH1D("hfs",";p_{T,lead}/p_{T,jet};N_{s-jet}",100,0,1);
   TH1D *hfc = new TH1D("hfc",";p_{T,lead}/p_{T,jet};N_{c-jet}",100,0,1);
   TH1D *hfb = new TH1D("hfb",";p_{T,lead}/p_{T,jet};N_{b-jet}",100,0,1);
   TH1D *hfg = new TH1D("hfg",";p_{T,lead}/p_{T,jet};N_{g-jet}",100,0,1);

   // Fragmentation function
   TH1D *hffq = new TH1D("hffq",";p_{T,cand}/p_{T,jet};N_{ud-jet}",100,0,1);
   TH1D *hffu = new TH1D("hffu",";p_{T,cand}/p_{T,jet};N_{u-jet}",100,0,1);
   TH1D *hffd = new TH1D("hffd",";p_{T,cand}/p_{T,jet};N_{d-jet}",100,0,1);
   TH1D *hffs = new TH1D("hffs",";p_{T,cand}/p_{T,jet};N_{s-jet}",100,0,1);
   TH1D *hffc = new TH1D("hffc",";p_{T,cand}/p_{T,jet};N_{c-jet}",100,0,1);
   TH1D *hffb = new TH1D("hffb",";p_{T,cand}/p_{T,jet};N_{b-jet}",100,0,1);
   TH1D *hffg = new TH1D("hffg",";p_{T,cand}/p_{T,jet};N_{g-jet}",100,0,1);

   // Fragmentation function sans leading particle
   TH1D *hf2q = new TH1D("hf2q",";p_{T,cand}/p_{T,jet};N_{ud-jet}",100,0,1);
   TH1D *hf2u = new TH1D("hf2u",";p_{T,cand}/p_{T,jet};N_{u-jet}",100,0,1);
   TH1D *hf2d = new TH1D("hf2d",";p_{T,cand}/p_{T,jet};N_{d-jet}",100,0,1);
   TH1D *hf2s = new TH1D("hf2s",";p_{T,cand}/p_{T,jet};N_{s-jet}",100,0,1);
   TH1D *hf2c = new TH1D("hf2c",";p_{T,cand}/p_{T,jet};N_{c-jet}",100,0,1);
   TH1D *hf2b = new TH1D("hf2b",";p_{T,cand}/p_{T,jet};N_{b-jet}",100,0,1);
   TH1D *hf2g = new TH1D("hf2g",";p_{T,cand}/p_{T,jet};N_{g-jet}",100,0,1);
   
   curdir->cd();
   
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;

      // Check if the signal flag has been set
      if (gInterrupted.load()) {
	cout << "Signal received, gracefully exiting the loop at entry "
	     << jentry << " and saving output." << endl << flush;
	// Perform any cleanup or partial saving of results here
	break; // Exit the loop
      }
      
      nb = fChain->GetEntry(jentry);   nbytes += nb;
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

      ////////////////
      // Particle loop
      ////////////////
      
      // Loop over two leading jets
      for (int i = 0; i != min(nGenJet,2); ++i) {

	p4j.SetPtEtaPhiM(GenJet_pt[i],GenJet_eta[i],GenJet_phi[i],
			 GenJet_mass[i]);
	
	//bool pass = (p4j.Pt()>84 && p4j.Pt()<153 && fabs(p4j.Eta())<1.3);
	bool pass = (p4j.Pt()>84 && p4j.Pt()<114 && fabs(p4j.Eta())<1.3);
	if (!pass) continue;

	// Pre-loop to find leading candidate in jet
	double ptlead(0.);
	int iLeadGenCand(-1);
	for (int k = 0; k != nGenJetGenPartCand; ++k) {

	  if (GenJetGenPartCand_genJetIdx[k]==i) {
	    int j = GenJetGenPartCand_GenPartCandIdx[k];
 	    double pt = GenPartCand_pt[j];
	    if (pt>ptlead) {
	      p4l.SetPtEtaPhiM(GenPartCand_pt[j],GenPartCand_eta[j],
			       GenPartCand_phi[j],GenPartCand_mass[j]);
	      ptlead = pt;
	      iLeadGenCand = j;
	    }
	  }
	} // for k

	Short_t f = GenJet_partonFlavour[i];
	double fi = ptlead / p4j.Pt();
	if (abs(f)==1|| abs(f)==2)
	  hfq->Fill(fi);
	if (abs(f)==1) hfd->Fill(fi);
	if (abs(f)==2) hfu->Fill(fi);
	if (abs(f)==3) hfs->Fill(fi);
	if (abs(f)==4) hfc->Fill(fi);
	if (abs(f)==5) hfb->Fill(fi);
	if (f==21)
	  hfg->Fill(fi);
	
	// Loop over candidates in these jets (k->j)
	for (int k = 0; k != nGenJetGenPartCand; ++k) {

	  int iGenJet = GenJetGenPartCand_genJetIdx[k];
	  if (iGenJet==i) {

	    int iGenCand = GenJetGenPartCand_GenPartCandIdx[k];
	    int j = iGenCand;
	    
	    p4c.SetPtEtaPhiM(GenPartCand_pt[j],GenPartCand_eta[j],
			     GenPartCand_phi[j],GenPartCand_mass[j]);

	    double dr = p4j.DeltaR(p4c);
	    //double dr = p4l.DeltaR(p4c);
	    Short_t f = GenJet_partonFlavour[i];
	    if (abs(f)==1|| abs(f)==2)
	      hdrq->Fill(dr);
	    if (abs(f)==1) hdrd->Fill(dr);
	    if (abs(f)==2) hdru->Fill(dr);
	    if (abs(f)==3) hdrs->Fill(dr);
	    if (abs(f)==4) hdrc->Fill(dr);
	    if (abs(f)==5) hdrb->Fill(dr);
	    if (f==21)
	      hdrg->Fill(dr);

	    double w = p4c.Pt() / p4j.Pt();
	    if (abs(f)==1|| abs(f)==2)
	      hrwq->Fill(dr, w);
	    if (abs(f)==1) hrwd->Fill(dr, w);
	    if (abs(f)==2) hrwu->Fill(dr, w);
	    if (abs(f)==3) hrws->Fill(dr, w);
	    if (abs(f)==4) hrwc->Fill(dr, w);
	    if (abs(f)==5) hrwb->Fill(dr, w);
	    if (f==21)
	      hrwg->Fill(dr, w);

	    double fi = p4c.Pt() / p4j.Pt();
	    if (abs(f)==1|| abs(f)==2)
	      hffq->Fill(fi);
	    if (abs(f)==1) hffd->Fill(fi);
	    if (abs(f)==2) hffu->Fill(fi);
	    if (abs(f)==3) hffs->Fill(fi);
	    if (abs(f)==4) hffc->Fill(fi);
	    if (abs(f)==5) hffb->Fill(fi);
	    if (f==21)
	      hffg->Fill(fi);

	    if (j != iLeadGenCand) {
	      if (abs(f)==1|| abs(f)==2)
		hf2q->Fill(fi);
	      if (abs(f)==1) hf2d->Fill(fi);
	      if (abs(f)==2) hf2u->Fill(fi);
	      if (abs(f)==3) hf2s->Fill(fi);
	      if (abs(f)==4) hf2c->Fill(fi);
	      if (abs(f)==5) hf2b->Fill(fi);
	      if (f==21)
		hf2g->Fill(fi);
	    } // lead cand
	    
	  } // in genjet
	} // for k
      } // for j

      //////////////////////
      // Jet response loop
      //////////////////////
      
      // Loop over two leading jets
      for (int i = 0; i != min(nGenJet,2); ++i) {

	p4j.SetPtEtaPhiM(GenJet_pt[i],GenJet_eta[i],GenJet_phi[i],
			 GenJet_mass[i]);
	
	bool pass = (fabs(p4j.Eta())<1.3);
	if (!pass) continue;
	
	// Loop over matching reco jetes
	for (int j = 0; j != nJet; ++j) {
	  
	  p4r.SetPtEtaPhiM(Jet_pt[j],Jet_eta[j],Jet_phi[j],
			   Jet_mass[j]);

	  if (p4j.DeltaR(p4r)<0.2) {
	    Short_t f = GenJet_partonFlavour[i];
	    double pt = p4j.Pt();

	    // Raw response
	    double r = p4r.Pt()*(1-Jet_rawFactor[j]) / pt;
	    if (abs(f)==1|| abs(f)==2)
	      prq->Fill(pt, r);
	    if (abs(f)==1) pru->Fill(pt, r);
	    if (abs(f)==2) prd->Fill(pt, r);
	    if (abs(f)==3) prs->Fill(pt, r);
	    if (abs(f)==4) prc->Fill(pt, r);
	    if (abs(f)==5) prb->Fill(pt, r);
	    if (f==21)
	      prg->Fill(pt, r);

	    // Corrected response
	    double c = p4r.Pt() / pt;
	    if (abs(f)==1|| abs(f)==2)
	      pcq->Fill(pt, c);
	    if (abs(f)==1) pcu->Fill(pt, c);
	    if (abs(f)==2) pcd->Fill(pt, c);
	    if (abs(f)==3) pcs->Fill(pt, c);
	    if (abs(f)==4) pcc->Fill(pt, c);
	    if (abs(f)==5) pcb->Fill(pt, c);
	    if (f==21)
	      pcg->Fill(pt, c);
	    
	  } // dR<0.2
	} // for j
      } // for i
      
   } // for jentry

   fout->Write();
   fout->Close();
} // Loop
