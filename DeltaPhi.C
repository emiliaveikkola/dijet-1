#include <TMath.h>
#include <TF1.h>
#include <TH1F.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include <TStyle.h>
#include <iostream>
#include <algorithm>
#include "tdrstyle_mod22.C"

void DeltaPhi() {
    // Open the ROOT file and get the histogram
    TFile *file = new TFile("output_stag3.root", "READ");
    TFile *file2 = new TFile("output_stag_DATA.root", "READ");

    TH1D *h_phi_d = (TH1D*)file->Get("h_phi_d");
    TH1D *h_phi_u = (TH1D*)file->Get("h_phi_u");
    TH1D *h_phi_s = (TH1D*)file->Get("h_phi_s");
    TH1D *h_phi_c = (TH1D*)file->Get("h_phi_c");

    h_phi_c->Scale(1./h_phi_c->Integral());
    h_phi_u->Scale(1./h_phi_u->Integral());
    h_phi_d->Scale(1./h_phi_d->Integral());
    h_phi_s->Scale(1./h_phi_s->Integral());



    setTDRStyle();
    lumi_136TeV = "Run3 simulation";
    extraText = "Private";
    TH1D *h1 = tdrHist("h1","N",0,0.06,"#Delta#Phi(jet,W)",-2,2);
    TCanvas *c1 = tdrCanvas("c1",h1,4,11,kSquare);
    h1->GetYaxis()->SetTitleOffset(1.5);
    h1->GetYaxis()->SetTitleSize(0.05);
    h1->GetXaxis()->SetTitleSize(0.05);
    h1->GetYaxis()->SetLabelSize(0.045);
    h1->GetXaxis()->SetLabelSize(0.045);
    //gPad->SetLogy();
    //c1->SetLogx();

    // Draw the histogram
    tdrDraw(h_phi_d,"histe",kNone,kAzure+7,kSolid, -1, kNone);
    h_phi_d->SetLineWidth(2);
    tdrDraw(h_phi_u,"histe",kNone,kPink-9,kSolid, -1, kNone);
    h_phi_u->SetLineWidth(2);
    tdrDraw(h_phi_s,"histe",kNone,kOrange-3,kSolid, -1, kNone);
    h_phi_s->SetLineWidth(2);
    tdrDraw(h_phi_c,"histe",kNone,kSpring-5,kSolid, -1, kNone);
    h_phi_c->SetLineWidth(2);



    // Create a legend
    TLegend *leg = tdrLeg(0.8,1.0-0.05*4,0.9,0.65);
    leg->AddEntry(h_phi_d, "d", "PLE");
    leg->AddEntry(h_phi_u, "u", "PLE");
    leg->AddEntry(h_phi_s, "s", "PLE");
    leg->AddEntry(h_phi_c, "c", "PLE");
    leg->SetTextSize(0.035);

    //leg->Draw();

    // Update the canvas to reflect the changes
    TLatex *tex1 = new TLatex();
    tex1->SetNDC(); tex1->SetTextSize(0.045); 

    //c1->SetLeftMargin(0.165);
    gPad->RedrawAxis();
    gPad->Update();

    // Save the canvas as a .pdf file
    c1->SaveAs("pdf/deltaphi2.pdf");
}