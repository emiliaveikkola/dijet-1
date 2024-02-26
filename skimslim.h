//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Feb 21 15:19:26 2024 by ROOT version 6.30/04
// from TTree Events/Events
// found on file: output_skimmed_tree_100.root
//////////////////////////////////////////////////////////

#ifndef skimslim_h
#define skimslim_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class skimslim {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          run;
   UInt_t          luminosityBlock;
   ULong64_t       event;
   Int_t           nGenJetGenPartCand;
   Int_t           GenJetGenPartCand_GenPartCandIdx[700];   //[nGenJetGenPartCand]
   Int_t           GenJetGenPartCand_genJetIdx[700];   //[nGenJetGenPartCand]
   Int_t           nGenPartCand;
   Int_t           GenPartCand_charge[700];   //[nGenPartCand]
   Int_t           GenPartCand_pdgId[700];   //[nGenPartCand]
   Float_t         GenPartCand_eta[700];   //[nGenPartCand]
   Float_t         GenPartCand_mass[700];   //[nGenPartCand]
   Float_t         GenPartCand_phi[700];   //[nGenPartCand]
   Float_t         GenPartCand_pt[700];   //[nGenPartCand]
   Int_t           nGenJet;
   Float_t         GenJet_eta[24];   //[nGenJet]
   Float_t         GenJet_mass[24];   //[nGenJet]
   Float_t         GenJet_phi[24];   //[nGenJet]
   Float_t         GenJet_pt[24];   //[nGenJet]
   Float_t         genWeight;
   Int_t           nJet;
   Float_t         Jet_eta[18];   //[nJet]
   Float_t         Jet_mass[18];   //[nJet]
   Float_t         Jet_phi[18];   //[nJet]
   Float_t         Jet_pt[18];   //[nJet]
   Float_t         Jet_rawFactor[18];   //[nJet]
   Short_t         GenJet_partonFlavour[24];   //[nGenJet]

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_luminosityBlock;   //!
   TBranch        *b_event;   //!
   TBranch        *b_nGenJetGenPartCand;   //!
   TBranch        *b_GenJetGenPartCand_GenPartCandIdx;   //!
   TBranch        *b_GenJetGenPartCand_genJetIdx;   //!
   TBranch        *b_nGenPartCand;   //!
   TBranch        *b_GenPartCand_charge;   //!
   TBranch        *b_GenPartCand_pdgId;   //!
   TBranch        *b_GenPartCand_eta;   //!
   TBranch        *b_GenPartCand_mass;   //!
   TBranch        *b_GenPartCand_phi;   //!
   TBranch        *b_GenPartCand_pt;   //!
   TBranch        *b_nGenJet;   //!
   TBranch        *b_GenJet_eta;   //!
   TBranch        *b_GenJet_mass;   //!
   TBranch        *b_GenJet_phi;   //!
   TBranch        *b_GenJet_pt;   //!
   TBranch        *b_genWeight;   //!
   TBranch        *b_nJet;   //!
   TBranch        *b_Jet_eta;   //!
   TBranch        *b_Jet_mass;   //!
   TBranch        *b_Jet_phi;   //!
   TBranch        *b_Jet_pt;   //!
   TBranch        *b_Jet_rawFactor;   //!
   TBranch        *b_GenJet_partonFlavour;   //!

   skimslim(TTree *tree=0);
   virtual ~skimslim();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef skimslim_cxx
skimslim::skimslim(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("output_skimmed_tree_100.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("output_skimmed_tree_100.root");
      }
      f->GetObject("Events",tree);

   }
   Init(tree);
}

skimslim::~skimslim()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t skimslim::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t skimslim::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void skimslim::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("luminosityBlock", &luminosityBlock, &b_luminosityBlock);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("nGenJetGenPartCand", &nGenJetGenPartCand, &b_nGenJetGenPartCand);
   fChain->SetBranchAddress("GenJetGenPartCand_GenPartCandIdx", GenJetGenPartCand_GenPartCandIdx, &b_GenJetGenPartCand_GenPartCandIdx);
   fChain->SetBranchAddress("GenJetGenPartCand_genJetIdx", GenJetGenPartCand_genJetIdx, &b_GenJetGenPartCand_genJetIdx);
   fChain->SetBranchAddress("nGenPartCand", &nGenPartCand, &b_nGenPartCand);
   fChain->SetBranchAddress("GenPartCand_charge", GenPartCand_charge, &b_GenPartCand_charge);
   fChain->SetBranchAddress("GenPartCand_pdgId", GenPartCand_pdgId, &b_GenPartCand_pdgId);
   fChain->SetBranchAddress("GenPartCand_eta", GenPartCand_eta, &b_GenPartCand_eta);
   fChain->SetBranchAddress("GenPartCand_mass", GenPartCand_mass, &b_GenPartCand_mass);
   fChain->SetBranchAddress("GenPartCand_phi", GenPartCand_phi, &b_GenPartCand_phi);
   fChain->SetBranchAddress("GenPartCand_pt", GenPartCand_pt, &b_GenPartCand_pt);
   fChain->SetBranchAddress("nGenJet", &nGenJet, &b_nGenJet);
   fChain->SetBranchAddress("GenJet_eta", GenJet_eta, &b_GenJet_eta);
   fChain->SetBranchAddress("GenJet_mass", GenJet_mass, &b_GenJet_mass);
   fChain->SetBranchAddress("GenJet_phi", GenJet_phi, &b_GenJet_phi);
   fChain->SetBranchAddress("GenJet_pt", GenJet_pt, &b_GenJet_pt);
   fChain->SetBranchAddress("genWeight", &genWeight, &b_genWeight);
   fChain->SetBranchAddress("nJet", &nJet, &b_nJet);
   fChain->SetBranchAddress("Jet_eta", Jet_eta, &b_Jet_eta);
   fChain->SetBranchAddress("Jet_mass", Jet_mass, &b_Jet_mass);
   fChain->SetBranchAddress("Jet_phi", Jet_phi, &b_Jet_phi);
   fChain->SetBranchAddress("Jet_pt", Jet_pt, &b_Jet_pt);
   fChain->SetBranchAddress("Jet_rawFactor", Jet_rawFactor, &b_Jet_rawFactor);
   fChain->SetBranchAddress("GenJet_partonFlavour", GenJet_partonFlavour, &b_GenJet_partonFlavour);
   Notify();
}

Bool_t skimslim::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void skimslim::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t skimslim::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
if (entry) {}
   return 1;
}
#endif // #ifdef skimslim_cxx
