#include <TH1.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>

void fraction() {
// Open the ROOT file containing the histograms
TFile *file = new TFile("output.root", "READ");
// Retrieve the histograms
TH1D *h_s_new = (TH1D*)file->Get("h_s_new");
TH1D *h_s3_new = (TH1D*)file->Get("h_s3_new");
TH1D *h_s5_new = (TH1D*)file->Get("h_s5_new");
TH1D *h_sall_new = (TH1D*)file->Get("h_sall_new");

// Normalize the histograms to percentages
int nSjet = h_s_new->GetEntries();
int nS3jet = h_s3_new->GetEntries();
int nS5jet = h_s5_new->GetEntries();
int nSall = h_sall_new->GetEntries();

/*h_s->Scale(1./nSjet);
h_s3->Scale(1./nS3jet);
h_s5->Scale(1./nS5jet);
h_sall->Scale(1./nSall);*/

/*h_s->Scale(1,"width");
h_s3->Scale(1,"width");
h_s5->Scale(1,"width");
h_sall->Scale(1,"width");*/

TH1D *hrs = (TH1D*)h_s_new->Clone("hrs");
TH1D *hrs3 = (TH1D*)h_s3_new->Clone("hrs3");
TH1D *hrs5 = (TH1D*)h_s5_new->Clone("hrs5");

/*hrs->Sumw2();
hrs3->Sumw2();
hrs5->Sumw2();*/

hrs->Divide(h_s_new,h_sall_new,1,1,"b");
hrs3->Divide(h_s3_new,h_sall_new,1,1,"b");
hrs5->Divide(h_s5_new,h_sall_new,1,1,"b");

// Create a stack
THStack *hs = new THStack("hs", "Pt fraction for S; PtCand; Jet pt fraction");

// Set histogram fill colors and add to stack
hrs->SetFillColor(625);
hrs5->SetFillColor(410);
hrs3->SetFillColor(593);

// Add histograms to the stack
hs->Add(hrs);
hs->Add(hrs3);
hs->Add(hrs5);

// Draw the stack
TCanvas *c1 = new TCanvas("c1", "Pt fractions", 800, 600);
c1->SetLogx();
hs->Draw("HISTE");

// Create legend
TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
legend->AddEntry(hrs5, "Photons", "f");
legend->AddEntry(hrs3, "Neutral Hadrons", "f");
legend->AddEntry(hrs, "Charged Hadrons", "f");
legend->Draw();
// Assuming the x-axis categories are correctly set when histograms were created
// If you need to set labels for the x-axis categories, do it here

// Update the canvas to reflect changes
c1->Modified();
c1->Update();

// Do not close the file if you want to interact with the histograms further
// file->Close(); // Uncomment this if you're done with the file
}