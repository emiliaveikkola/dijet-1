#include <TH1.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>

void fraction_d() {
// Open the ROOT file containing the histograms
TFile *file = new TFile("output.root", "READ");
// Retrieve the histograms
TH1D *h_d_new = (TH1D*)file->Get("h_d_new");
TH1D *h_d3_new = (TH1D*)file->Get("h_d3_new");
TH1D *h_d5_new = (TH1D*)file->Get("h_d5_new");
TH1D *h_dall_new = (TH1D*)file->Get("h_dall_new");

// Normalize the histograms to percentages
int nDjet = h_d_new->GetEntries();
int nD3jet = h_d3_new->GetEntries();
int nD5jet = h_d5_new->GetEntries();
int nDall = h_dall_new->GetEntries();

/*h_s->Scale(1./nSjet);
h_s3->Scale(1./nS3jet);
h_s5->Scale(1./nS5jet);
h_sall->Scale(1./nSall);*/

/*h_s->Scale(1,"width");
h_s3->Scale(1,"width");
h_s5->Scale(1,"width");
h_sall->Scale(1,"width");*/

TH1D *hrd = (TH1D*)h_d_new->Clone("hrd");
TH1D *hrd3 = (TH1D*)h_d3_new->Clone("hrd3");
TH1D *hrd5 = (TH1D*)h_d5_new->Clone("hrd5");

hrd->Divide(h_d_new,h_dall_new,1,1,"b");
hrd3->Divide(h_d3_new,h_dall_new,1,1,"b");
hrd5->Divide(h_d5_new,h_dall_new,1,1,"b");

// Create a stack
THStack *hd = new THStack("hd", "Pt fraction for D; PtCand; Jet pt fraction");

// Set histogram fill colors and add to stack
hrd->SetFillColor(625);
hrd5->SetFillColor(410);
hrd3->SetFillColor(593);

// Add histograms to the stack
hd->Add(hrd);
hd->Add(hrd3);
hd->Add(hrd5);

// Draw the stack
TCanvas *c1 = new TCanvas("c1", "Pt fractions", 800, 600);
c1->SetLogx();
hd->Draw("histe");

// Create legend
TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
legend->AddEntry(hrd5, "Photons", "f");
legend->AddEntry(hrd3, "Neutral Hadrons", "f");
legend->AddEntry(hrd, "Charged Hadrons", "f");

legend->Draw();
// Assuming the x-axis categories are correctly set when histograms were created
// If you need to set labels for the x-axis categories, do it here

// Update the canvas to reflect changes
c1->Modified();
c1->Update();

// Do not close the file if you want to interact with the histograms further
// file->Close(); // Uncomment this if you're done with the file
}