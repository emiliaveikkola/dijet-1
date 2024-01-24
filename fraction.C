#include <TH1.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include "tdrstyle_mod22.C"

void fraction() {
// Open the ROOT file containing the histograms
TFile *file = new TFile("output.root", "READ");
// Retrieve the histograms
TH1D *h_s_three = (TH1D*)file->Get("h_s_three");
TH1D *h_s3_three = (TH1D*)file->Get("h_s3_three");
TH1D *h_s5_three = (TH1D*)file->Get("h_s5_three");
TH1D *h_sall_three = (TH1D*)file->Get("h_sall_three");

TH1D *h_d_three = (TH1D*)file->Get("h_d_three");
TH1D *h_d3_three = (TH1D*)file->Get("h_d3_three");
TH1D *h_d5_three = (TH1D*)file->Get("h_d5_three");
TH1D *h_dall_three = (TH1D*)file->Get("h_dall_three");

TH1D *h_u_three = (TH1D*)file->Get("h_u_three");
TH1D *h_u3_three = (TH1D*)file->Get("h_u3_three");
TH1D *h_u5_three = (TH1D*)file->Get("h_u5_three");
TH1D *h_uall_three = (TH1D*)file->Get("h_uall_three");


// Normalize the histograms to percentages
/*int nSjet = h_s_three->GetEntries();
int nS3jet = h_s3_three->GetEntries();
int nS5jet = h_s5_three->GetEntries();
int nSall = h_sall_three->GetEntries();

h_s->Scale(1./nSjet);
h_s3->Scale(1./nS3jet);
h_s5->Scale(1./nS5jet);
h_sall->Scale(1./nSall);

h_s->Scale(1,"width");
h_s3->Scale(1,"width");
h_s5->Scale(1,"width");
h_sall->Scale(1,"width");*/

TH1D *hrs = (TH1D*)h_s_three->Clone("hrs");
TH1D *hrs3 = (TH1D*)h_s3_three->Clone("hrs3");
TH1D *hrs5 = (TH1D*)h_s5_three->Clone("hrs5");

TH1D *hru = (TH1D*)h_u_three->Clone("hru");
TH1D *hru3 = (TH1D*)h_u3_three->Clone("hru3");
TH1D *hru5 = (TH1D*)h_u5_three->Clone("hru5");

TH1D *hrd = (TH1D*)h_d_three->Clone("hrd");
TH1D *hrd3 = (TH1D*)h_d3_three->Clone("hrd3");
TH1D *hrd5 = (TH1D*)h_d5_three->Clone("hrd5");

/*hrs->Sumw2();
hrs3->Sumw2();
hrs5->Sumw2();*/

hrs->Divide(h_s_three,h_sall_three,1,1,"b");
hrs3->Divide(h_s3_three,h_sall_three,1,1,"b");
hrs5->Divide(h_s5_three,h_sall_three,1,1,"b");

hru->Divide(h_u_three,h_uall_three,1,1,"b");
hru3->Divide(h_u3_three,h_uall_three,1,1,"b");
hru5->Divide(h_u5_three,h_uall_three,1,1,"b");

hrd->Divide(h_d_three,h_dall_three,1,1,"b");
hrd3->Divide(h_d3_three,h_dall_three,1,1,"b");
hrd5->Divide(h_d5_three,h_dall_three,1,1,"b");

// Create a stack
THStack *hs = new THStack("hs", "; p_{T,cand}; S N fraction");

// Set histogram fill colors and add to stack
hrs->SetFillColor(625);
hrs5->SetFillColor(410);
hrs3->SetFillColor(593);

// Add histograms to the stack
hs->Add(hrs);
hs->Add(hrs3);
hs->Add(hrs5);

// Draw the stack
// Draw the stack
TCanvas *c1 = new TCanvas("c1", "p_{T} fractions", 800, 600);
c1->SetLogx();
hs->Draw("hist");

gPad->SetBottomMargin(0.14);
gPad->SetRightMargin(0.17);
gPad->Update();

TH1 *h1 = hs->GetHistogram();
h1->GetXaxis()->SetTitleSize(0.06);
h1->GetXaxis()->SetTitleOffset(1.07);
h1->GetYaxis()->SetTitleSize(0.06);
h1->GetYaxis()->SetTitleOffset(0.7);
h1->GetXaxis()->SetLabelSize(0.05); 
h1->GetYaxis()->SetLabelSize(0.05); 

// Create legend
TLegend *leg1 = tdrLeg(0.83,0.8-0.06*3,1.05,0.9);
leg1->AddEntry(hrs5, "Photons", "f");
leg1->AddEntry(hrs3, "#splitline{Neutral}{Hadrons}", "f");
leg1->AddEntry(hrs, "#splitline{Charged}{Hadrons}", "f");
leg1->SetTextSize(0.04);
leg1->Draw();

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
tex3->DrawLatex(0.61,0.92,"Run3 (13.6 TeV)");

TLatex *tex4 = new TLatex();
tex4->SetNDC(); tex4->SetTextSize(0.045);
tex4->SetTextFont(52);
tex4->DrawLatex(0.15,0.83,"Private");

// Update the canvas to reflect changes
c1->RedrawAxis();
c1->Modified();
c1->Update();
c1->SaveAs("pdf/fractionsS.pdf");


// Create a stack
THStack *hu = new THStack("hu", "; p_{T,cand}; U Jet N fraction");

// Set histogram fill colors and add to stack
hru->SetFillColor(625);
hru5->SetFillColor(410);
hru3->SetFillColor(593);

// Add histograms to the stack
hu->Add(hru);
hu->Add(hru3);
hu->Add(hru5);

// Draw the stack
TCanvas *c2 = new TCanvas("c2", "p_{T} fractions", 800, 600);
c2->SetLogx();
hu->Draw("hist");

gPad->SetBottomMargin(0.14);
gPad->SetRightMargin(0.17);
gPad->Update();

TH1 *h2 = hu->GetHistogram();
h2->GetXaxis()->SetTitleSize(0.06);
h2->GetXaxis()->SetTitleOffset(1.07);
h2->GetYaxis()->SetTitleSize(0.06);
h2->GetYaxis()->SetTitleOffset(0.7);
h2->GetXaxis()->SetLabelSize(0.05); 
h2->GetYaxis()->SetLabelSize(0.05); 

// Create legend
TLegend *leg2 = tdrLeg(0.83,0.8-0.06*3,1.05,0.9);
leg2->AddEntry(hru5, "Photons", "f");
leg2->AddEntry(hru3, "#splitline{Neutral}{Hadrons}", "f");
leg2->AddEntry(hru, "#splitline{Charged}{Hadrons}", "f");
leg2->SetTextSize(0.04);
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
tex23->DrawLatex(0.61,0.92,"Run3 (13.6 TeV)");

TLatex *tex24 = new TLatex();
tex24->SetNDC(); tex24->SetTextSize(0.045);
tex24->SetTextFont(52);
tex24->DrawLatex(0.15,0.83,"Private");
// Update the canvas to reflect changes
c2->RedrawAxis();
c2->Modified();
c2->Update();
c2->SaveAs("pdf/fractionsU.pdf");


// Create a stack
THStack *hd = new THStack("hd", "; p_{T,cand}; D Jet N fraction");

// Set histogram fill colors and add to stack
hrd->SetFillColor(625);
hrd5->SetFillColor(410);
hrd3->SetFillColor(593);

// Add histograms to the stack
hd->Add(hrd);
hd->Add(hrd3);
hd->Add(hrd5);

TCanvas *c3 = new TCanvas("c3", "p_{T} fractions", 800, 600);
c3->SetLogx();
hd->Draw("hist");

gPad->SetBottomMargin(0.14);
gPad->SetRightMargin(0.17);
gPad->Update();

TH1 *h3 = hd->GetHistogram();
h3->GetXaxis()->SetTitleSize(0.06);
h3->GetXaxis()->SetTitleOffset(1.07);
h3->GetYaxis()->SetTitleSize(0.06);
h3->GetYaxis()->SetTitleOffset(0.7);
h3->GetXaxis()->SetLabelSize(0.05); 
h3->GetYaxis()->SetLabelSize(0.05); 

// Create legend
TLegend *leg3 = tdrLeg(0.83,0.8-0.06*3,1.05,0.9);
leg3->AddEntry(hrd5, "Photons", "f");
leg3->AddEntry(hrd3, "#splitline{Neutral}{Hadrons}", "f");
leg3->AddEntry(hrd, "#splitline{Charged}{Hadrons}", "f");
leg3->SetTextSize(0.04);
leg3->Draw();

TLatex *tex31 = new TLatex();
tex31->SetNDC(); tex31->SetTextSize(0.035);
tex31->DrawLatex(0.15,0.77,"|#eta| < 1.3");
tex31->DrawLatex(0.15,0.72,"60 < p_{T,jet} < 140 GeV");

TLatex *tex32 = new TLatex();
tex32->SetNDC(); tex32->SetTextSize(0.065);
tex32->DrawLatex(0.1,0.92,"CMS");

TLatex *tex33 = new TLatex();
tex33->SetNDC(); tex33->SetTextSize(0.05);
tex33->SetTextFont(42);
tex33->DrawLatex(0.61,0.92,"Run3 (13.6 TeV)");

TLatex *tex34 = new TLatex();
tex34->SetNDC(); tex34->SetTextSize(0.045);
tex34->SetTextFont(52);
tex34->DrawLatex(0.15,0.83,"Private");

// Update the canvas to reflect changes
c3->RedrawAxis();
c3->Modified();
c3->Update();
c3->SaveAs("pdf/fractionsD.pdf");


// Do not close the file if you want to interact with the histograms further
// file->Close(); // Uncomment this if you're done with the file
}