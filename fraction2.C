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
TH1D *h_sall_three = (TH1D*)file->Get("h_sall_three");
TH1D *h_s5_three = (TH1D*)file->Get("h_s5_three");

TH1D *h_k0l2 = (TH1D*)file->Get("h_k0l2");
TH1D *h_k0s2 = (TH1D*)file->Get("h_k0s2");
TH1D *h_kp2 = (TH1D*)file->Get("h_kp2");
//TH1D *h_k02 = (TH1D*)file->Get("h_k02");
TH1D *h_pionp2 = (TH1D*)file->Get("h_pionp2");
TH1D *h_pion02 = (TH1D*)file->Get("h_pion02");
TH1D *h_lambda2 = (TH1D*)file->Get("h_lambda2");
TH1D *h_sigma02 = (TH1D*)file->Get("h_sigma02");
TH1D *h_duall_three = (TH1D*)file->Get("h_duall_three");
TH1D *h_du5_three = (TH1D*)file->Get("h_du5_three");



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
TH1D *hrs5 = (TH1D*)h_s5_three->Clone("hrs5");

TH1D *hrk0l2 = (TH1D*)h_k0l2->Clone("hrk0l2");
TH1D *hrk0s2 = (TH1D*)h_k0s2->Clone("hrk0s2");
TH1D *hrkp2 = (TH1D*)h_kp2->Clone("hrkp2");
//TH1D *hrk02 = (TH1D*)h_k02->Clone("hrk02");
TH1D *hrlambda2 = (TH1D*)h_lambda2->Clone("hrlambda2");
TH1D *hrsigma02 = (TH1D*)h_sigma02->Clone("hrsigma02");
TH1D *hrpionp2 = (TH1D*)h_pionp2->Clone("hrpionp2");
TH1D *hrpion02 = (TH1D*)h_pion02->Clone("hrpion02");
TH1D *hrdu5 = (TH1D*)h_du5_three->Clone("hrdu5");

hrk0l->Divide(h_sall_three);
hrk0s->Divide(h_sall_three);
hrkp->Divide(h_sall_three);
//hrk0->Divide(h_sall);
hrlambda->Divide(h_sall_three);
hrsigma0->Divide(h_sall_three);
hrpionp->Divide(h_sall_three);
hrpion0->Divide(h_sall_three);
hrs5->Divide(h_sall_three);

hrk0l2->Divide(h_duall_three);
hrk0s2->Divide(h_duall_three);
hrkp2->Divide(h_duall_three);
//hrk02->Divide(h_duall_three);
hrlambda2->Divide(h_duall_three);
hrsigma02->Divide(h_duall_three);
hrpionp2->Divide(h_duall_three);
hrpion02->Divide(h_duall_three);
hrdu5->Divide(h_duall_three);

// Create a stack
//setTDRStyle();
//lumi_136TeV = "Run3";
//extraText = "Private";
//TH1D *h1 = tdrHist("h","Jet p_{T} fraction (S-U)",-0.06 + 1e-4,0.10 -1e-4,"p_{T,cand} (GeV)",0.1,100);
//TCanvas *c1 = tdrCanvas("c1",h1,8,kSquare);
//c1->SetLogx();
THStack *hs = new THStack("hs", "; p_{T,cand} (GeV); S Jet p_{T} fraction");
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
TCanvas *c1 = new TCanvas("c1", "Pt fractions for S", 800, 600);
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
c1->SaveAs("pdf/fractions2S.pdf");


THStack *hdu = new THStack("hdu", "; p_{T,cand} (GeV); U & D Jet p_{T} fraction");
//hs->GetXaxis()->SetTitleSize(0.05);
//hs->GetYaxis()->SetTitleSize(0.05);
//hs->GetXaxis()->SetTitleOffset(1.2);
//hs->GetYaxis()->SetTitleOffset(1.2);

// Set histogram fill colors and add to stack
hrdu5->SetFillColor(kBlue-9);
hrk0l2->SetFillColor(kOrange-3);
hrk0s2->SetFillColor(kRed-7);
hrkp2->SetFillColor(kOrange-2);
//hrk02->SetFillColor(kOrange);
hrlambda2->SetFillColor(kAzure+7);
hrpionp2->SetFillColor(kGreen-6);
hrpion02->SetFillColor(kViolet-4);
hrsigma02->SetFillColor(kPink+6);


// Add histograms to the stack
hdu->Add(hrk0s2);
hdu->Add(hrk0l2);
hdu->Add(hrkp2);
//hdu->Add(hrk02);
hdu->Add(hrpionp2);
hdu->Add(hrlambda2);
hdu->Add(hrpion02);
hdu->Add(hrsigma02);
hdu->Add(hrdu5);

// Draw the stack
TCanvas *c2 = new TCanvas("c2", "Pt fractions for S", 800, 600);
c2->SetLogx();
hdu->Draw("hist");

gPad->SetBottomMargin(0.14);
gPad->Update();
TH1 *h2 = hdu->GetHistogram();
h2->GetXaxis()->SetTitleSize(0.06);
h2->GetXaxis()->SetTitleOffset(1.07);
h2->GetYaxis()->SetTitleSize(0.06);
h2->GetYaxis()->SetTitleOffset(0.7);
h2->GetXaxis()->SetLabelSize(0.05); 
h2->GetYaxis()->SetLabelSize(0.05); 

// Create legend
TLegend *leg2 = tdrLeg(0.9,0.79-0.025*8,1.1,0.9);
leg2->AddEntry(hrdu5, "#gamma", "f");
leg2->AddEntry(hrlambda2, "#Lambda", "f");
leg2->AddEntry(hrpionp2, "#pi^{+/-}", "f");
leg2->AddEntry(hrkp2, "K^{+/-}", "f");
leg2->AddEntry(hrk0l2, "K^{0}_{L}", "f");
leg2->AddEntry(hrk0s2, "K^{0}_{S}", "f");
//leg2->AddEntry(hrk02, "K^0", "f");
leg2->AddEntry(hrsigma02, "#Sigma^{0}", "f");
leg2->AddEntry(hrpion02, "#pi^{0}", "f");
leg2->SetTextFont(132);
leg2->SetTextSize(0.03);
leg2->Draw();

TLatex *tex21 = new TLatex();
tex21->SetNDC(); tex21->SetTextSize(0.035);
tex21->DrawLatex(0.15,0.77,"|#eta| < 1.3");
tex21->DrawLatex(0.15,0.72,"60 < p_{T,jet} < 140 GeV");

TLatex *tex22 = new TLatex();
tex22->SetNDC(); tex22->SetTextSize(0.065);
tex22->DrawLatex(0.1,0.92,"CMS");

TLatex *tex23 = new TLatex();
tex23->SetNDC(); tex23->SetTextSize(0.05);
tex23->SetTextFont(42);
tex23->DrawLatex(0.65,0.92,"Run3 (13.6 TeV)");

TLatex *tex24 = new TLatex();
tex24->SetNDC(); tex24->SetTextSize(0.045);
tex24->SetTextFont(52);
tex24->DrawLatex(0.15,0.83,"Private");
// Assuming the x-axis categories are correctly set when histograms were created
// If you need to set labels for the x-axis categories, do it here

// Update the canvas to reflect changes
c2->RedrawAxis();
c2->Modified();
c2->Update();
c2->SaveAs("pdf/fractions2UD.pdf");

// Do not close the file if you want to interact with the histograms further
// file->Close(); // Uncomment this if you're done with the file
}