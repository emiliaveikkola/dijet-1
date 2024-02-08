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
TH1D *h_s_round = (TH1D*)file->Get("h_s_round");
TH1D *h_s3_round = (TH1D*)file->Get("h_s3_round");
TH1D *h_s5_round = (TH1D*)file->Get("h_s5_round");
TH1D *h_sall_round = (TH1D*)file->Get("h_sall_round");

TH1D *h_d_round = (TH1D*)file->Get("h_d_round");
TH1D *h_d3_round = (TH1D*)file->Get("h_d3_round");
TH1D *h_d5_round = (TH1D*)file->Get("h_d5_round");
TH1D *h_dall_round = (TH1D*)file->Get("h_dall_round");

TH1D *h_u_round = (TH1D*)file->Get("h_u_round");
TH1D *h_u3_round = (TH1D*)file->Get("h_u3_round");
TH1D *h_u5_round = (TH1D*)file->Get("h_u5_round");
TH1D *h_uall_round = (TH1D*)file->Get("h_uall_round");


// Normalize the histograms to percentages
/*int nSjet = h_s_round->GetEntries();
int nS3jet = h_s3_round->GetEntries();
int nS5jet = h_s5_round->GetEntries();
int nSall = h_sall_round->GetEntries();

h_s->Scale(1./nSjet);
h_s3->Scale(1./nS3jet);
h_s5->Scale(1./nS5jet);
h_sall->Scale(1./nSall);

h_s->Scale(1,"width");
h_s3->Scale(1,"width");
h_s5->Scale(1,"width");
h_sall->Scale(1,"width");*/

TH1D *hrs = (TH1D*)h_s_round->Clone("hrs");
TH1D *hrs3 = (TH1D*)h_s3_round->Clone("hrs3");
TH1D *hrs5 = (TH1D*)h_s5_round->Clone("hrs5");

TH1D *hru = (TH1D*)h_u_round->Clone("hru");
TH1D *hru3 = (TH1D*)h_u3_round->Clone("hru3");
TH1D *hru5 = (TH1D*)h_u5_round->Clone("hru5");

TH1D *hrd = (TH1D*)h_d_round->Clone("hrd");
TH1D *hrd3 = (TH1D*)h_d3_round->Clone("hrd3");
TH1D *hrd5 = (TH1D*)h_d5_round->Clone("hrd5");

/*hrs->Sumw2();
hrs3->Sumw2();
hrs5->Sumw2();*/

hrs->Divide(h_s_round,h_sall_round,1,1,"b");
hrs3->Divide(h_s3_round,h_sall_round,1,1,"b");
hrs5->Divide(h_s5_round,h_sall_round,1,1,"b");

hru->Divide(h_u_round,h_uall_round,1,1,"b");
hru3->Divide(h_u3_round,h_uall_round,1,1,"b");
hru5->Divide(h_u5_round,h_uall_round,1,1,"b");

hrd->Divide(h_d_round,h_dall_round,1,1,"b");
hrd3->Divide(h_d3_round,h_dall_round,1,1,"b");
hrd5->Divide(h_d5_round,h_dall_round,1,1,"b");

// Create a stack

setTDRStyle();
lumi_136TeV = "Run3";
extraText = "Private";

TH1D *h_1 = tdrHist("h_1","S Jet energy fraction",0 +1e-5,1-1e-4,"p_{T,cand} (GeV)",0.1,100);
TCanvas *c1 = tdrCanvas("c1",h_1,8,kSquare);

TH1D *h_2 = tdrHist("h_2","Data/MC",0,1,"p_{T,cand} (GeV)",0.1,100);
TCanvas *c2 = tdrCanvas("c2",h_2,8,kSquare);

TCanvas *c = tdrDiCanvas("c",h_1,h_2,8,0);

c->cd(1);
gPad->SetLogx();

THStack *hs = new THStack("hs", "; p_{T,cand}; S Jet N fraction");

// Set histogram fill colors and add to stack
hrs->SetFillColor(625);
hrs5->SetFillColor(410);
hrs3->SetFillColor(593);

// Add histograms to the stack
hs->Add(hrs);
hs->Add(hrs3);
hs->Add(hrs5);

hs->Draw("hist same");

