#include <vector>
#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <TH2.h>
#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <TLorentzVector.h>

#include <iostream>
#include <algorithm>
#include <TLegend.h>
#include <TColor.h>
#include <TStopwatch.h>
#include "tdrstyle_mod22.C"

int skimandslim() {
    // Open the input file
    //TFile* input_file = TFile::Open("tree_1.root", "READ");
    //if (!input_file || input_file->IsZombie()) {
       //7 std::cerr << "Error opening input file." << std::endl << flush;
        //return -1;
    //}

        for (int i = 1; i <= 100; ++i) {
        std::stringstream ss;
        ss << "tree_" << i << ".root";
        std::string inputFileName = ss.str();

        TFile* input_file = TFile::Open(Form("/Users/macbookpro/Downloads/data/0000/%s",inputFileName.c_str()), "READ");
        if (!input_file || input_file->IsZombie()) {
            std::cerr << "Error opening input file: " << inputFileName << std::endl;
            continue; // Skip to next file
        }
   

    // Get the TTree from the input file
    TTree* tree = nullptr;
    input_file->GetObject("Events", tree);
    if (!tree) {
        std::cerr << "Tree 'Events' not found." << std::endl<< flush;
        input_file->Close();
        return -1;
    }



    // Create a new file for the skimmed and slimmed output
    TFile* output_file = TFile::Open(Form("/Users/macbookpro/Downloads/data/skimmed/output_skimmed_%s",inputFileName.c_str()), "RECREATE");
    if (!output_file || output_file->IsZombie()) {
        std::cerr << "Error creating output file." << std::endl<< flush;
        input_file->Close();
        return -1;
    }



    // Select branches to keep
    tree->SetBranchStatus("*", 0); // Disable all branches first

    // Scalars
Short_t GenJet_partonFlavour[19];
Float_t genWeight, GenJet_pt[19], GenJet_eta[19], GenJet_phi[19], GenJet_mass[19];
Int_t nGenJet, nGenJetGenPartCand;
Int_t GenJetGenPartCand_genJetIdx[700], GenJetGenPartCand_GenPartCandIdx[700], GenPartCand_pdgId[700];
Float_t GenPartCand_pt[700], GenPartCand_eta[700], GenPartCand_phi[700], GenPartCand_mass[700];
Int_t GenPartCand_charge[700];
UInt_t          run;
UInt_t          luminosityBlock;
ULong64_t       event;
Int_t           nJet;
Float_t         Jet_phi[14];   //[nJet]
Float_t         Jet_pt[14];   //[nJet]
Float_t         Jet_eta[14];   //[nJet]
Float_t         Jet_mass[14];   //[nJet]
Float_t         Jet_rawFactor[14];   //[nJet]

std::vector<std::string> branchNames = {"genWeight",
"GenJet_partonFlavour", "GenJetGenPartCand_genJetIdx", "GenJetGenPartCand_GenPartCandIdx","GenPartCand_pdgId",
"nGenJet", "GenJet_pt", "GenJet_eta", "GenJet_phi", "GenJet_mass",
"nJet", "Jet_pt", "Jet_eta", "Jet_phi", "Jet_mass",
"Jet_rawFactor",
"GenPartCand_pt", "GenPartCand_eta", "GenPartCand_phi",  "GenPartCand_mass", "GenPartCand_charge"};

// Set branch addresses
     // Set branch status to 1 (enable) and set address for each variable
    tree->SetBranchStatus("genWeight", 1);
    tree->SetBranchAddress("genWeight", &genWeight);

    tree->SetBranchStatus("GenJet_partonFlavour", 1);
    tree->SetBranchAddress("GenJet_partonFlavour", GenJet_partonFlavour);

    tree->SetBranchStatus("nGenJet", 1);
    tree->SetBranchAddress("nGenJet", &nGenJet);

    tree->SetBranchStatus("GenJet_pt", 1);
    tree->SetBranchAddress("GenJet_pt", GenJet_pt);

    tree->SetBranchStatus("GenJet_eta", 1);
    tree->SetBranchAddress("GenJet_eta", GenJet_eta);

    tree->SetBranchStatus("GenJet_phi", 1);
    tree->SetBranchAddress("GenJet_phi", GenJet_phi);

    tree->SetBranchStatus("GenJet_mass", 1);
    tree->SetBranchAddress("GenJet_mass", GenJet_mass);

    tree->SetBranchStatus("GenJetGenPartCand_genJetIdx", 1);
    tree->SetBranchAddress("GenJetGenPartCand_genJetIdx", GenJetGenPartCand_genJetIdx);

    tree->SetBranchStatus("GenJetGenPartCand_GenPartCandIdx", 1);
    tree->SetBranchAddress("GenJetGenPartCand_GenPartCandIdx", GenJetGenPartCand_GenPartCandIdx);

    tree->SetBranchStatus("GenPartCand_pdgId", 1);
    tree->SetBranchAddress("GenPartCand_pdgId", GenPartCand_pdgId);

    tree->SetBranchStatus("GenPartCand_pt", 1);
    tree->SetBranchAddress("GenPartCand_pt", GenPartCand_pt);

    tree->SetBranchStatus("GenPartCand_eta", 1);
    tree->SetBranchAddress("GenPartCand_eta", GenPartCand_eta);

    tree->SetBranchStatus("GenPartCand_phi", 1);
    tree->SetBranchAddress("GenPartCand_phi", GenPartCand_phi);

    tree->SetBranchStatus("GenPartCand_mass", 1);
    tree->SetBranchAddress("GenPartCand_mass", GenPartCand_mass);

    tree->SetBranchStatus("GenPartCand_charge", 1);
    tree->SetBranchAddress("GenPartCand_charge", GenPartCand_charge);

    // Setting branch addresses for event information
    tree->SetBranchStatus("run", 1);
    tree->SetBranchAddress("run", &run);

    tree->SetBranchStatus("luminosityBlock", 1);
    tree->SetBranchAddress("luminosityBlock", &luminosityBlock);

    tree->SetBranchStatus("event", 1);
    tree->SetBranchAddress("event", &event);

    // Jet information
    tree->SetBranchStatus("nJet", 1);
    tree->SetBranchAddress("nJet", &nJet);

    tree->SetBranchStatus("Jet_phi", 1);
    tree->SetBranchAddress("Jet_phi", Jet_phi);

    tree->SetBranchStatus("Jet_pt", 1);
    tree->SetBranchAddress("Jet_pt", Jet_pt);

    tree->SetBranchStatus("Jet_eta", 1);
    tree->SetBranchAddress("Jet_eta", Jet_eta);

    tree->SetBranchStatus("Jet_mass", 1);
    tree->SetBranchAddress("Jet_mass", Jet_mass);

    tree->SetBranchStatus("Jet_rawFactor", 1);
    tree->SetBranchAddress("Jet_rawFactor", Jet_rawFactor);

    // Clone the structure of the tree but don't copy the data yet
    TTree* slimmed_tree = tree->CloneTree(0);

Long64_t nEntries = tree->GetEntries();
for (Long64_t i = 0; i < nEntries; ++i) {
    tree->GetEntry(i);
    //bool eventSelected = false;
    //for (int j = 0; j < nGenJet; ++j) { // Assuming nGenJet is the number of GenJets in the event
        //if (GenJet_pt[j] > 80 && GenJet_pt[j] < 100) {
            slimmed_tree->Fill(); // Fill the tree only if the event is selected
            //eventSelected = true;
            //break; // Breaks out of the inner loop if at least one jet meets criteria
        //}
    //}
    /*
        if (eventSelected) {
        
    }
    */

}

    // Write and close files
    slimmed_tree->Write();
    output_file->Close();
    input_file->Close();

    
     }
    return 0;
}
