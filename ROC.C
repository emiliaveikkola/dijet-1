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

void ROC() {
    setTDRStyle();
    lumi_136TeV = "Run3 simulation";
    extraText = "Private";

    // Open the ROOT file and get the histogram
    TFile *file = new TFile("/Users/macbookpro/Downloads/data/W/Muo16_MC.root", "READ");
    TTree *tree = nullptr;
    file->GetObject("tree", tree);

    //TH1D *ctag1 = (TH1D*)file->Get("ctag1");

    // Create histograms
    TH1D *h1 = tdrHist("h1","Fraction",0 + 1e-7,5,"ctag",0,1);
    TCanvas *c1 = tdrCanvas("c1",h1,8,11,kSquare);
    c1->SetLogy();

    TH1D *h0 = new TH1D("h0", "ctag1 distribution; ctag1; Fraction", 100, 0, 1);
    TH1D *hc = new TH1D("hc", "ctag1 for abs(flav1)==3; ctag1; Fraction", 100, 0, 1);
    TH1D *hx = new TH1D("hx", "ctag1 for abs(flav1)!=3; ctag1; Fraction", 100, 0, 1);

    // Fill histograms
    //tree->Draw("ctag1>>h0tree");
    //tree->Draw("ctag1>>hctree", "abs(flav1)==3");
    //tree->Draw("ctag1>>hxtree", "abs(flav1)!=3");

    tree->Project("h0", "ctag1");
    tree->Project("hc", "ctag1", "abs(flav1)==4");
    tree->Project("hx", "ctag1", "abs(flav1)!=4");

    TH1D *h02 = (TH1D*)h0->Clone("h02");
    TH1D *hc2 = (TH1D*)hc->Clone("hc2");
    TH1D *hx2 = (TH1D*)hx->Clone("hx2");

    // Scale histograms
    hx2->Scale(1. / hx2->Integral());
    hc2->Scale(1. / hc2->Integral());

    tdrDraw(hc2,"Pz",kFullCircle,kGreen-3);
    hc2->SetMarkerSize(1.5);

    tdrDraw(hx2,"Pz",kFullSquare,kBlue-9);
    hx2->SetMarkerSize(1.35);

    // Create a legend
    TLegend *leg = tdrLeg(0.7,0.8-0.05*2,0.8,0.87);
    leg->AddEntry(hc2, "hc", "PLE");
    leg->AddEntry(hx2, "hx", "PLE");
    
    leg->Draw();

    // Update the canvas to reflect the changes
    gPad->Update();

    // Save the canvas as a .pdf file
    c1->SaveAs("pdf/ROC1.pdf");


    TH1D *h2 = tdrHist("h2","Charm efficiency ",0,1,"Background efficiency",0,1);
    TCanvas *c2 = tdrCanvas("c2",h2,8,11,kSquare);

    // Create ROC curve data

    TGraph *rocCurve = new TGraph(100);
    for (int i = 1; i !=101; ++i) {
        double x = hx2->Integral(i, 100);
        double y = hc2->Integral(i, 100);
        rocCurve->SetPoint(i, x, y);
    }
    
    rocCurve->SetLineColor(kBlue+1);
    rocCurve->SetLineWidth(2);
    rocCurve->Draw();
    TLine *l = new TLine();
    l->DrawLine(0,0,1,1);

       // Save the canvas
    c2->SaveAs("pdf/ROC_Curve.pdf");
}