// Create legend
TLegend *leg1 = tdrLeg(0.65,0.8-0.06*3,0.95,0.9);
leg1->AddEntry(hrs5, "Photons", "f");
leg1->AddEntry(hrs3, "#splitline{Neutral}{Hadrons}", "f");
leg1->AddEntry(hrs, "#splitline{Charged}{Hadrons}", "f");
leg1->SetTextSize(0.04);
leg1->Draw();

gPad->RedrawAxis();
c->cd(2);
gPad->SetLogx();

THStack *hu = new THStack("hu", "; p_{T,cand}; U Jet N fraction");

// Set histogram fill colors and add to stack
hru->SetFillColor(625);
hru5->SetFillColor(410);
hru3->SetFillColor(593);

// Add histograms to the stack
hu->Add(hru);
hu->Add(hru3);
hu->Add(hru5);

hu->Draw("hist same");

TLegend *leg2 = tdrLeg(0.83,0.8-0.06*3,1.05,0.9);
leg2->AddEntry(hru5, "Photons", "f");
leg2->AddEntry(hru3, "#splitline{Neutral}{Hadrons}", "f");
leg2->AddEntry(hru, "#splitline{Charged}{Hadrons}", "f");
leg2->SetTextSize(0.04);
leg2->Draw();



//hs->Draw("hist same");

c->SetRightMargin(0.17);
gPad->RedrawAxis();
c->Update();

/*
TLatex *tex1 = new TLatex();
tex1->SetNDC(); tex1->SetTextSize(0.045);
tex1->DrawLatex(0.17,0.8,"|#eta| < 1.3");
tex1->DrawLatex(0.17,0.75,"60 < p_{T,jet} < 140 GeV");*/

/*TLatex *tex2 = new TLatex();
tex2->SetNDC(); tex2->SetTextSize(0.065);
tex2->DrawLatex(0.1,0.92,"CMS");

TLatex *tex3 = new TLatex();
tex3->SetNDC(); tex3->SetTextSize(0.05);
tex3->SetTextFont(42);
tex3->DrawLatex(0.61,0.92,"Run3 (13.6 TeV)");

TLatex *tex4 = new TLatex();
tex4->SetNDC(); tex4->SetTextSize(0.045);
tex4->SetTextFont(52);
tex4->DrawLatex(0.15,0.83,"Private");*/

// Update the canvas to reflect changes
c->RedrawAxis();
c->Modified();
c->Update();
c->SaveAs("pdf/fractionsS&U.pdf");

/*
setTDRStyle();
lumi_136TeV = "Run3";
extraText = "Private";

// Create a stack


hu->Draw("hist same");

gPad->SetRightMargin(0.17);
gPad->Update();

// Create legend


TLatex *tex21 = new TLatex();
tex21->SetNDC(); tex21->SetTextSize(0.045);
tex21->DrawLatex(0.17,0.8,"|#eta| < 1.3");
tex21->DrawLatex(0.17,0.75,"60 < p_{T,jet} < 140 GeV");

c2->RedrawAxis();
c2->Modified();
c2->Update();
c2->SaveAs("pdf/fractionsU.pdf");

setTDRStyle();
lumi_136TeV = "Run3";
extraText = "Private";
TH1D *h_3 = tdrHist("h_3","U Jet energy fraction",0,1,"p_{T,genjet} (GeV)",0.1,100);
TCanvas *c3 = tdrCanvas("c3",h_3,8,kSquare);
c3->SetLogx();
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

hd->Draw("hist same");

gPad->SetRightMargin(0.17);
gPad->Update();

// Create legend
TLegend *leg3 = tdrLeg(0.83,0.8-0.06*3,1.05,0.9);
leg3->AddEntry(hrd5, "Photons", "f");
leg3->AddEntry(hrd3, "#splitline{Neutral}{Hadrons}", "f");
leg3->AddEntry(hrd, "#splitline{Charged}{Hadrons}", "f");
leg3->SetTextSize(0.04);
leg3->Draw();

TLatex *tex31 = new TLatex();
tex31->SetNDC(); tex31->SetTextSize(0.045);
tex31->DrawLatex(0.17,0.8,"|#eta| < 1.3");
tex31->DrawLatex(0.17,0.75,"60 < p_{T,jet} < 140 GeV");

c3->RedrawAxis();
c3->Modified();
c3->Update();
c3->SaveAs("pdf/fractionsD.pdf");*/


// Do not close the file if you want to interact with the histograms further
// file->Close(); // Uncomment this if you're done with the file
}