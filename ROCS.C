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

void ROCS() {
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

    TH1D *h0 = new TH1D("h0", "nhf1 distribution; nhf1; Fraction", 100, 0, 1);

    TH1D *h_s_nhf = new TH1D("h_s_nhf", "nhf1 for abs(flav1)==3; nhf1; Fraction", 100, 0, 1);
    TH1D *h_c_nhf = new TH1D("h_c_nhf", "nhf1 for abs(flav1)==3; nhf1; Fraction", 100, 0, 1);
    TH1D *h_ud_nhf = new TH1D("h_ud_nhf", "nhf1 for abs(flav1)==1 && abs(flav1)==2; nhf1; Fraction", 100, 0, 1);

    TH1D *h_c_ctag = new TH1D("h_c_ctag", "ctag1 for abs(flav1)==4; ctag1; Fraction", 100, 0, 1);
    TH1D *h_s_ctag = new TH1D("h_s_ctag", "ctag1 for abs(flav1)==4; ctag1; Fraction", 100, 0, 1);
    TH1D *h_ud_ctag = new TH1D("h_ud_ctag", "nhf1 for abs(flav1)==1 && abs(flav1)==2; ctag1; Fraction", 100, 0, 1);

    TH1D *h_xs_nhf = new TH1D("h_xs_nhf", "nhf1 for abs(flav1)!=3; nhf1; Fraction", 100, 0, 1);
    TH1D *h_xc_ctag = new TH1D("h_xc_ctag", "ctag1 for abs(flav1)!=4; ctag1; Fraction", 100, 0, 1);





    // Fill histograms
    //tree->Draw("ctag1>>h0tree");
    //tree->Draw("ctag1>>hctree", "abs(flav1)==3");
    //tree->Draw("ctag1>>hxtree", "abs(flav1)!=3");

    tree->Project("h0", "nhf1");

    tree->Project("h_s_nhf", "nhf1", "abs(flav1)==3");
    tree->Project("h_c_nhf", "nhf1", "abs(flav1)==4");
    tree->Project("h_ud_nhf", "nhf1", "abs(flav1)==1 || abs(flav1)==2");

    tree->Project("h_c_ctag", "ctag1", "abs(flav1)==4");
    tree->Project("h_s_ctag", "ctag1", "abs(flav1)==3");
    tree->Project("h_ud_ctag", "ctag1", "abs(flav1)==1 || abs(flav1)==2");

    tree->Project("h_xs_nhf", "nhf1", "abs(flav1)!=3");
    tree->Project("h_xc_ctag", "ctag1", "abs(flav1)!=4");

    

    TH1D *h02 = (TH1D*)h0->Clone("h02");

    TH1D *h_s_nhf2 = (TH1D*)h_s_nhf->Clone("h_s_nhf2");
    TH1D *h_c_nhf2 = (TH1D*)h_c_nhf->Clone("h_c_nhf2");
    TH1D *h_ud_nhf2 = (TH1D*)h_ud_nhf->Clone("h_ud_nhf2");

    TH1D *h_c_ctag2 = (TH1D*)h_c_ctag->Clone("h_c_ctag2");
    TH1D *h_s_ctag2 = (TH1D*)h_s_ctag->Clone("h_s_ctag2");
    TH1D *h_ud_ctag2 = (TH1D*)h_ud_ctag->Clone("h_ud_ctag2");

    TH1D *h_xs_nhf2 = (TH1D*)h_xs_nhf->Clone("h_xs_nhf2");
    TH1D *h_xc_ctag2 = (TH1D*)h_xc_ctag->Clone("h_xc_ctag2");


    // Scale histograms
    h_s_nhf2->Scale(1. / h_s_nhf2->Integral());
    h_c_nhf2->Scale(1. / h_c_nhf2->Integral());
    h_ud_nhf2->Scale(1. / h_ud_nhf2->Integral());

    h_c_ctag2->Scale(1. / h_c_ctag2->Integral());
    h_s_ctag2->Scale(1. / h_s_ctag2->Integral());
    h_ud_ctag2->Scale(1. / h_ud_ctag2->Integral());

    h_xs_nhf2->Scale(1. / h_xs_nhf2->Integral());
    h_xc_ctag2->Scale(1. / h_xc_ctag2->Integral());


    tdrDraw(h_s_nhf2,"Pz",kFullCircle,kOrange+7);
    h_s_nhf2->SetMarkerSize(0.5);

    tdrDraw(h_c_nhf2,"Pz",kFullCircle,kGreen+2);
    h_c_nhf2->SetMarkerSize(0.5);
    
    tdrDraw(h_ud_nhf2,"Pz",kFullCircle,kPink-9);
    h_ud_nhf2->SetMarkerSize(0.5);
    
    tdrDraw(h_c_ctag2,"Pz",kFullCircle,kGreen-7);
    h_c_ctag2->SetMarkerSize(0.5);

    tdrDraw(h_s_ctag2,"Pz",kFullCircle,kOrange-2);
    h_s_ctag2->SetMarkerSize(0.5);

    tdrDraw(h_ud_ctag2,"Pz",kFullCircle,kGreen+4);
    h_ud_ctag2->SetMarkerSize(0.5);

    tdrDraw(h_xs_nhf2,"Pz",kFullCircle,kBlue);
    h_xs_nhf2->SetMarkerSize(0.5);

    tdrDraw(h_xc_ctag2,"Pz",kFullCircle,kViolet);
    h_xc_ctag2->SetMarkerSize(0.5);

    // Create a legend
    TLegend *leg = tdrLeg(0.2,0.55-0.05*7,0.4,0.6);
    leg->AddEntry(h_s_nhf2, "s", "PLE");
    leg->AddEntry(h_c_ctag2, "c", "PLE");
    leg->AddEntry(h_ud_nhf2, "ud nhf", "PLE");
    leg->AddEntry(h_ud_ctag2, "ud ctag", "PLE");
    leg->AddEntry(h_xs_nhf2, "x-s", "PLE");
    leg->AddEntry(h_xc_ctag2, "x-c", "PLE");
 
    
    leg->Draw();

    // Update the canvas to reflect the changes
    gPad->Update();

    // Save the canvas as a .pdf file
    c1->SaveAs("pdf/ROC1S.pdf");


    TH1D *h2 = tdrHist("h2","Efficiency ",0,1,"Background efficiency",0.001,1);
    TCanvas *c2 = tdrCanvas("c2",h2,8,11,kSquare);

    // Create ROC curve data

    TGraph *rocCurveSX = new TGraph(100);
    TGraph *rocCurveSUD = new TGraph(100);
    TGraph *rocCurveSC = new TGraph(100);

    TGraph *rocCurveCX = new TGraph(100);
    TGraph *rocCurveCUD = new TGraph(100);
    TGraph *rocCurveCS = new TGraph(100);

    for (int i = 1; i !=101; ++i) {
        double x1 = h_xs_nhf2->Integral(i, 100);
        double y1 = h_s_nhf2->Integral(i, 100);
        rocCurveSX->SetPoint(i, x1, y1);

        double x2 = h_ud_nhf2->Integral(i, 100);
        double y2 = h_s_nhf2->Integral(i, 100);
        rocCurveSUD->SetPoint(i, x2, y2);
        
        double x3 = h_c_nhf2->Integral(i, 100);
        double y3 = h_s_nhf2->Integral(i, 100);
        rocCurveSC->SetPoint(i, x3, y3);

        double x4 = h_xc_ctag2->Integral(i, 100);
        double y4 = h_c_ctag2->Integral(i, 100);
        rocCurveCX->SetPoint(i, x4, y4);

        double x5 = h_ud_ctag2->Integral(i, 100);
        double y5 = h_c_ctag2->Integral(i, 100);
        rocCurveCUD->SetPoint(i, x5, y5);

        double x6 = h_s_ctag2->Integral(i, 100);
        double y6 = h_c_ctag2->Integral(i, 100);
        rocCurveCS->SetPoint(i, x6, y6);

    }
    
    rocCurveSX->SetLineColor(kOrange+7);
    rocCurveSUD->SetLineColor(kOrange-1);
    rocCurveSC->SetLineColor(kBlue-4);
    rocCurveCX->SetLineColor(kGreen-2);
    rocCurveCUD->SetLineColor(kViolet+2);
    rocCurveCS->SetLineColor(kPink+1);

    rocCurveSX->SetLineWidth(1);
    rocCurveSUD->SetLineWidth(1);
    rocCurveSC->SetLineWidth(1);
    rocCurveCX->SetLineWidth(1);
    rocCurveCUD->SetLineWidth(1);
    rocCurveCS->SetLineWidth(1);

    rocCurveSX->Draw("same");
    rocCurveSUD->Draw("same");
    rocCurveSC->Draw("same");
    rocCurveCX->Draw("same");
    rocCurveCUD->Draw("same");
    rocCurveCS->Draw("same");

    TLine *l = new TLine();
    l->DrawLine(0,0,1,1);

    TLegend *leg2 = tdrLeg(0.6,0.3-0.05*2,0.9,0.5);
    leg2->AddEntry(rocCurveSX, "s vs x", "PLE");
    leg2->AddEntry(rocCurveSUD, "s vs ud", "PLE");
    leg2->AddEntry(rocCurveSC, "s vs c", "PLE");
    leg2->AddEntry(rocCurveCX, "c vs x", "PLE");
    leg2->AddEntry(rocCurveCUD, "c vs ud", "PLE");
    leg2->AddEntry(rocCurveCS, "c vs s", "PLE");

    leg2->Draw();

    // Update the canvas to reflect the changes
    gPad->Update();

       // Save the canvas
    c2->SaveAs("pdf/ROC_Curvesall.pdf");
}