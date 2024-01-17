#include <TH1.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include <TColor.h>
#include "tdrstyle_mod22.C"

void differenceSU() {
// Open the ROOT file containing the histograms
TFile *file = new TFile("output.root", "READ");
// Retrieve the histograms
TH1D *h_u_new = (TH1D*)file->Get("h_u_new");
TH1D *h_u3_new = (TH1D*)file->Get("h_u3_new");
TH1D *h_u5_new = (TH1D*)file->Get("h_u5_new");
TH1D *h_uall_new = (TH1D*)file->Get("h_uall_new");

TH1D *h_s_new = (TH1D*)file->Get("h_s_new");
TH1D *h_s3_new = (TH1D*)file->Get("h_s3_new");
TH1D *h_s5_new = (TH1D*)file->Get("h_s5_new");
TH1D *h_sall_new = (TH1D*)file->Get("h_sall_new");


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

TH1D *hrs = (TH1D*)h_s_new->Clone("hrs");
TH1D *hrs3 = (TH1D*)h_s3_new->Clone("hrs3");
TH1D *hrs5 = (TH1D*)h_s5_new->Clone("hrs5");

hru->Divide(h_u_new,h_uall_new,1,1,"b");
hru3->Divide(h_u3_new,h_uall_new,1,1,"b");
hru5->Divide(h_u5_new,h_uall_new,1,1,"b");

hrs->Divide(h_s_new,h_sall_new,1,1,"b");
hrs3->Divide(h_s3_new,h_sall_new,1,1,"b");
hrs5->Divide(h_s5_new,h_sall_new,1,1,"b");

// Set histogram fill colors and add to stack
hru->SetFillColor(625);
hru5->SetFillColor(410);
hru3->SetFillColor(593);

hrs->SetFillColor(625);
hrs5->SetFillColor(410);
hrs3->SetFillColor(593);

// Add histograms to the stack
hrs->Add(hru, -1);
hrs3->Add(hru3, -1);
hrs5->Add(hru5, -1);

/*// Create a stack
THStack *hs_u = new THStack("hs_u", "Pt fraction for S-U; PtCand; Jet pt fraction");

hs_u->Add(hrs);
hs_u->Add(hrs3);
hs_u->Add(hrs5);*/

// Draw the stack
//TCanvas *c1 = new TCanvas("c1", "Pt fractions", 800, 600);
setTDRStyle();
lumi_136TeV = "Run3";
extraText = "Private";
TH1D *h = tdrHist("h","Jet p_{T} fraction (S-U)",-0.06 + 1e-4,0.10 -1e-4,"p_{T,cand} (GeV)",0.1,100);
TCanvas *c1 = tdrCanvas("c1",h,8,kSquare);
c1->SetLogx();
//hrs->SetFillStyle(kNone);
//hrs->Draw("histe");
tdrDraw(hrs,"histe",kFullSquare,kRed,kSolid,-1,kNone);
hrs->SetMarkerSize(1.5);
//hrs3->SetFillStyle(kNone);
//hrs3->Draw("histe same");
tdrDraw(hrs3,"histe",kFullCircle,kGreen+2,kSolid,-1,kNone);
hrs3->SetMarkerSize(1.5);


//hrs5->SetFillStyle(kNone);
//hrs5->Draw("histe same");
tdrDraw(hrs5,"histe",kFullDiamond,kBlue,kSolid,-1,kNone);
hrs5->SetMarkerSize(1.75);


// Create legend
//TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
TLegend *leg = tdrLeg(0.5,0.9-0.05*3,0.75,0.9);
leg->AddEntry(hrs5, "Photons", "ple");
leg->AddEntry(hrs3, "Neutral Hadrons", "ple");
leg->AddEntry(hrs, "Charged Hadrons", "ple");
leg->Draw();

TLatex *tex = new TLatex();
tex->SetNDC(); tex->SetTextSize(0.045);
tex->DrawLatex(0.17,0.8,"|#eta| < 1.3");
tex->DrawLatex(0.17,0.75,"60 < p_{T,jet} < 140 GeV");
// Assuming the x-axis categories are correctly set when histograms were created
// If you need to set labels for the x-axis categories, do it here

// Update the canvas to reflect changes
c1->RedrawAxis();
c1->Modified();
c1->Update();
c1->SaveAs("pdf/differenceSU_c1.pdf");
//c1->SetLogx(0);
c1->SaveAs("pdf/differenceSU_c2.pdf");
// Do not close the file if you want to interact with the histograms further
// file->Close(); // Uncomment this if you're done with the file
}