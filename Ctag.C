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
#include <TLatex.h>
#include "tdrstyle_mod22.C"

void Ctag() {
    setTDRStyle();

    // Open the ROOT file
    TFile *file = new TFile("output_stag3.root", "READ");

    TH1D *p = (TH1D*)file->Get("p");
    TH1D *ps = (TH1D*)file->Get("ps");
    TH1D *p2 = (TH1D*)file->Get("p2");
    TH1D *ps2 = (TH1D*)file->Get("ps2");

    lumi_136TeV = "Run3 simulation";
    extraText = "Private";
    TH1D *h1 = tdrHist("h1","ctag > 0.43",0,0.28,"p^{reco}_{T}",21,200);
    TCanvas *c1 = tdrCanvas("c1",h1,4,11,kSquare);


    h1->GetXaxis()->SetLabelSize(0.04);
    h1->GetYaxis()->SetLabelSize(0.04);
    h1->GetXaxis()->SetTitleSize(0.045);
    h1->GetXaxis()->SetTitleOffset(1.2);
    h1->GetYaxis()->SetTitleOffset(1.4);
    h1->GetYaxis()->SetTitleSize(0.045);
    //gPad->SetLogy();
    //c1->SetLogx();


    tdrDraw(p,"Pz",kFullCircle,kSpring-7);
    p->SetMarkerSize(0.8);
    tdrDraw(p2,"Pz",kFullCircle,kSpring-5);
    p2->SetMarkerSize(0.8);

    tdrDraw(ps,"Pz",kFullCircle,kOrange+10);
    ps->SetMarkerSize(0.8);
    tdrDraw(ps2,"Pz",kFullCircle,kOrange-3);
    ps2->SetMarkerSize(0.8);

    // Create a legend
    TLegend *leg = tdrLeg(0.75,0.5-0.05*4,0.9,0.53);
    leg->AddEntry(p, "c_{jet1}", "ple");
    leg->AddEntry(p2, "c_{jet2}", "ple");
    leg->AddEntry(ps, "s_{jet1}", "ple");
    leg->AddEntry(ps2, "s_{jet2}", "ple");
    leg->SetTextSize(0.03);
    leg->Draw();

    // Update the canvas to reflect the changes
    TLatex *tex1 = new TLatex();
    tex1->SetNDC(); tex1->SetTextSize(0.045); 


    gPad->RedrawAxis();
    gPad->Update();

    // Save the canvas as a .pdf file
    c1->SaveAs("pdf/ctag2.pdf");
}