#include <TH1.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>

void fraction2() {
// Open the ROOT file containing the histograms
TFile *file = new TFile("output.root", "READ");
// Retrieve the histograms
TH1D *h_k0l = (TH1D*)file->Get("h_k0l");
TH1D *h_k0s = (TH1D*)file->Get("h_k0s");
TH1D *h_kp = (TH1D*)file->Get("h_kp");
//TH1D *h_k0 = (TH1D*)file->Get("h_k0");
TH1D *h_pionp = (TH1D*)file->Get("h_pionp");
TH1D *h_pion0 = (TH1D*)file->Get("h_pion0");
TH1D *h_lambda = (TH1D*)file->Get("h_lambda");
TH1D *h_sigma0 = (TH1D*)file->Get("h_sigma0");
TH1D *h_sall = (TH1D*)file->Get("h_sall");


// Normalize the histograms to percentages
/*
int nK0L = h_k0l->GetEntries();
int nK0S = h_k0s->GetEntries();
int nKp = h_kp->GetEntries();
int nK0 = h_k0->GetEntries();
int nLambda = h_lambda->GetEntries();
int nSigma0 = h_sigma0->GetEntries();

h_s->Scale(1./nSjet);
h_s3->Scale(1./nS3jet);
h_s5->Scale(1./nS5jet);
h_sall->Scale(1./nSall);*/

/*h_s->Scale(1,"width");
h_s3->Scale(1,"width");
h_s5->Scale(1,"width");
h_sall->Scale(1,"width");
*/

TH1D *hrk0l = (TH1D*)h_k0l->Clone("hrk0l");
TH1D *hrk0s = (TH1D*)h_k0s->Clone("hrk0s");
TH1D *hrkp = (TH1D*)h_kp->Clone("hrkp");
//TH1D *hrk0 = (TH1D*)h_k0->Clone("hrk0");
TH1D *hrlambda = (TH1D*)h_lambda->Clone("hrlambda");
TH1D *hrsigma0 = (TH1D*)h_sigma0->Clone("hrsigma0");
TH1D *hrpionp = (TH1D*)h_pionp->Clone("hrpionp");
TH1D *hrpion0 = (TH1D*)h_pion0->Clone("hrpion0");

hrk0l->Divide(h_sall);
hrk0s->Divide(h_sall);
hrkp->Divide(h_sall);
//hrk0->Divide(h_sall);
hrlambda->Divide(h_sall);
hrsigma0->Divide(h_sall);
hrpionp->Divide(h_sall);
hrpion0->Divide(h_sall);

// Create a stack
THStack *hs = new THStack("hs", "Pt fraction; PtCand; Jet pt fraction");

// Set histogram fill colors and add to stack
hrk0l->SetFillColor(kRed);
hrk0s->SetFillColor(kBlue);
hrkp->SetFillColor(kGreen);
//hrk0->SetFillColor(kOrange);
hrlambda->SetFillColor(kCyan);
hrsigma0->SetFillColor(kMagenta);
hrpionp->SetFillColor(kViolet);
hrpion0->SetFillColor(kOrange);

// Add histograms to the stack
hs->Add(hrk0l);
hs->Add(hrk0s);
hs->Add(hrkp);
//hs->Add(hrk0);
hs->Add(hrlambda);
hs->Add(hrsigma0);
hs->Add(hrpionp);
hs->Add(hrpion0);

// Draw the stack
TCanvas *c1 = new TCanvas("c1", "Pt fractions for S", 800, 600);
hs->Draw("hist");

// Create legend
TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9);
leg->AddEntry(hrk0l, "K^0_L", "f");
leg->AddEntry(hrk0s, "K^0_S", "f");
leg->AddEntry(hrkp, "K^+/-", "f");
//leg->AddEntry(hrk0, "K^0", "f");
leg->AddEntry(hrpionp, "Pi^+/-+", "f");
leg->AddEntry(hrpion0, "Pi^0", "f");
leg->AddEntry(hrlambda, "Lambda", "f");
leg->AddEntry(hrsigma0, "Sigma^0", "f");
leg->Draw();
// Assuming the x-axis categories are correctly set when histograms were created
// If you need to set labels for the x-axis categories, do it here

// Update the canvas to reflect changes
c1->Modified();
c1->Update();

// Do not close the file if you want to interact with the histograms further
// file->Close(); // Uncomment this if you're done with the file
}