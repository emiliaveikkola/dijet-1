#include <TH1.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include <TColor.h>
#include "tdrstyle_mod22.C"

void difference() {
// Open the ROOT file containing the histograms
TFile *file = new TFile("output.root", "READ");
// Retrieve the histograms
TH1D *h_u_three = (TH1D*)file->Get("h_u_three");
TH1D *h_u3_three = (TH1D*)file->Get("h_u3_three");
TH1D *h_u5_three = (TH1D*)file->Get("h_u5_three");
TH1D *h_uall_three = (TH1D*)file->Get("h_uall_three");

TH1D *h_s_three = (TH1D*)file->Get("h_s_three");
TH1D *h_s3_three = (TH1D*)file->Get("h_s3_three");
TH1D *h_s5_three = (TH1D*)file->Get("h_s5_three");
TH1D *h_sall_three = (TH1D*)file->Get("h_sall_three");

TH1D *h_d_three = (TH1D*)file->Get("h_d_three");
TH1D *h_d3_three = (TH1D*)file->Get("h_d3_three");
TH1D *h_d5_three = (TH1D*)file->Get("h_d5_three");
TH1D *h_dall_three = (TH1D*)file->Get("h_dall_three");

TH1D *h_du_three = (TH1D*)file->Get("h_du_three");
TH1D *h_du3_three = (TH1D*)file->Get("h_du3_three");
TH1D *h_du5_three = (TH1D*)file->Get("h_du5_three");
TH1D *h_duall_three = (TH1D*)file->Get("h_duall_three");

// Normalize the histograms to percentages
/*int nUjet = h_u_three->GetEntries();
int nU3jet = h_u3_three->GetEntries();
int nU5jet = h_u5_three->GetEntries();
int nUall = h_uall_three->GetEntries();

h_s->Scale(1./nSjet);
h_s3->Scale(1./nS3jet);
h_s5->Scale(1./nS5jet);
h_sall->Scale(1./nSall);

h_s->Scale(1,"width");
h_s3->Scale(1,"width");
h_s5->Scale(1,"width");
h_sall->Scale(1,"width");*/

TH1D *hru = (TH1D*)h_u_three->Clone("hru");
TH1D *hru3 = (TH1D*)h_u3_three->Clone("hru3");
TH1D *hru5 = (TH1D*)h_u5_three->Clone("hru5");

TH1D *hrs = (TH1D*)h_s_three->Clone("hrs");
TH1D *hrs3 = (TH1D*)h_s3_three->Clone("hrs3");
TH1D *hrs5 = (TH1D*)h_s5_three->Clone("hrs5");

TH1D *hrd = (TH1D*)h_d_three->Clone("hrd");
TH1D *hrd3 = (TH1D*)h_d3_three->Clone("hrd3");
TH1D *hrd5 = (TH1D*)h_d5_three->Clone("hrd5");

TH1D *hrdu = (TH1D*)h_du_three->Clone("hrdu");
TH1D *hrdu3 = (TH1D*)h_du3_three->Clone("hrdu3");
TH1D *hrdu5 = (TH1D*)h_du5_three->Clone("hrdu5");

hru->Divide(h_u_three,h_uall_three,1,1,"b");
hru3->Divide(h_u3_three,h_uall_three,1,1,"b");
hru5->Divide(h_u5_three,h_uall_three,1,1,"b");

hrs->Divide(h_s_three,h_sall_three,1,1,"b");
hrs3->Divide(h_s3_three,h_sall_three,1,1,"b");
hrs5->Divide(h_s5_three,h_sall_three,1,1,"b");

hrd->Divide(h_d_three,h_dall_three,1,1,"b");
hrd3->Divide(h_d3_three,h_dall_three,1,1,"b");
hrd5->Divide(h_d5_three,h_dall_three,1,1,"b");

hrdu->Divide(h_du_three,h_duall_three,1,1,"b");
hrdu3->Divide(h_du3_three,h_duall_three,1,1,"b");
hrdu5->Divide(h_du5_three,h_duall_three,1,1,"b");

// Set histogram fill colors and add to stack
/* hru->SetFillColor(625);
hru5->SetFillColor(410);
hru3->SetFillColor(593);

hrs->SetFillColor(625);
hrs5->SetFillColor(410);
hrs3->SetFillColor(593);*/

TH1D *hrsd = (TH1D*)hrs->Clone("hrsd");
TH1D *hrsd3 = (TH1D*)hrs3->Clone("hrsd3");
TH1D *hrsd5 = (TH1D*)hrs5->Clone("hrsd5");

TH1D *hrsdu = (TH1D*)hrs->Clone("hrsdu");
TH1D *hrsdu3 = (TH1D*)hrs3->Clone("hrsdu3");
TH1D *hrsdu5 = (TH1D*)hrs5->Clone("hrsdu5");

TH1D *hrdd = (TH1D*)hrd->Clone("hrdd");
TH1D *hrdd3 = (TH1D*)hrd3->Clone("hrdd3");
TH1D *hrdd5 = (TH1D*)hrd5->Clone("hrdd5");

// Substrations
hrs->Add(hru, -1);
hrs3->Add(hru3, -1);
hrs5->Add(hru5, -1);

hrd->Add(hru, -1);
hrd3->Add(hru3, -1);
hrd5->Add(hru5, -1);

hrsd->Add(hrdd, -1);
hrsd3->Add(hrdd3, -1);
hrsd5->Add(hrdd5, -1);

hrsdu->Add(hrdu, -1);
hrsdu3->Add(hrdu3, -1);
hrsdu5->Add(hrdu5, -1);

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
TH1D *h1 = tdrHist("h1","Jet p_{T} fraction (S-U)",0,1"p_{T,cand} (GeV)",0.1,100);
TCanvas *c1 = tdrCanvas("c1",h1,8,kSquare);
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
TLegend *leg1 = tdrLeg(0.5,0.9-0.05*3,0.75,0.9);
leg1->AddEntry(hrs5, "Photons", "ple");
leg1->AddEntry(hrs3, "Neutral Hadrons", "ple");
leg1->AddEntry(hrs, "Charged Hadrons", "ple");
leg1->Draw();

TLatex *tex1 = new TLatex();
tex1->SetNDC(); tex1->SetTextSize(0.045);
tex1->DrawLatex(0.17,0.8,"|#eta| < 1.3");
tex1->DrawLatex(0.17,0.75,"60 < p_{T,jet} < 140 GeV");
// Assuming the x-axis categories are correctly set when histograms were created
// If you need to set labels for the x-axis categories, do it here

// Update the canvas to reflect changes
c1->RedrawAxis();
c1->Modified();
c1->Update();
c1->SaveAs("pdf/differenceSU.pdf");

TH1D *h2 = tdrHist("h2","Jet p_{T} fraction (D-U)",-0.06 + 1e-4,0.08 -1e-4,"p_{T,cand} (GeV)",0.1,100);
TCanvas *c2 = tdrCanvas("c1",h2,8,kSquare);
c2->SetLogx();

tdrDraw(hrd,"histe",kFullSquare,kRed,kSolid,-1,kNone);
hrd->SetMarkerSize(1.5);
tdrDraw(hrd3,"histe",kFullCircle,kGreen+2,kSolid,-1,kNone);
hrd3->SetMarkerSize(1.5);
tdrDraw(hrd5,"histe",kFullDiamond,kBlue,kSolid,-1,kNone);
hrd5->SetMarkerSize(1.75);


// Create legend
//TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
TLegend *leg2 = tdrLeg(0.5,0.9-0.05*3,0.75,0.9);
leg2->AddEntry(hrd5, "Photons", "ple");
leg2->AddEntry(hrd3, "Neutral Hadrons", "ple");
leg2->AddEntry(hrd, "Charged Hadrons", "ple");
leg2->Draw();

TLatex *tex2 = new TLatex();
tex2->SetNDC(); tex2->SetTextSize(0.045);
tex2->DrawLatex(0.17,0.8,"|#eta| < 1.3");
tex2->DrawLatex(0.17,0.75,"60 < p_{T,jet} < 140 GeV");
// Assuming the x-axis categories are correctly set when histograms were created
// If you need to set labels for the x-axis categories, do it here

// Update the canvas to reflect changes
c2->RedrawAxis();
c2->Modified();
c2->Update();
c2->SaveAs("pdf/differenceDU.pdf");

TH1D *h3 = tdrHist("h3","Jet p_{T} fraction (S-D)",-0.09 + 1e-4,0.12 -1e-4,"p_{T,cand} (GeV)",0.1,100);
TCanvas *c3 = tdrCanvas("c1",h3,8,kSquare);
c3->SetLogx();

tdrDraw(hrsd,"histe",kFullSquare,kRed,kSolid,-1,kNone);
hrsd->SetMarkerSize(1.5);
tdrDraw(hrsd3,"histe",kFullCircle,kGreen+2,kSolid,-1,kNone);
hrsd3->SetMarkerSize(1.5);
tdrDraw(hrsd5,"histe",kFullDiamond,kBlue,kSolid,-1,kNone);
hrsd5->SetMarkerSize(1.75);


// Create legend
//TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
TLegend *leg3 = tdrLeg(0.5,0.9-0.05*3,0.75,0.9);
leg3->AddEntry(hrsd5, "Photons", "ple");
leg3->AddEntry(hrsd3, "Neutral Hadrons", "ple");
leg3->AddEntry(hrsd, "Charged Hadrons", "ple");
leg3->Draw();

TLatex *tex3 = new TLatex();
tex3->SetNDC(); tex3->SetTextSize(0.045);
tex3->DrawLatex(0.17,0.8,"|#eta| < 1.3");
tex3->DrawLatex(0.17,0.75,"60 < p_{T,jet} < 140 GeV");
// Assuming the x-axis categories are correctly set when histograms were created
// If you need to set labels for the x-axis categories, do it here

// Update the canvas to reflect changes
c3->RedrawAxis();
c3->Modified();
c3->Update();
c3->SaveAs("pdf/differenceSD.pdf");

TH1D *h4 = tdrHist("h4","Jet p_{T} fraction (S-DU)",-0.07 + 1e-4,0.10 -1e-4,"p_{T,cand} (GeV)",0.1,100);
TCanvas *c4 = tdrCanvas("c4",h4,8,kSquare);
c4->SetLogx();
//hrs->SetFillStyle(kNone);
//hrs->Draw("histe");
tdrDraw(hrsdu,"histe",kFullSquare,kRed,kSolid,-1,kNone);
hrsdu->SetMarkerSize(1.5);
//hrs3->SetFillStyle(kNone);
//hrs3->Draw("histe same");
tdrDraw(hrsdu3,"histe",kFullCircle,kGreen+2,kSolid,-1,kNone);
hrsdu3->SetMarkerSize(1.5);
//hrs5->SetFillStyle(kNone);
//hrs5->Draw("histe same");
tdrDraw(hrsdu5,"histe",kFullDiamond,kBlue,kSolid,-1,kNone);
hrsdu5->SetMarkerSize(1.75);


// Create legend
//TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
TLegend *leg4 = tdrLeg(0.5,0.9-0.05*3,0.75,0.9);
leg4->AddEntry(hrsdu5, "Photons", "ple");
leg4->AddEntry(hrsdu3, "Neutral Hadrons", "ple");
leg4->AddEntry(hrsdu, "Charged Hadrons", "ple");
leg4->Draw();

TLatex *tex4 = new TLatex();
tex4->SetNDC(); tex4->SetTextSize(0.045);
tex4->DrawLatex(0.17,0.8,"|#eta| < 1.3");
tex4->DrawLatex(0.17,0.75,"60 < p_{T,jet} < 140 GeV");
// Assuming the x-axis categories are correctly set when histograms were created
// If you need to set labels for the x-axis categories, do it here

// Update the canvas to reflect changes
c4->RedrawAxis();
c4->Modified();
c4->Update();
c4->SaveAs("pdf/differenceSDU.pdf");

TH1D *h5 = tdrHist("h5","Jet p_{T} fraction (S-U & D-U)",-0.07 + 1e-4,0.15 -1e-4,"p_{T,cand} (GeV)",0.1,100);
TCanvas *c5 = tdrCanvas("c5",h5,8,kSquare);
c5->SetLogx();

tdrDraw(hrs,"histe",kFullSquare,kRed,kSolid,-1,kNone);
hrs->SetMarkerSize(1.5);
tdrDraw(hrs3,"histe",kFullCircle,kGreen+2,kSolid,-1,kNone);
hrs3->SetMarkerSize(1.5);
tdrDraw(hrs5,"histe",kFullDiamond,kBlue,kSolid,-1,kNone);
hrs5->SetMarkerSize(1.75);
tdrDraw(hrd,"histe",kSquare,kRed,kDashed,-1,kNone);
hrd->SetMarkerSize(1.5);
tdrDraw(hrd3,"histe",kCircle,kGreen+2,kDashed,-1,kNone);
hrd3->SetMarkerSize(1.5);
tdrDraw(hrd5,"histe",kOpenDiamond,kBlue,kDashed,-1,kNone);
hrd5->SetMarkerSize(1.75);


// Create legend
//TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
TLegend *leg5 = tdrLeg(0.5,0.9-0.05*6,0.75,0.9);
leg5->AddEntry(hrs5, "Photons S-U", "ple");
leg5->AddEntry(hrs3, "Neutral Hadron S-U", "ple");
leg5->AddEntry(hrs, "Charged Hadrons S-U", "ple");
leg5->AddEntry(hrd5, "Photons D-U", "ple");
leg5->AddEntry(hrd3, "Neutral Hadrons D-U", "ple");
leg5->AddEntry(hrd, "Charged Hadrons D-U", "ple");
leg5->Draw();

TLatex *tex5 = new TLatex();
tex5->SetNDC(); tex5->SetTextSize(0.045);
tex5->DrawLatex(0.17,0.8,"|#eta| < 1.3");
tex5->DrawLatex(0.17,0.75,"60 < p_{T,jet} < 140 GeV");
// Assuming the x-axis categories are correctly set when histograms were created
// If you need to set labels for the x-axis categories, do it here

// Update the canvas to reflect changes
c5->RedrawAxis();
c5->Modified();
c5->Update();
c5->SaveAs("pdf/differenceSU&DU.pdf");
// Do not close the file if you want to interact with the histograms further
// file->Close(); // Uncomment this if you're done with the file
}