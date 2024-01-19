#include <TH1.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include "tdrstyle_mod22.C"

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
TH1D *h_sall_new = (TH1D*)file->Get("h_sall_new");
TH1D *h_s5_new = (TH1D*)file->Get("h_s5_new");


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
TH1D *hrs5 = (TH1D*)h_s5_new->Clone("hrs5");

hrk0l->Divide(h_sall_new);
hrk0s->Divide(h_sall_new);
hrkp->Divide(h_sall_new);
//hrk0->Divide(h_sall);
hrlambda->Divide(h_sall_new);
hrsigma0->Divide(h_sall_new);
hrpionp->Divide(h_sall_new);
hrpion0->Divide(h_sall_new);
hrs5->Divide(h_sall_new);

// Create a stack
//setTDRStyle();
//lumi_136TeV = "Run3";
//extraText = "Private";
//TH1D *h1 = tdrHist("h","Jet p_{T} fraction (S-U)",-0.06 + 1e-4,0.10 -1e-4,"p_{T,cand} (GeV)",0.1,100);
//TCanvas *c1 = tdrCanvas("c1",h1,8,kSquare);
//c1->SetLogx();
THStack *hs = new THStack("hs", "; p_{T,cand} (GeV); Jet p_{T} fraction");
//hs->GetXaxis()->SetTitleSize(0.05);
//hs->GetYaxis()->SetTitleSize(0.05);
//hs->GetXaxis()->SetTitleOffset(1.2);
//hs->GetYaxis()->SetTitleOffset(1.2);

// Set histogram fill colors and add to stack
hrs5->SetFillColor(kBlue-9);
hrk0l->SetFillColor(kOrange-3);
hrk0s->SetFillColor(kRed-7);
hrkp->SetFillColor(kOrange-2);
//hrk0->SetFillColor(kOrange);
hrlambda->SetFillColor(kAzure+7);
hrpionp->SetFillColor(kGreen-6);
hrpion0->SetFillColor(kViolet-4);
hrsigma0->SetFillColor(kPink+6);


// Add histograms to the stack
hs->Add(hrk0s);
hs->Add(hrk0l);
hs->Add(hrkp);
//hs->Add(hrk0);
hs->Add(hrpionp);
hs->Add(hrlambda);
hs->Add(hrpion0);
hs->Add(hrsigma0);
hs->Add(hrs5);

// Draw the stack
TCanvas *c1 = new TCanvas("c2", "Pt fractions for S", 800, 600);
c1->SetLogx();
hs->Draw("hist");

gPad->SetBottomMargin(0.14);
gPad->Update();
TH1 *h = hs->GetHistogram();
h->GetXaxis()->SetTitleSize(0.06);
h->GetXaxis()->SetTitleOffset(1.07);
h->GetYaxis()->SetTitleSize(0.06);
h->GetYaxis()->SetTitleOffset(0.7);
h->GetXaxis()->SetLabelSize(0.05); 
h->GetYaxis()->SetLabelSize(0.05); 

// Create legend
TLegend *leg = tdrLeg(0.9,0.79-0.025*8,1.1,0.9);
leg->AddEntry(hrs5, "#gamma", "f");
leg->AddEntry(hrlambda, "#Lambda", "f");
leg->AddEntry(hrpionp, "#pi^{+/-}", "f");
leg->AddEntry(hrkp, "K^{+/-}", "f");
leg->AddEntry(hrk0l, "K^{0}_{L}", "f");
leg->AddEntry(hrk0s, "K^{0}_{S}", "f");
//leg->AddEntry(hrk0, "K^0", "f");
leg->AddEntry(hrsigma0, "#Sigma^{0}", "f");
leg->AddEntry(hrpion0, "#pi^{0}", "f");
leg->SetTextFont(132);
leg->SetTextSize(0.03);
leg->Draw();

TLatex *tex1 = new TLatex();
tex1->SetNDC(); tex1->SetTextSize(0.035);
tex1->DrawLatex(0.15,0.77,"|#eta| < 1.3");
tex1->DrawLatex(0.15,0.72,"60 < p_{T,jet} < 140 GeV");

TLatex *tex2 = new TLatex();
tex2->SetNDC(); tex2->SetTextSize(0.065);
tex2->DrawLatex(0.1,0.92,"CMS");

TLatex *tex3 = new TLatex();
tex3->SetNDC(); tex3->SetTextSize(0.05);
tex3->SetTextFont(42);
tex3->DrawLatex(0.65,0.92,"Run3 (13.6 TeV)");

TLatex *tex4 = new TLatex();
tex4->SetNDC(); tex4->SetTextSize(0.045);
tex4->SetTextFont(52);
tex4->DrawLatex(0.15,0.83,"Private");
// Assuming the x-axis categories are correctly set when histograms were created
// If you need to set labels for the x-axis categories, do it here

// Update the canvas to reflect changes
c1->RedrawAxis();
c1->Modified();
c1->Update();
c1->SaveAs("pdf/fractionsS.pdf");

// Do not close the file if you want to interact with the histograms further
// file->Close(); // Uncomment this if you're done with the file
}