#include <TH1.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include <TColor.h>

void fraction_u() {
// Open the ROOT file containing the histograms
TFile *file = new TFile("output.root", "READ");
// Retrieve the histograms
TH1D *h_u_new = (TH1D*)file->Get("h_u_new");
TH1D *h_u3_new = (TH1D*)file->Get("h_u3_new");
TH1D *h_u5_new = (TH1D*)file->Get("h_u5_new");
TH1D *h_uall_new = (TH1D*)file->Get("h_uall_new");

// Normalize the histograms to percentages
int nUjet = h_u_new->GetEntries();
int nU3jet = h_u3_new->GetEntries();
int nU5jet = h_u5_new->GetEntries();
int nUall = h_uall_new->GetEntries();

/*h_s->Scale(1./nSjet);
h_s3->Scale(1./nS3jet);
h_s5->Scale(1./nS5jet);
h_sall->Scale(1./nSall);*/

/*h_s->Scale(1,"width");
h_s3->Scale(1,"width");
h_s5->Scale(1,"width");
h_sall->Scale(1,"width");*/

TH1D *hru = (TH1D*)h_u_new->Clone("hru");
TH1D *hru3 = (TH1D*)h_u3_new->Clone("hru3");
TH1D *hru5 = (TH1D*)h_u5_new->Clone("hru5");

hru->Divide(h_u_new,h_uall_new,1,1,"b");
hru3->Divide(h_u3_new,h_uall_new,1,1,"b");
hru5->Divide(h_u5_new,h_uall_new,1,1,"b");

// Create a stack
THStack *hu = new THStack("hu", "Pt fraction for U; PtCand; Jet pt fraction");

// Set histogram fill colors and add to stack
hru->SetFillColor(625);
hru5->SetFillColor(410);
hru3->SetFillColor(593);

// Add histograms to the stack
hu->Add(hru);
hu->Add(hru3);
hu->Add(hru5);

// Draw the stack
TCanvas *c1 = new TCanvas("c1", "Pt fractions", 800, 600);
c1->SetLogx();
hu->Draw("histe");

// Create legend
TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
legend->AddEntry(hru5, "Photons", "f");
legend->AddEntry(hru3, "Neutral Hadrons", "f");
legend->AddEntry(hru, "Charged Hadrons", "f");
legend->Draw();
// Assuming the x-axis categories are correctly set when histograms were created
// If you need to set labels for the x-axis categories, do it here

// Update the canvas to reflect changes
c1->Modified();
c1->Update();

// Do not close the file if you want to interact with the histograms further
// file->Close(); // Uncomment this if you're done with the file
}