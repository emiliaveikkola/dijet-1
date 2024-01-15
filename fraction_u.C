#include <TH1.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>

void fraction_u() {
// Open the ROOT file containing the histograms
TFile *file = new TFile("output.root", "READ");
// Retrieve the histograms
TH1D *h_u = (TH1D*)file->Get("h_s");
TH1D *h_u3 = (TH1D*)file->Get("h_s3");
TH1D *h_u5 = (TH1D*)file->Get("h_s5");
TH1D *h_uall = (TH1D*)file->Get("h_sall");

// Normalize the histograms to percentages
int nUjet = h_u->GetEntries();
int nU3jet = h_u3->GetEntries();
int nU5jet = h_u5->GetEntries();
int nUall = h_uall->GetEntries();

/*h_s->Scale(1./nSjet);
h_s3->Scale(1./nS3jet);
h_s5->Scale(1./nS5jet);
h_sall->Scale(1./nSall);*/

/*h_s->Scale(1,"width");
h_s3->Scale(1,"width");
h_s5->Scale(1,"width");
h_sall->Scale(1,"width");*/

TH1D *hru = (TH1D*)h_u->Clone("hru");
TH1D *hru3 = (TH1D*)h_u3->Clone("hru3");
TH1D *hru5 = (TH1D*)h_u5->Clone("hru5");

hru->Divide(h_uall);
hru3->Divide(h_uall);
hru5->Divide(h_uall);

// Create a stack
THStack *hu = new THStack("hu", "Pt fraction; PtCand; Jet pt fraction");

// Set histogram fill colors and add to stack
hru->SetFillColor(kRed);
hru3->SetFillColor(kBlue);
hru5->SetFillColor(kGreen);

// Add histograms to the stack
hu->Add(hru);
hu->Add(hru3);
hu->Add(hru5);

// Draw the stack
TCanvas *c1 = new TCanvas("c1", "Pt fractions", 800, 600);
hu->Draw("hist");

// Create legend
TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
legend->AddEntry(hru, "Charged Hadrons", "f");
legend->AddEntry(hru3, "Neutral Hadrons", "f");
legend->AddEntry(hru5, "Photons", "f");
legend->Draw();
// Assuming the x-axis categories are correctly set when histograms were created
// If you need to set labels for the x-axis categories, do it here

// Update the canvas to reflect changes
c1->Modified();
c1->Update();

// Do not close the file if you want to interact with the histograms further
// file->Close(); // Uncomment this if you're done with the file
}