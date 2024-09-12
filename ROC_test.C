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


    double interpolate(TGraph* graph, double x) {
    int n = graph->GetN();
    double *xPoints = graph->GetX();
    double *yPoints = graph->GetY();

    if (x < xPoints[0] || x > xPoints[n-1]) return 0; // Out of range values return 0 or other appropriate value

    for (int i = 0; i < n - 1; i++) {
        if (x >= xPoints[i] && x <= xPoints[i+1]) {
            // Perform linear interpolation
            double slope = (yPoints[i+1] - yPoints[i]) / (xPoints[i+1] - xPoints[i]);
            return yPoints[i] + slope * (x - xPoints[i]);
        }
    }
    return 0; // In case of some unexpected error
}

void ROC_test() {
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

    TH1D *h_s_nhf1 = new TH1D("h_s_nhf1", "nhf1 for abs(flav1)==3; nhf1; Fraction", 100, 0, 1);
    TH1D *h_c_nhf1 = new TH1D("h_c_nhf1", "nhf1 for abs(flav1)==3; nhf1; Fraction", 100, 0, 1);
    TH1D *h_ud_nhf1 = new TH1D("h_ud_nhf1", "nhf1 for abs(flav1)==1 && abs(flav1)==2; nhf1; Fraction", 100, 0, 1);
    TH1D *h_xs_nhf1 = new TH1D("h_xs_nhf1", "nhf1 for abs(flav1)!=3; nhf1; Fraction", 100, 0, 1);

    TH1D *h_s_nhf2 = new TH1D("h_s_nhf2", "nhf2 for abs(flav2)==3; nhf1; Fraction", 100, 0, 1);
    TH1D *h_c_nhf2 = new TH1D("h_c_nhf2", "nhf2 for abs(flav2)==3; nhf1; Fraction", 100, 0, 1);
    TH1D *h_ud_nhf2 = new TH1D("h_ud_nhf2", "nhf2 for abs(flav2)==1 && abs(flav2)==2; nhf1; Fraction", 100, 0, 1);
    TH1D *h_xs_nhf2 = new TH1D("h_xs_nhf2", "nhf2 for abs(flav2)!=3; nhf1; Fraction", 100, 0, 1);

    TH1D *h_c_ctag0 = new TH1D("h_c_ctag0", "ctag1 for abs(flav1)==4; ctag1; Fraction", 100, 0, 1);
    TH1D *h_c_ctag = new TH1D("h_c_ctag", "ctag2 for abs(flav2)==4; ctag2; Fraction", 100, 0, 1);

    TH1D *h_c_ctag1 = new TH1D("h_c_ctag1", "ctag1 for abs(flav1)==4; ctag1; Fraction", 100, 0, 1);
    TH1D *h_s_ctag1 = new TH1D("h_s_ctag1", "ctag1 for abs(flav1)==4; ctag1; Fraction", 100, 0, 1);
    TH1D *h_uds_ctag1 = new TH1D("h_uds_ctag1", "ctag1 for abs(flav1)==1 && abs(flav1)==2; ctag1; Fraction", 100, 0, 1);
    TH1D *h_g_ctag1 = new TH1D("h_g_ctag1", "ctag1 for abs(flav1)==1 && abs(flav1)==2; ctag1; Fraction", 100, 0, 1);

    TH1D *h_c_ctag2 = new TH1D("h_c_ctag2", "ctag1 for abs(flav1)==4; ctag2; Fraction", 100, 0, 1);
    TH1D *h_s_ctag2 = new TH1D("h_s_ctag2", "ctag1 for abs(flav1)==4; ctag2; Fraction", 100, 0, 1);
    TH1D *h_uds_ctag2 = new TH1D("h_uds_ctag2", "ctag1 for abs(flav1)==1 && abs(flav1)==2; ctag1; Fraction", 100, 0, 1);
    TH1D *h_g_ctag2 = new TH1D("h_g_ctag2", "ctag1 for abs(flav1)==1 && abs(flav1)==2; ctag1; Fraction", 100, 0, 1);

    TH1D *h_xc_ctag0 = new TH1D("h_xc_ctag0", "ctag1 for abs(flav1)!=4; ctag1; Fraction", 100, 0, 1);
    TH1D *h_xc_ctag = new TH1D("h_xc_ctag", "ctag2 for abs(flav2)!=4; ctag1; Fraction", 100, 0, 1);
   
    TH1D *h_xc_ctag1 = new TH1D("h_xc_ctag1", "ctag1 for abs(flav1)!=4; ctag1; Fraction", 100, 0, 1);
    TH1D *h_xc_ctag2 = new TH1D("h_xc_ctag2", "ctag2 for abs(flav2)!=4; ctag1; Fraction", 100, 0, 1);

    TH1D *h_ud_udstag1 = new TH1D("h_ud_udstag1", "ctag1 for abs(flav1)!=4; ctag1; Fraction", 100, 0, 1);
    TH1D *h_ud_udstag2 = new TH1D("h_ud_udstag2", "ctag2 for abs(flav2)!=4; ctag1; Fraction", 100, 0, 1);





    // Fill histograms
    //tree->Draw("ctag1>>h0tree");
    //tree->Draw("ctag1>>hctree", "abs(flav1)==3");
    //tree->Draw("ctag1>>hxtree", "abs(flav1)!=3");

    tree->Project("h0", "nhf1");

    tree->Project("h_s_nhf1", "nhf1", "abs(flav1)==3");
    tree->Project("h_c_nhf1", "nhf1", "abs(flav1)==4");
    tree->Project("h_ud_nhf1", "nhf1", "abs(flav1)==1 || abs(flav1)==2");
    tree->Project("h_xs_nhf1", "nhf1", "abs(flav1)!=3");

    tree->Project("h_s_nhf2", "nhf2", "abs(flav2)==3");
    tree->Project("h_c_nhf2", "nhf2", "abs(flav2)==4");
    tree->Project("h_ud_nhf2", "nhf2", "abs(flav2)==1 || abs(flav2)==2");
    tree->Project("h_xs_nhf2", "nhf2", "abs(flav2)!=3");

    tree->Project("h_c_ctag0", "ctag1", "abs(flav1)==4");
    tree->Project("h_c_ctag", "ctag2", "abs(flav2)==4");

    tree->Project("h_c_ctag1", "ctag1/(udstag1+gtag1+ctag1)", "abs(flav1)==4");
    tree->Project("h_s_ctag1", "ctag1/(udstag1+gtag1+ctag1)", "abs(flav1)==3");
    tree->Project("h_uds_ctag1", "ctag1/(udstag1+gtag1+ctag1)", "abs(flav1)==1 || abs(flav1)==2 || abs(flav1)==3");
    tree->Project("h_g_ctag1", "ctag1/(udstag1+gtag1+ctag1)", "abs(flav1)==21");

    tree->Project("h_c_ctag2", "ctag2/(udstag2+gtag2+ctag2)", "abs(flav2)==4");
    tree->Project("h_s_ctag2", "ctag2/(udstag2+gtag2+ctag2)", "abs(flav2)==3");
    tree->Project("h_uds_ctag2", "ctag2/(udstag2+gtag2+ctag2)", "abs(flav2)==1 || abs(flav2)==2 || abs(flav2)==3");
    tree->Project("h_g_ctag2", "ctag2/(udstag2+gtag2+ctag2)", "abs(flav2)==21");

    tree->Project("h_xc_ctag0", "ctag1", "abs(flav1)!=4");
    tree->Project("h_xc_ctag", "ctag2", "abs(flav1)!=4");

    tree->Project("h_xc_ctag1", "ctag1/(udstag1+gtag1+ctag1)", "abs(flav1)!=4");
    tree->Project("h_xc_ctag2", "ctag2/(udstag2+gtag2+ctag2)", "abs(flav1)!=4");

    

    TH1D *h03 = (TH1D*)h0->Clone("h03");

    TH1D *h_s_nhf3 = (TH1D*)h_s_nhf1->Clone("h_s_nhf3");
    TH1D *h_c_nhf3 = (TH1D*)h_c_nhf1->Clone("h_c_nhf3");
    TH1D *h_ud_nhf3 = (TH1D*)h_ud_nhf1->Clone("h_ud_nhf3");
    TH1D *h_xs_nhf3 = (TH1D*)h_xs_nhf1->Clone("h_xs_nhf3");

    TH1D *h_s_nhf4 = (TH1D*)h_s_nhf2->Clone("h_s_nhf4");
    TH1D *h_c_nhf4 = (TH1D*)h_c_nhf2->Clone("h_c_nhf4");
    TH1D *h_ud_nhf4 = (TH1D*)h_ud_nhf2->Clone("h_ud_nhf4");
    TH1D *h_xs_nhf4 = (TH1D*)h_xs_nhf2->Clone("h_xs_nhf4");

    TH1D *h_c_ctag00 = (TH1D*)h_c_ctag0->Clone("h_c_ctag00");
    TH1D *h_c_ctag11 = (TH1D*)h_c_ctag->Clone("h_c_ctag11");

    TH1D *h_c_ctag3 = (TH1D*)h_c_ctag1->Clone("h_c_ctag3");
    TH1D *h_s_ctag3 = (TH1D*)h_s_ctag1->Clone("h_s_ctag3");
    TH1D *h_uds_ctag3 = (TH1D*)h_uds_ctag1->Clone("h_uds_ctag3");
    TH1D *h_g_ctag3 = (TH1D*)h_g_ctag1->Clone("h_g_ctag3");

    TH1D *h_c_ctag4 = (TH1D*)h_c_ctag2->Clone("h_c_ctag4");
    TH1D *h_s_ctag4 = (TH1D*)h_s_ctag2->Clone("h_s_ctag4");
    TH1D *h_uds_ctag4 = (TH1D*)h_uds_ctag2->Clone("h_uds_ctag4");
    TH1D *h_g_ctag4 = (TH1D*)h_g_ctag2->Clone("h_g_ctag4");

    TH1D *h_xc_ctag00 = (TH1D*)h_xc_ctag0->Clone("h_xc_ctag00");
    TH1D *h_xc_ctag11 = (TH1D*)h_xc_ctag->Clone("h_xc_ctag11");

    TH1D *h_xc_ctag3 = (TH1D*)h_xc_ctag1->Clone("h_xc_ctag3");
    TH1D *h_xc_ctag4 = (TH1D*)h_xc_ctag2->Clone("h_xc_ctag4");

    // add 2 to 1

    h_s_nhf3->Add(h_s_nhf4);
    h_c_nhf3->Add(h_c_nhf4);
    h_ud_nhf3->Add(h_ud_nhf4);
    h_xs_nhf3->Add(h_xs_nhf4);

    h_c_ctag00->Add(h_c_ctag11);

    h_c_ctag3->Add(h_c_ctag4);
    h_s_ctag3->Add(h_s_ctag4);
    h_uds_ctag3->Add(h_uds_ctag4);
    h_g_ctag3->Add(h_g_ctag4);

    h_xc_ctag00->Add(h_xc_ctag11);

    h_xc_ctag3->Add(h_xc_ctag4);

 

    // Scale histograms
    h_s_nhf3->Scale(1. / h_s_nhf3->Integral());
    h_c_nhf3->Scale(1. / h_c_nhf3->Integral());
    h_ud_nhf3->Scale(1. / h_ud_nhf3->Integral());

    h_xs_nhf3->Scale(1. / h_xs_nhf3->Integral());


    h_c_ctag00->Scale(1. / h_c_ctag00->Integral());

    h_c_ctag3->Scale(1. / h_c_ctag3->Integral());
    h_s_ctag3->Scale(1. / h_s_ctag3->Integral());
    h_uds_ctag3->Scale(1. / h_uds_ctag3->Integral());
    h_g_ctag3->Scale(1. / h_g_ctag3->Integral());

    h_xc_ctag00->Scale(1. / h_xc_ctag00->Integral());
    h_xc_ctag3->Scale(1. / h_xc_ctag3->Integral());







    tdrDraw(h_s_nhf3,"Pz",kFullCircle,kOrange+7);
    h_s_nhf3->SetMarkerSize(0.5);

    tdrDraw(h_c_nhf3,"Pz",kFullCircle,kGreen+2);
    h_c_nhf3->SetMarkerSize(0.5);
    
    tdrDraw(h_ud_nhf3,"Pz",kFullCircle,kPink-9);
    h_ud_nhf3->SetMarkerSize(0.5);
    
    tdrDraw(h_c_ctag3,"Pz",kFullCircle,kGreen-7);
    h_c_ctag3->SetMarkerSize(0.5);

    tdrDraw(h_s_ctag3,"Pz",kFullCircle,kOrange-2);
    h_s_ctag3->SetMarkerSize(0.5);

    tdrDraw(h_uds_ctag3,"Pz",kFullCircle,kGreen+4);
    h_uds_ctag3->SetMarkerSize(0.5);

    tdrDraw(h_xs_nhf3,"Pz",kFullCircle,kBlue);
    h_xs_nhf3->SetMarkerSize(0.5);

    tdrDraw(h_xc_ctag3,"Pz",kFullCircle,kViolet);
    h_xc_ctag3->SetMarkerSize(0.5);

    // Create a legend
    TLegend *leg = tdrLeg(0.2,0.55-0.05*7,0.4,0.6);
    leg->AddEntry(h_s_nhf3, "s", "PLE");
    leg->AddEntry(h_c_ctag3, "c", "PLE");
    leg->AddEntry(h_ud_nhf3, "ud nhf", "PLE");
    leg->AddEntry(h_uds_ctag3, "uds ctag", "PLE");
    leg->AddEntry(h_xs_nhf3, "x-s", "PLE");
    leg->AddEntry(h_xc_ctag3, "x-c", "PLE");
 
    
    leg->Draw();

    // Update the canvas to reflect the changes
    gPad->Update();

    // Save the canvas as a .pdf file
    c1->SaveAs("pdf/ROC1S2.pdf");


















TFile *file2 = new TFile("output_z2.root", "READ");

TH1D *h_c_ctag_cvl_df30 = (TH1D*)file2->Get("h_c_ctag_cvl_df30");
    TH1D *h_c_udstag_cvl_df30 = (TH1D*)file2->Get("h_c_udstag_cvl_df30");

    TH1D *h_c_ctag_cvb_df30 = (TH1D*)file2->Get("h_c_ctag_cvb_df30");
    TH1D *h_c_btag_cvb_df30 = (TH1D*)file2->Get("h_c_btag_cvb_df30");

    TH1D *h_b_btag_b_df30 = (TH1D*)file2->Get("h_b_btag_b_df30");
    TH1D *h_b_udstag_b_df30 = (TH1D*)file2->Get("h_b_udstag_b_df30");
    TH1D *h_b_ctag_b_df30 = (TH1D*)file2->Get("h_b_ctag_b_df30");




    TH1D *h_c_ctag_cvl_df30c = (TH1D*)h_c_ctag_cvl_df30->Clone("h_c_ctag_cvl_df30c");
    TH1D *h_c_udstag_cvl_df30c = (TH1D*)h_c_udstag_cvl_df30->Clone("h_c_udstag_cvl_df30c");

    TH1D *h_c_ctag_cvb_df30c = (TH1D*)h_c_ctag_cvb_df30->Clone("h_c_ctag_cvb_df30c");
    TH1D *h_c_btag_cvb_df30c = (TH1D*)h_c_btag_cvb_df30->Clone("h_c_btag_cvb_df30c");

    TH1D *h_b_btag_b_df30c = (TH1D*)h_b_btag_b_df30->Clone("h_b_btag_b_df30c");
    TH1D *h_b_udstag_b_df30c = (TH1D*)h_b_udstag_b_df30->Clone("h_b_udstag_b_df30c");
    TH1D *h_b_ctag_b_df30c = (TH1D*)h_b_ctag_b_df30->Clone("h_b_ctag_b_df30c");


    // Scale histograms
    h_c_ctag_cvl_df30c->Scale(1. / h_c_ctag_cvl_df30c->Integral());
    h_c_udstag_cvl_df30c->Scale(1. / h_c_udstag_cvl_df30c->Integral());

    h_c_ctag_cvb_df30c->Scale(1. / h_c_ctag_cvb_df30c->Integral());
    h_c_btag_cvb_df30c->Scale(1. / h_c_btag_cvb_df30c->Integral());

    h_b_btag_b_df30c->Scale(1. / h_b_btag_b_df30c->Integral());
    h_b_udstag_b_df30c->Scale(1. / h_b_udstag_b_df30c->Integral());
    h_b_ctag_b_df30c->Scale(1. / h_b_ctag_b_df30c->Integral());

     






TH1D *h_c_ctag_cvl_pn30 = (TH1D*)file2->Get("h_c_ctag_cvl_pn30");
    TH1D *h_c_udstag_cvl_pn30 = (TH1D*)file2->Get("h_c_udstag_cvl_pn30");

    TH1D *h_c_ctag_cvb_pn30 = (TH1D*)file2->Get("h_c_ctag_cvb_pn30");
    TH1D *h_c_btag_cvb_pn30 = (TH1D*)file2->Get("h_c_btag_cvb_pn30");

    TH1D *h_b_btag_b_pn30 = (TH1D*)file2->Get("h_b_btag_b_pn30");
    TH1D *h_b_udstag_b_pn30 = (TH1D*)file2->Get("h_b_udstag_b_pn30");
    TH1D *h_b_ctag_b_pn30 = (TH1D*)file2->Get("h_b_ctag_b_pn30");




    TH1D *h_c_ctag_cvl_pn30c = (TH1D*)h_c_ctag_cvl_pn30->Clone("h_c_ctag_cvl_pn30c");
    TH1D *h_c_udstag_cvl_pn30c = (TH1D*)h_c_udstag_cvl_pn30->Clone("h_c_udstag_cvl_pn30c");

    TH1D *h_c_ctag_cvb_pn30c = (TH1D*)h_c_ctag_cvb_pn30->Clone("h_c_ctag_cvb_pn30c");
    TH1D *h_c_btag_cvb_pn30c = (TH1D*)h_c_btag_cvb_pn30->Clone("h_c_btag_cvb_pn30c");

    TH1D *h_b_btag_b_pn30c = (TH1D*)h_b_btag_b_pn30->Clone("h_b_btag_b_pn30c");
    TH1D *h_b_udstag_b_pn30c = (TH1D*)h_b_udstag_b_pn30->Clone("h_b_udstag_b_pn30c");
    TH1D *h_b_ctag_b_pn30c = (TH1D*)h_b_ctag_b_pn30->Clone("h_b_ctag_b_pn30c");


    // Scale histograms
    h_c_ctag_cvl_pn30c->Scale(1. / h_c_ctag_cvl_pn30c->Integral());
    h_c_udstag_cvl_pn30c->Scale(1. / h_c_udstag_cvl_pn30c->Integral());

    h_c_ctag_cvb_pn30c->Scale(1. / h_c_ctag_cvb_pn30c->Integral());
    h_c_btag_cvb_pn30c->Scale(1. / h_c_btag_cvb_pn30c->Integral());

    h_b_btag_b_pn30c->Scale(1. / h_b_btag_b_pn30c->Integral());
    h_b_udstag_b_pn30c->Scale(1. / h_b_udstag_b_pn30c->Integral());
    h_b_ctag_b_pn30c->Scale(1. / h_b_ctag_b_pn30c->Integral());















    TH1D *h2 = tdrHist("h2","mis-id rate ",1e-3-5e-4,1,"jet efficiency",0.079,1);
    TCanvas *c2 = tdrCanvas("c2",h2,4,11,kRectangular);
    h2->GetXaxis()->SetLabelSize(0.04);
    h2->GetYaxis()->SetLabelSize(0.04);
    h2->GetXaxis()->SetTitleSize(0.045);
    h2->GetXaxis()->SetTitleOffset(1.2);
    h2->GetYaxis()->SetTitleOffset(1.4);
    h2->GetYaxis()->SetTitleSize(0.045);
    //c2->SetCanvasSize(800, 620); // Customize the size as needed
    c2->SetLogy();

    // Define the specific x-coordinates where grid lines should appear
    double gridXPositions[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    int nXPositions = sizeof(gridXPositions) / sizeof(gridXPositions[0]);

    // Define the specific y-coordinates where grid lines should appear
    double gridYPositions[] = {0.0006, 0.0007, 0.0008, 0.0009, 0.001, 0.002, 0.003, 0.004, 0.005,
    0.006, 0.007, 0.008, 0.009, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.1,
    0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    int nYPositions = sizeof(gridYPositions) / sizeof(gridYPositions[0]);

    // Get x-axis range to draw lines
    double xMin = h2->GetXaxis()->GetXmin();
    double xMax = h2->GetXaxis()->GetXmax();

    // Get y-axis range to draw lines
    double yMin = h2->GetMinimum();
    double yMax = h2->GetMaximum();

    // Draw vertical grid lines at specified x-positions
    for (int i = 0; i < nXPositions; i++) {
        TLine *line = new TLine(gridXPositions[i], yMin, gridXPositions[i], yMax);
        line->SetLineColor(kBlack); // Set line color to gray
        line->SetLineStyle(3); // Dashed line for distinction
        line->Draw("same");
    }
    // Draw horizontal grid lines at specified y-positions
    for (int i = 0; i < nYPositions; i++) {
        TLine *line = new TLine(xMin, gridYPositions[i], xMax, gridYPositions[i]);
        line->SetLineColor(kBlack); // Set line color to gray
        line->SetLineStyle(3); // Dashed line for distinction
        line->Draw("same");
    }

    gPad->Update();

    // Create ROC curve data

    TGraph *rocCurveSX = new TGraph(100);
    TGraph *rocCurveSUD = new TGraph(100);
    TGraph *rocCurveSC = new TGraph(100);

    TGraph *rocCurveCX = new TGraph(100);
    TGraph *rocCurveCUDS = new TGraph(100);
    TGraph *rocCurveCS = new TGraph(100);
    TGraph *rocCurveCG = new TGraph(100);

    TGraph *rocCurveCX_old = new TGraph(100);

    double dx5_min(1), x5_020(1), x5_cut_020(1), y5_020(1);
    double dx5_min2(1), x5_080(1), x5_cut_080(1), y5_080(1);

    double dx9_min(1), x9_020(1), x9_cut_020(1), y9_020(1);
    double dx9_min2(1), x9_080(1), x9_cut_080(1), y9_080(1);
    for (int i = 0; i < 100; ++i) {
        double y1 = h_xs_nhf3->Integral(i + 1, 100);
        double x1 = h_s_nhf3->Integral(i + 1, 100);
        rocCurveSX->SetPoint(i, x1, y1);

        double y2 = h_ud_nhf3->Integral(i, 100);
        double x2 = h_s_nhf3->Integral(i, 100);
        rocCurveSUD->SetPoint(i, x2, y2);
        
        double y3 = h_c_nhf3->Integral(i, 100);
        double x3 = h_s_nhf3->Integral(i, 100);
        rocCurveSC->SetPoint(i, x3, y3);

        double y4 = h_xc_ctag3->Integral(i, 100);
        double x4 = h_c_ctag3->Integral(i, 100);
        rocCurveCX->SetPoint(i, x4, y4);

        double y5 = h_uds_ctag3->Integral(i, 100);
        double x5 = h_c_ctag3->Integral(i, 100);
        rocCurveCUDS->SetPoint(i, x5, y5);

        if (fabs(x5-0.2)< dx5_min){
            x5_cut_020 = h_c_ctag3->GetBinLowEdge(i);
            x5_020 = x5;
            dx5_min = fabs(x5 - 0.2);
            y5_020 = y5;
        }

        if (fabs(x5-0.8)< dx5_min2){
            x5_cut_080 = h_c_ctag3->GetBinLowEdge(i);
            x5_080 = x5;
            dx5_min2 = fabs(x5 - 0.8);
            y5_080 = y5;
        }

        double y6 = h_s_ctag3->Integral(i + 1, 100);
        double x6 = h_c_ctag3->Integral(i + 1, 100);
        rocCurveCS->SetPoint(i, x6, y6);

        double y7 = h_xc_ctag00->Integral(i + 1, 100);
        double x7 = h_c_ctag00->Integral(i + 1, 100);
        rocCurveCX_old->SetPoint(i, x7, y7);

        double y8 = h_g_ctag3->Integral(i + 1, 100);
        double x8 = h_c_ctag3->Integral(i + 1, 100);
        rocCurveCG->SetPoint(i, x8, y8);

    }
    cout << "for ctag > " << x5_cut_020 << " ctag_eff = " << x5_020 << " (target = 0.20)"
         << " mis-tag = "<< y5_020 << " (target = 0.01)" << endl << flush; 

    cout << "for ctag > " << x5_cut_080 << " ctag_eff = " << x5_080 << " (target = 0.80)"
         << " mis-tag = "<< y5_080 << " (target = 0.60)" << endl << flush;
    rocCurveSX->SetLineColor(kOrange+7);
    rocCurveSUD->SetLineColor(kAzure+7);
    rocCurveSC->SetLineColor(kBlue-4);

    rocCurveCX->SetLineColor(kViolet+2);
    rocCurveCX_old->SetLineColor(kGreen+1);
    rocCurveCUDS->SetLineColor(kViolet-2);
    rocCurveCS->SetLineColor(kOrange-3);
    rocCurveCG->SetLineColor(kOrange);

    //rocCurveSX->SetLineWidth(5);
    rocCurveSUD->SetLineWidth(3);
    //rocCurveSC->SetLineWidth(5);
    //rocCurveCX->SetLineWidth(5);
    rocCurveCUDS->SetLineWidth(3);
    //rocCurveCS->SetLineWidth(3);
    //rocCurveCG->SetLineWidth(3);
    //rocCurveCX_old->SetLineWidth(2);
    //rocCurveSX->Draw("same");
    //rocCurveSUD->Draw("same");
    //rocCurveSC->Draw("same");
    //rocCurveCX->Draw("same");
    //rocCurveCX_old->Draw("same");
    rocCurveCUDS->Draw("same");
    //rocCurveCS->Draw("same");
    //rocCurveCG->Draw("same");
    //TLine *l = new TLine();
    //l->DrawLine(0,0,1,1);
    TF1 *l = new TF1("l", "x",0.08,1);
    l->SetLineColor(kBlack);
    l->Draw("same");





    // Data points
    // Define the data points using std::vector of std::pairs
    std::vector<std::pair<double, double>> dataPoints1 = {
        {0.20724160632, 0.000500568281832},
        {0.235802200158, 0.00101243401142},
        {0.25364276705, 0.00148503004894},
        {0.272666204228, 0.00215147859874},
        {0.294059621656, 0.00311701447667},
        {0.309513249584, 0.00414165123147},
        {0.321394948423, 0.00498510624459},
        {0.333276647262, 0.00600033244736},
        {0.346343336227, 0.00722231136355},
        {0.366536924655, 0.0095964567944},
        {0.383167063351, 0.0121360878626},
        {0.399792962369, 0.0149731459901},
        {0.416416741548, 0.0182465465657},
        {0.431855530602, 0.0222355717225},
        {0.447290079977, 0.0264351919781},
        {0.466285959245, 0.0326149574103},
        {0.485279718674, 0.0397451771003},
        {0.499525038245, 0.0460983257042},
        {0.51733168771, 0.0554863358815},
        {0.533949107371, 0.0651558610364},
        {0.548190187264, 0.0737260134827},
        {0.568366816979, 0.0887404539061},
        {0.583792886997, 0.100412760987},
        {0.596846856926, 0.112224956423},
        {0.626509767159, 0.140181440602},
        {0.675151597947, 0.195700587218},
        {0.70955446868, 0.244451778974},
        {0.755813600182, 0.316879726374},
        {0.816301092542, 0.431581292992},
        {0.864925964615, 0.545796079096},
        {0.912363726724, 0.681759949669},
        {0.949125978512, 0.800569290351},
        {0.969285649513, 0.872903049548},
        {0.988260330389, 0.951772373851},
        {1.000118711, 1},
        {0.219144503551, 0.000681759949669},
        {0.245316038586, 0.00123377040111},
        {0.282171563299, 0.0024953860676},
        {0.653796337624, 0.168729652949},
        {0.733277589413, 0.280044592696},
        {0.787838011308, 0.37672862678},
        {0.840019973596, 0.482350961403},
        {0.891016945759, 0.617586329859},
        {0.261967375674, 0.00176550686112},
        {0.225097012087, 0.000800569290351}
    };

    // Sort the vector by the first element of the pair (x value)
    std::sort(dataPoints1.begin(), dataPoints1.end());

    // Prepare arrays to hold sorted x and y values for TGraph
    const int nPoints1 = dataPoints1.size();
    double x1[nPoints1], y1[nPoints1];
    for (int i = 0; i < nPoints1; ++i) {
        x1[i] = dataPoints1[i].first;
        y1[i] = dataPoints1[i].second;
    }

    // Create a TGraph
    TGraph *graph1 = new TGraph(nPoints1, x1, y1);
    graph1->SetTitle("Data Points;X values;Y values");
    graph1->SetLineWidth(3);
    graph1->SetLineColor(kGreen+1);

    // Draw the graph
    //graph1->Draw("same");


        std::vector<std::pair<double, double>> dataPoints2 = {
        {0.0031347962382445027, 0.0003645211863014662},
        {0.004702194357366768, 0.0004471057441071598},
        {0.004702194357366768, 0.0005484106771534533},
        {0.006269592476489005, 0.0007142994776918197},
        {0.007836990595611298, 0.0009416123691642899},
        {0.010971786833855773, 0.0013023429535611785},
        {0.014106583072100304, 0.0015042419803248561},
        {0.017241379310344834, 0.002055670593132338},
        {0.02037617554858931, 0.0026138760763488723},
        {0.025078369905956105, 0.0033235964526577883},
        {0.032915360501567376, 0.005121456461841465},
        {0.040752351097178674, 0.006670143926840944},
        {0.04858934169278997, 0.008687142092539846},
        {0.05799373040752351, 0.011178745686715013},
        {0.07366771159874608, 0.01602629150838806},
        {0.08620689655172412, 0.02013251591012392},
        {0.10971786833855796, 0.028860052989869205},
        {0.13009404388714735, 0.037132657437310194},
        {0.16457680250783702, 0.05258725102490756},
        {0.17711598746081503, 0.06000761296549203},
        {0.19905956112852663, 0.07183775185384043},
        {0.24608150470219436, 0.10050654809487614},
        {0.30407523510971785, 0.13891890345984237},
        {0.38087774294670845, 0.19901342640323774},
        {0.438871473354232, 0.24986776708087594},
        {0.5015673981191222, 0.3062518908537716},
        {0.5329153605015673, 0.3370189759545361},
        {0.5768025078369905, 0.37983877028516294},
        {0.6018808777429467, 0.4081058266966143},
        {0.6363636363636362, 0.4437257422014454},
        {0.6943573667711598, 0.506061563428159},
        {0.7758620689655171, 0.5981658144525434},
        {0.8322884012539185, 0.6660145433404081},
        {0.8683385579937304, 0.7154840765085432},
        {0.9231974921630093, 0.8062833011385832},
        {0.9545454545454544, 0.866220501907806},
        {0.9733542319749215, 0.9086568208256768},
        {0.9890282131661443, 0.9532080006358582},
        {0.9984326018808778, 0.9762777579765805},
        {0.3432601880877743, 0.16828103104263495},
        {0.2695924764890282, 0.11467348092877286}
    };

    // Sort the vector by the first element of the pair (x value)
    std::sort(dataPoints2.begin(), dataPoints2.end());

    // Prepare arrays to hold sorted x and y values for TGraph
    const int nPoints2 = dataPoints2.size();
    double x2[nPoints2], y2[nPoints2];
    for (int i = 0; i < nPoints2; ++i) {
        x2[i] = dataPoints2[i].first;
        y2[i] = dataPoints2[i].second;
    }

    // Create a TGraph
    TGraph *graph2 = new TGraph(nPoints2, x2, y2);
    graph2->SetTitle("Sorted Data Points;X values;Y values");
    //graph2->SetLineColor(kBlack);

    // Draw the graph
    //graph2->Draw("same");


        // Define the data points using std::vector of std::pairs
    std::vector<std::pair<double, double>> dataPoints3 = {
        {0.0031347962382445027, 0.0003558672254837294},
        {0.0031347962382445027, 0.0004261366249881465},
        {0.0031347962382445027, 0.0005617574774363089},
        {0.0031347962382445027, 0.0007494907085085303},
        {0.0031347962382445027, 0.0009880211769767852},
        {0.004702194357366768, 0.0013181822726623408},
        {0.006269592476489005, 0.0017376699430927893},
        {0.007836990595611298, 0.0024324620192908313},
        {0.009404388714733536, 0.003168257698597744},
        {0.010971786833855773, 0.003933012843160524},
        {0.01567398119122254, 0.005571923937539945},
        {0.018808777429467072, 0.006916746631369037},
        {0.021943573667711602, 0.00798903285937508},
        {0.025078369905956105, 0.010037100825125926},
        {0.029780564263322873, 0.012163596765526793},
        {0.036050156739811906, 0.014918493029340972},
        {0.043887147335423204, 0.017649302441581277},
        {0.05015673981191221, 0.020880375892949585},
        {0.059561128526645746, 0.025608544680885987},
        {0.07053291536050155, 0.030661155939055745},
        {0.08620689655172412, 0.03898114330688804},
        {0.10031347962382445, 0.04556244905963141},
        {0.11442006269592475, 0.053898532255385656},
        {0.13322884012539182, 0.06452673275634156},
        {0.15830721003134796, 0.07724487976474907},
        {0.17711598746081503, 0.08813793540216434},
        {0.2006269592476489, 0.10177682598335083},
        {0.23197492163009403, 0.12182774842077193},
        {0.26332288401253917, 0.14236680876090327},
        {0.2884012539184953, 0.1585748934437759},
        {0.3260188087774294, 0.1875347012687284},
        {0.3510971786833856, 0.20392596985800243},
        {0.3840125391849529, 0.23264413506696527},
        {0.41379310344827575, 0.2529638548651877},
        {0.43416927899686514, 0.2718044158019051},
        {0.45611285266457674, 0.28855524741653105},
        {0.48746081504702193, 0.317544468768884},
        {0.518808777429467, 0.34944604386333533},
        {0.5517241379310345, 0.37995322484971245},
        {0.5783699059561127, 0.408221111963394},
        {0.5987460815047021, 0.42821188416054184},
        {0.6489028213166144, 0.4768189977077838},
        {0.6818181818181817, 0.5122549526640878},
        {0.713166144200627, 0.550334778823825},
        {0.7727272727272727, 0.6201405335491128},
        {0.7460815047021943, 0.5841739457319345},
        {0.6269592476489028, 0.45456759581431183},
        {0.8040752351097178, 0.658284335115702},
        {0.847962382445141, 0.715659240527625},
        {0.8808777429467083, 0.759663932619414},
        {0.9106583072100314, 0.80640476827233},
        {0.9388714733542318, 0.8560376073759793},
        {0.9733542319749215, 0.9196387919377691},
        {0.9921630094043887, 0.964692083770465},
        {0.9984326018808778, 1.0000188300949049}
    };

    // Sort the vector by the first element of the pair (x value)
    std::sort(dataPoints3.begin(), dataPoints3.end());

    // Prepare arrays to hold sorted x and y values for TGraph
    const int nPoints3 = dataPoints3.size();
    double x3[nPoints3], y3[nPoints3];
    for (int i = 0; i < nPoints3; ++i) {
        x3[i] = dataPoints3[i].first;
        y3[i] = dataPoints3[i].second;
    }

    // Create a TGraph
    TGraph *graph3 = new TGraph(nPoints3, x3, y3);
    graph3->SetTitle("Sorted Data Points;X values;Y values");
    //graph3->SetLineColor(kRed);
    //graph3->Draw("same");


double xMin2 = std::min(graph2->GetX()[0], graph3->GetX()[0]);
double xMax2 = std::max(graph2->GetX()[graph2->GetN() - 1], graph3->GetX()[graph3->GetN() - 1]);
int numPoints = 100; // Choose an appropriate number of points
std::vector<double> xCommon(numPoints), yAvg(numPoints);

double deltaX = (xMax2 - xMin2) / (numPoints - 1);

for (int i = 0; i < numPoints; i++) {
    double xValue = xMin2 + i * deltaX;
    double y1 = interpolate(graph2, xValue);
    double y2 = interpolate(graph3, xValue);
    yAvg[i] = (y1 + y2) / 2.0;
    xCommon[i] = xValue;
}

TGraph *graphAvg = new TGraph(numPoints, &xCommon[0], &yAvg[0]);

graphAvg->SetLineColor(kPink-3);
graphAvg->SetLineWidth(2);
//graphAvg->Draw("same"); // Draw with markers and lines
















   // Define the specific x-coordinates where grid lines should appear
    double gridXPositionsdf[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    int nXPositionsdf = sizeof(gridXPositionsdf) / sizeof(gridXPositionsdf[0]);

    // Define the specific y-coordinates where grid lines should appear
    double gridYPositionsdf[] = {0.0006, 0.0007, 0.0008, 0.0009, 0.001, 0.002, 0.003, 0.004, 0.005,
    0.006, 0.007, 0.008, 0.009, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.1,
    0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    int nYPositionsdf = sizeof(gridYPositionsdf) / sizeof(gridYPositionsdf[0]);

    // Get x-axis range to draw lines
    double xMindf = h2->GetXaxis()->GetXmin();
    double xMaxdf = h2->GetXaxis()->GetXmax();

    // Get y-axis range to draw lines
    double yMindf = h2->GetMinimum();
    double yMaxdf = h2->GetMaximum();

    // Draw vertical grid lines at specified x-positions
    for (int i = 0; i < nXPositions; i++) {
        TLine *line = new TLine(gridXPositionsdf[i], yMin, gridXPositionsdf[i], yMax);
        line->SetLineColor(kBlack); // Set line color to gray
        line->SetLineStyle(3); // Dashed line for distinction
        line->Draw("same");
    }
    // Draw horizontal grid lines at specified y-positions
    for (int i = 0; i < nYPositionsdf; i++) {
        TLine *line = new TLine(xMindf, gridYPositionsdf[i], xMaxdf, gridYPositionsdf[i]);
        line->SetLineColor(kBlack); // Set line color to gray
        line->SetLineStyle(3); // Dashed line for distinction
        line->Draw("same");
    }

    gPad->Update();

    // Create ROC curve data


    TGraph *rocCurveCUDS_cvl = new TGraph(100);
    TGraph *rocCurveCB_cvb = new TGraph(100);
    TGraph *rocCurveBUDS_b = new TGraph(100);
    TGraph *rocCurveBC_b = new TGraph(100);


    double dx5_mindf(1), x5_020df(1), x5_cut_020df(1), y5_020df(1);
    double dx5_min2df(1), x5_080df(1), x5_cut_080df(1), y5_080df(1);
    for (int i = 0; i < 100; ++i) {
        double y5 = h_c_udstag_cvl_df30c->Integral(i, 100);
        double x5 = h_c_ctag_cvl_df30c->Integral(i, 100);
        rocCurveCUDS_cvl->SetPoint(i, x5, y5);

        double y6 = h_c_btag_cvb_df30c->Integral(i, 100);
        double x6 = h_c_ctag_cvb_df30c->Integral(i, 100);
        rocCurveCB_cvb->SetPoint(i, x6, y6);

        double y7 = h_b_udstag_b_df30c->Integral(i, 100);
        double x7 = h_b_btag_b_df30c->Integral(i, 100);
        rocCurveBUDS_b->SetPoint(i, x7, y7);

        double y8 = h_b_ctag_b_df30c->Integral(i, 100);
        double x8 = h_b_btag_b_df30c->Integral(i, 100);
        rocCurveBC_b->SetPoint(i, x8, y8);

        if (fabs(x5-0.2)< dx5_mindf){
            x5_cut_020df = h_c_ctag_cvl_df30c->GetBinLowEdge(i);
            x5_020df = x5;
            dx5_mindf = fabs(x5 - 0.2);
            y5_020df = y5;
        }

        if (fabs(x5-0.8)< dx5_min2df){
            x5_cut_080df = h_c_ctag_cvl_df30c->GetBinLowEdge(i);
            x5_080df = x5;
            dx5_min2df = fabs(x5 - 0.8);
            y5_080df = y5;
        }
    }
    cout << "for ctag > " << x5_cut_020df << " ctag_eff = " << x5_020df << " (target = 0.20)"
         << " mis-tag = "<< y5_020df << " (target = 0.01)" << endl << flush; 

    cout << "for ctag > " << x5_cut_080df << " ctag_eff = " << x5_080df << " (target = 0.80)"
         << " mis-tag = "<< y5_080df << " (target = 0.60)" << endl << flush;


    rocCurveCUDS_cvl->SetLineColor(kViolet-2);
    rocCurveCUDS_cvl->SetLineWidth(5);
    rocCurveCUDS_cvl->SetLineStyle(3);
    //rocCurveCUDS_cvl->Draw("same");

    rocCurveCB_cvb->SetLineColor(kOrange-3);
    rocCurveCB_cvb->SetLineWidth(5);
    rocCurveCB_cvb->SetLineStyle(3);
    //rocCurveCB_cvb->Draw("same");

    rocCurveBUDS_b->SetLineColor(kBlue);
    rocCurveBUDS_b->SetLineWidth(5);
    rocCurveBUDS_b->SetLineStyle(3);
    //rocCurveBUDS_b->Draw("same");

    rocCurveBC_b->SetLineColor(kTeal+3);
    rocCurveBC_b->SetLineWidth(5);
    rocCurveBC_b->SetLineStyle(3);
    //rocCurveBC_b->Draw("same");

    TF1 *ldf = new TF1("ldf", "x",0.08,1);
    ldf->SetLineColor(kBlack);
    ldf->Draw("same");





    // Data points
    // Define the data points using std::vector of std::pairs
    std::vector<std::pair<double, double>> dataPoints1df = {
        {0.20724160632, 0.000500568281832},
        {0.235802200158, 0.00101243401142},
        {0.25364276705, 0.00148503004894},
        {0.272666204228, 0.00215147859874},
        {0.294059621656, 0.00311701447667},
        {0.309513249584, 0.00414165123147},
        {0.321394948423, 0.00498510624459},
        {0.333276647262, 0.00600033244736},
        {0.346343336227, 0.00722231136355},
        {0.366536924655, 0.0095964567944},
        {0.383167063351, 0.0121360878626},
        {0.399792962369, 0.0149731459901},
        {0.416416741548, 0.0182465465657},
        {0.431855530602, 0.0222355717225},
        {0.447290079977, 0.0264351919781},
        {0.466285959245, 0.0326149574103},
        {0.485279718674, 0.0397451771003},
        {0.499525038245, 0.0460983257042},
        {0.51733168771, 0.0554863358815},
        {0.533949107371, 0.0651558610364},
        {0.548190187264, 0.0737260134827},
        {0.568366816979, 0.0887404539061},
        {0.583792886997, 0.100412760987},
        {0.596846856926, 0.112224956423},
        {0.626509767159, 0.140181440602},
        {0.675151597947, 0.195700587218},
        {0.70955446868, 0.244451778974},
        {0.755813600182, 0.316879726374},
        {0.816301092542, 0.431581292992},
        {0.864925964615, 0.545796079096},
        {0.912363726724, 0.681759949669},
        {0.949125978512, 0.800569290351},
        {0.969285649513, 0.872903049548},
        {0.988260330389, 0.951772373851},
        {1.000118711, 1},
        {0.219144503551, 0.000681759949669},
        {0.245316038586, 0.00123377040111},
        {0.282171563299, 0.0024953860676},
        {0.653796337624, 0.168729652949},
        {0.733277589413, 0.280044592696},
        {0.787838011308, 0.37672862678},
        {0.840019973596, 0.482350961403},
        {0.891016945759, 0.617586329859},
        {0.261967375674, 0.00176550686112},
        {0.225097012087, 0.000800569290351}
    };

    // Sort the vector by the first element of the pair (x value)
    std::sort(dataPoints1df.begin(), dataPoints1df.end());

    // Prepare arrays to hold sorted x and y values for TGraph
    const int nPoints1df = dataPoints1df.size();
    double x1df[nPoints1df], y1df[nPoints1df];
    for (int i = 0; i < nPoints1df; ++i) {
        x1df[i] = dataPoints1df[i].first;
        y1df[i] = dataPoints1df[i].second;
    }

    // Create a TGraph
    TGraph *graph1df = new TGraph(nPoints1df, x1df, y1df);
    graph1df->SetTitle("Data Points;X values;Y values");
    graph1df->SetLineWidth(2);
    graph1df->SetLineColor(kPink-3);

    // Draw the graph
    //graph1df->Draw("same");


        std::vector<std::pair<double, double>> dataPoints2df = {
        {0.0031347962382445027, 0.0003645211863014662},
        {0.004702194357366768, 0.0004471057441071598},
        {0.004702194357366768, 0.0005484106771534533},
        {0.006269592476489005, 0.0007142994776918197},
        {0.007836990595611298, 0.0009416123691642899},
        {0.010971786833855773, 0.0013023429535611785},
        {0.014106583072100304, 0.0015042419803248561},
        {0.017241379310344834, 0.002055670593132338},
        {0.02037617554858931, 0.0026138760763488723},
        {0.025078369905956105, 0.0033235964526577883},
        {0.032915360501567376, 0.005121456461841465},
        {0.040752351097178674, 0.006670143926840944},
        {0.04858934169278997, 0.008687142092539846},
        {0.05799373040752351, 0.011178745686715013},
        {0.07366771159874608, 0.01602629150838806},
        {0.08620689655172412, 0.02013251591012392},
        {0.10971786833855796, 0.028860052989869205},
        {0.13009404388714735, 0.037132657437310194},
        {0.16457680250783702, 0.05258725102490756},
        {0.17711598746081503, 0.06000761296549203},
        {0.19905956112852663, 0.07183775185384043},
        {0.24608150470219436, 0.10050654809487614},
        {0.30407523510971785, 0.13891890345984237},
        {0.38087774294670845, 0.19901342640323774},
        {0.438871473354232, 0.24986776708087594},
        {0.5015673981191222, 0.3062518908537716},
        {0.5329153605015673, 0.3370189759545361},
        {0.5768025078369905, 0.37983877028516294},
        {0.6018808777429467, 0.4081058266966143},
        {0.6363636363636362, 0.4437257422014454},
        {0.6943573667711598, 0.506061563428159},
        {0.7758620689655171, 0.5981658144525434},
        {0.8322884012539185, 0.6660145433404081},
        {0.8683385579937304, 0.7154840765085432},
        {0.9231974921630093, 0.8062833011385832},
        {0.9545454545454544, 0.866220501907806},
        {0.9733542319749215, 0.9086568208256768},
        {0.9890282131661443, 0.9532080006358582},
        {0.9984326018808778, 0.9762777579765805},
        {0.3432601880877743, 0.16828103104263495},
        {0.2695924764890282, 0.11467348092877286}
    };

    // Sort the vector by the first element of the pair (x value)
    std::sort(dataPoints2df.begin(), dataPoints2df.end());

    // Prepare arrays to hold sorted x and y values for TGraph
    const int nPoints2df = dataPoints2df.size();
    double x2df[nPoints2df], y2df[nPoints2df];
    for (int i = 0; i < nPoints2df; ++i) {
        x2df[i] = dataPoints2df[i].first;
        y2df[i] = dataPoints2df[i].second;
    }

    // Create a TGraph
    TGraph *graph2df = new TGraph(nPoints2df, x2df, y2df);
    graph2df->SetTitle("Sorted Data Points;X values;Y values");
    //graph2->SetLineColor(kBlack);

    // Draw the graph
    //graph2->Draw("same");


        // Define the data points using std::vector of std::pairs
    std::vector<std::pair<double, double>> dataPoints3df = {
        {0.0031347962382445027, 0.0003558672254837294},
        {0.0031347962382445027, 0.0004261366249881465},
        {0.0031347962382445027, 0.0005617574774363089},
        {0.0031347962382445027, 0.0007494907085085303},
        {0.0031347962382445027, 0.0009880211769767852},
        {0.004702194357366768, 0.0013181822726623408},
        {0.006269592476489005, 0.0017376699430927893},
        {0.007836990595611298, 0.0024324620192908313},
        {0.009404388714733536, 0.003168257698597744},
        {0.010971786833855773, 0.003933012843160524},
        {0.01567398119122254, 0.005571923937539945},
        {0.018808777429467072, 0.006916746631369037},
        {0.021943573667711602, 0.00798903285937508},
        {0.025078369905956105, 0.010037100825125926},
        {0.029780564263322873, 0.012163596765526793},
        {0.036050156739811906, 0.014918493029340972},
        {0.043887147335423204, 0.017649302441581277},
        {0.05015673981191221, 0.020880375892949585},
        {0.059561128526645746, 0.025608544680885987},
        {0.07053291536050155, 0.030661155939055745},
        {0.08620689655172412, 0.03898114330688804},
        {0.10031347962382445, 0.04556244905963141},
        {0.11442006269592475, 0.053898532255385656},
        {0.13322884012539182, 0.06452673275634156},
        {0.15830721003134796, 0.07724487976474907},
        {0.17711598746081503, 0.08813793540216434},
        {0.2006269592476489, 0.10177682598335083},
        {0.23197492163009403, 0.12182774842077193},
        {0.26332288401253917, 0.14236680876090327},
        {0.2884012539184953, 0.1585748934437759},
        {0.3260188087774294, 0.1875347012687284},
        {0.3510971786833856, 0.20392596985800243},
        {0.3840125391849529, 0.23264413506696527},
        {0.41379310344827575, 0.2529638548651877},
        {0.43416927899686514, 0.2718044158019051},
        {0.45611285266457674, 0.28855524741653105},
        {0.48746081504702193, 0.317544468768884},
        {0.518808777429467, 0.34944604386333533},
        {0.5517241379310345, 0.37995322484971245},
        {0.5783699059561127, 0.408221111963394},
        {0.5987460815047021, 0.42821188416054184},
        {0.6489028213166144, 0.4768189977077838},
        {0.6818181818181817, 0.5122549526640878},
        {0.713166144200627, 0.550334778823825},
        {0.7727272727272727, 0.6201405335491128},
        {0.7460815047021943, 0.5841739457319345},
        {0.6269592476489028, 0.45456759581431183},
        {0.8040752351097178, 0.658284335115702},
        {0.847962382445141, 0.715659240527625},
        {0.8808777429467083, 0.759663932619414},
        {0.9106583072100314, 0.80640476827233},
        {0.9388714733542318, 0.8560376073759793},
        {0.9733542319749215, 0.9196387919377691},
        {0.9921630094043887, 0.964692083770465},
        {0.9984326018808778, 1.0000188300949049}
    };

    // Sort the vector by the first element of the pair (x value)
    std::sort(dataPoints3df.begin(), dataPoints3df.end());

    // Prepare arrays to hold sorted x and y values for TGraph
    const int nPoints3df = dataPoints3df.size();
    double x3df[nPoints3df], y3df[nPoints3df];
    for (int i = 0; i < nPoints3; ++i) {
        x3df[i] = dataPoints3df[i].first;
        y3df[i] = dataPoints3df[i].second;
    }

    // Create a TGraph
    TGraph *graph3df = new TGraph(nPoints3df, x3df, y3df);
    graph3df->SetTitle("Sorted Data Points;X values;Y values");
    //graph3->SetLineColor(kRed);
    //graph3->Draw("same");


    double xMin2df = std::min(graph2df->GetX()[0], graph3df->GetX()[0]);
    double xMax2df = std::max(graph2df->GetX()[graph2df->GetN() - 1], graph3df->GetX()[graph3df->GetN() - 1]);
    int numPointsdf = 100; // Choose an appropriate number of points
    std::vector<double> xCommondf(numPointsdf), yAvgdf(numPointsdf);

    double deltaXdf = (xMax2df - xMin2df) / (numPointsdf - 1);

    for (int i = 0; i < numPointsdf; i++) {
        double xValue = xMin2df + i * deltaXdf;
        double y1 = interpolate(graph2df, xValue);
        double y2 = interpolate(graph3df, xValue);
        yAvgdf[i] = (y1 + y2) / 2.0;
        xCommondf[i] = xValue;
    }











    // Define the specific x-coordinates where grid lines should appear
    double gridXPositionspn[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    int nXPositionspn = sizeof(gridXPositionspn) / sizeof(gridXPositionspn[0]);

    // Define the specific y-coordinates where grid lines should appear
    double gridYPositionspn[] = {0.0006, 0.0007, 0.0008, 0.0009, 0.001, 0.002, 0.003, 0.004, 0.005,
    0.006, 0.007, 0.008, 0.009, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.1,
    0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    int nYPositionspn = sizeof(gridYPositionspn) / sizeof(gridYPositionspn[0]);

    // Get x-axis range to draw lines
    double xMinpn = h2->GetXaxis()->GetXmin();
    double xMaxpn = h2->GetXaxis()->GetXmax();

    // Get y-axis range to draw lines
    double yMinpn = h2->GetMinimum();
    double yMaxpn = h2->GetMaximum();

    // Draw vertical grid lines at specified x-positions
    for (int i = 0; i < nXPositionspn; i++) {
        TLine *line = new TLine(gridXPositionspn[i], yMinpn, gridXPositionspn[i], yMaxpn);
        line->SetLineColor(kBlack); // Set line color to gray
        line->SetLineStyle(3); // Dashed line for distinction
        line->Draw("same");
    }
    // Draw horizontal grid lines at specified y-positions
    for (int i = 0; i < nYPositionspn; i++) {
        TLine *line = new TLine(xMinpn, gridYPositionspn[i], xMaxpn, gridYPositionspn[i]);
        line->SetLineColor(kBlack); // Set line color to gray
        line->SetLineStyle(3); // Dashed line for distinction
        line->Draw("same");
    }

    gPad->Update();

    // Create ROC curve data


    TGraph *rocCurveCUDS_cvlp = new TGraph(100);
    TGraph *rocCurveCB_cvbp = new TGraph(100);
    TGraph *rocCurveBUDS_bp = new TGraph(100);
    TGraph *rocCurveBC_bp = new TGraph(100);


    double dx5_minpn(1), x5_020pn(1), x5_cut_020pn(1), y5_020pn(1);
    double dx5_min2pn(1), x5_080pn(1), x5_cut_080pn(1), y5_080pn(1);
    for (int i = 0; i < 100; ++i) {
        double y5 = h_c_udstag_cvl_pn30c->Integral(i, 100);
        double x5 = h_c_ctag_cvl_pn30c->Integral(i, 100);
        rocCurveCUDS_cvlp->SetPoint(i, x5, y5);

        double y6 = h_c_btag_cvb_pn30c->Integral(i, 100);
        double x6 = h_c_ctag_cvb_pn30c->Integral(i, 100);
        rocCurveCB_cvbp->SetPoint(i, x6, y6);

        double y7 = h_b_udstag_b_pn30c->Integral(i, 100);
        double x7 = h_b_btag_b_pn30c->Integral(i, 100);
        rocCurveBUDS_bp->SetPoint(i, x7, y7);

        double y8 = h_b_ctag_b_pn30c->Integral(i, 100);
        double x8 = h_b_btag_b_pn30c->Integral(i, 100);
        rocCurveBC_bp->SetPoint(i, x8, y8);

        if (fabs(x5-0.2)< dx5_minpn){
            x5_cut_020pn = h_c_ctag_cvl_pn30c->GetBinLowEdge(i);
            x5_020pn = x5;
            dx5_minpn = fabs(x5 - 0.2);
            y5_020pn = y5;
        }

        if (fabs(x5-0.8)< dx5_min2){
            x5_cut_080pn = h_c_ctag_cvl_pn30c->GetBinLowEdge(i);
            x5_080pn = x5;
            dx5_min2pn = fabs(x5 - 0.8);
            y5_080pn = y5;
        }
    }
    cout << "for ctag > " << x5_cut_020pn << " ctag_eff = " << x5_020pn << " (target = 0.20)"
         << " mis-tag = "<< y5_020pn << " (target = 0.01)" << endl << flush; 

    cout << "for ctag > " << x5_cut_080pn << " ctag_eff = " << x5_080pn << " (target = 0.80)"
         << " mis-tag = "<< y5_080pn << " (target = 0.60)" << endl << flush;


    rocCurveCUDS_cvlp->SetLineColor(kViolet-2);
    rocCurveCUDS_cvlp->SetLineWidth(4);
    rocCurveCUDS_cvlp->SetLineStyle(2);
    //rocCurveCUDS_cvlp->Draw("same");

    rocCurveCB_cvbp->SetLineColor(kOrange-3);
    rocCurveCB_cvbp->SetLineWidth(4);
    rocCurveCB_cvbp->SetLineStyle(2);
    //rocCurveCB_cvbp->Draw("same");

    rocCurveBUDS_bp->SetLineColor(kGreen+1);
    rocCurveBUDS_bp->SetLineWidth(2);
    rocCurveBUDS_bp->SetLineStyle(1);
    rocCurveBUDS_bp->Draw("same");

    rocCurveBC_bp->SetLineColor(kAzure+7);
    rocCurveBC_bp->SetLineWidth(2);
    rocCurveBC_bp->SetLineStyle(1);
    rocCurveBC_bp->Draw("same");

    TF1 *lpn = new TF1("lpn", "x",0.08,1);
    lpn->SetLineColor(kBlack);
    //lpn->Draw("same");





    // Data points
    // Define the data points using std::vector of std::pairs
    std::vector<std::pair<double, double>> dataPoints1pn = {
        {0.20724160632, 0.000500568281832},
        {0.235802200158, 0.00101243401142},
        {0.25364276705, 0.00148503004894},
        {0.272666204228, 0.00215147859874},
        {0.294059621656, 0.00311701447667},
        {0.309513249584, 0.00414165123147},
        {0.321394948423, 0.00498510624459},
        {0.333276647262, 0.00600033244736},
        {0.346343336227, 0.00722231136355},
        {0.366536924655, 0.0095964567944},
        {0.383167063351, 0.0121360878626},
        {0.399792962369, 0.0149731459901},
        {0.416416741548, 0.0182465465657},
        {0.431855530602, 0.0222355717225},
        {0.447290079977, 0.0264351919781},
        {0.466285959245, 0.0326149574103},
        {0.485279718674, 0.0397451771003},
        {0.499525038245, 0.0460983257042},
        {0.51733168771, 0.0554863358815},
        {0.533949107371, 0.0651558610364},
        {0.548190187264, 0.0737260134827},
        {0.568366816979, 0.0887404539061},
        {0.583792886997, 0.100412760987},
        {0.596846856926, 0.112224956423},
        {0.626509767159, 0.140181440602},
        {0.675151597947, 0.195700587218},
        {0.70955446868, 0.244451778974},
        {0.755813600182, 0.316879726374},
        {0.816301092542, 0.431581292992},
        {0.864925964615, 0.545796079096},
        {0.912363726724, 0.681759949669},
        {0.949125978512, 0.800569290351},
        {0.969285649513, 0.872903049548},
        {0.988260330389, 0.951772373851},
        {1.000118711, 1},
        {0.219144503551, 0.000681759949669},
        {0.245316038586, 0.00123377040111},
        {0.282171563299, 0.0024953860676},
        {0.653796337624, 0.168729652949},
        {0.733277589413, 0.280044592696},
        {0.787838011308, 0.37672862678},
        {0.840019973596, 0.482350961403},
        {0.891016945759, 0.617586329859},
        {0.261967375674, 0.00176550686112},
        {0.225097012087, 0.000800569290351}
    };

    // Sort the vector by the first element of the pair (x value)
    std::sort(dataPoints1pn.begin(), dataPoints1pn.end());

    // Prepare arrays to hold sorted x and y values for TGraph
    const int nPoints1pn = dataPoints1pn.size();
    double x1pn[nPoints1pn], y1pn[nPoints1pn];
    for (int i = 0; i < nPoints1; ++i) {
        x1pn[i] = dataPoints1pn[i].first;
        y1pn[i] = dataPoints1pn[i].second;
    }

    // Create a TGraph
    TGraph *graph1pn = new TGraph(nPoints1pn, x1pn, y1pn);
    graph1pn->SetTitle("Data Points;X values;Y values");
    graph1pn->SetLineWidth(2);
    graph1pn->SetLineColor(kPink-3);

    // Draw the graph
    //graph1pn->Draw("same");


        std::vector<std::pair<double, double>> dataPoints2pn = {
        {0.0031347962382445027, 0.0003645211863014662},
        {0.004702194357366768, 0.0004471057441071598},
        {0.004702194357366768, 0.0005484106771534533},
        {0.006269592476489005, 0.0007142994776918197},
        {0.007836990595611298, 0.0009416123691642899},
        {0.010971786833855773, 0.0013023429535611785},
        {0.014106583072100304, 0.0015042419803248561},
        {0.017241379310344834, 0.002055670593132338},
        {0.02037617554858931, 0.0026138760763488723},
        {0.025078369905956105, 0.0033235964526577883},
        {0.032915360501567376, 0.005121456461841465},
        {0.040752351097178674, 0.006670143926840944},
        {0.04858934169278997, 0.008687142092539846},
        {0.05799373040752351, 0.011178745686715013},
        {0.07366771159874608, 0.01602629150838806},
        {0.08620689655172412, 0.02013251591012392},
        {0.10971786833855796, 0.028860052989869205},
        {0.13009404388714735, 0.037132657437310194},
        {0.16457680250783702, 0.05258725102490756},
        {0.17711598746081503, 0.06000761296549203},
        {0.19905956112852663, 0.07183775185384043},
        {0.24608150470219436, 0.10050654809487614},
        {0.30407523510971785, 0.13891890345984237},
        {0.38087774294670845, 0.19901342640323774},
        {0.438871473354232, 0.24986776708087594},
        {0.5015673981191222, 0.3062518908537716},
        {0.5329153605015673, 0.3370189759545361},
        {0.5768025078369905, 0.37983877028516294},
        {0.6018808777429467, 0.4081058266966143},
        {0.6363636363636362, 0.4437257422014454},
        {0.6943573667711598, 0.506061563428159},
        {0.7758620689655171, 0.5981658144525434},
        {0.8322884012539185, 0.6660145433404081},
        {0.8683385579937304, 0.7154840765085432},
        {0.9231974921630093, 0.8062833011385832},
        {0.9545454545454544, 0.866220501907806},
        {0.9733542319749215, 0.9086568208256768},
        {0.9890282131661443, 0.9532080006358582},
        {0.9984326018808778, 0.9762777579765805},
        {0.3432601880877743, 0.16828103104263495},
        {0.2695924764890282, 0.11467348092877286}
    };

    // Sort the vector by the first element of the pair (x value)
    std::sort(dataPoints2pn.begin(), dataPoints2pn.end());

    // Prepare arrays to hold sorted x and y values for TGraph
    const int nPoints2pn = dataPoints2pn.size();
    double x2pn[nPoints2pn], y2pn[nPoints2pn];
    for (int i = 0; i < nPoints2pn; ++i) {
        x2pn[i] = dataPoints2pn[i].first;
        y2pn[i] = dataPoints2pn[i].second;
    }

    // Create a TGraph
    TGraph *graph2pn = new TGraph(nPoints2pn, x2pn, y2pn);
    graph2pn->SetTitle("Sorted Data Points;X values;Y values");
    //graph2->SetLineColor(kBlack);

    // Draw the graph
    //graph2->Draw("same");


        // Define the data points using std::vector of std::pairs
    std::vector<std::pair<double, double>> dataPoints3pn = {
        {0.0031347962382445027, 0.0003558672254837294},
        {0.0031347962382445027, 0.0004261366249881465},
        {0.0031347962382445027, 0.0005617574774363089},
        {0.0031347962382445027, 0.0007494907085085303},
        {0.0031347962382445027, 0.0009880211769767852},
        {0.004702194357366768, 0.0013181822726623408},
        {0.006269592476489005, 0.0017376699430927893},
        {0.007836990595611298, 0.0024324620192908313},
        {0.009404388714733536, 0.003168257698597744},
        {0.010971786833855773, 0.003933012843160524},
        {0.01567398119122254, 0.005571923937539945},
        {0.018808777429467072, 0.006916746631369037},
        {0.021943573667711602, 0.00798903285937508},
        {0.025078369905956105, 0.010037100825125926},
        {0.029780564263322873, 0.012163596765526793},
        {0.036050156739811906, 0.014918493029340972},
        {0.043887147335423204, 0.017649302441581277},
        {0.05015673981191221, 0.020880375892949585},
        {0.059561128526645746, 0.025608544680885987},
        {0.07053291536050155, 0.030661155939055745},
        {0.08620689655172412, 0.03898114330688804},
        {0.10031347962382445, 0.04556244905963141},
        {0.11442006269592475, 0.053898532255385656},
        {0.13322884012539182, 0.06452673275634156},
        {0.15830721003134796, 0.07724487976474907},
        {0.17711598746081503, 0.08813793540216434},
        {0.2006269592476489, 0.10177682598335083},
        {0.23197492163009403, 0.12182774842077193},
        {0.26332288401253917, 0.14236680876090327},
        {0.2884012539184953, 0.1585748934437759},
        {0.3260188087774294, 0.1875347012687284},
        {0.3510971786833856, 0.20392596985800243},
        {0.3840125391849529, 0.23264413506696527},
        {0.41379310344827575, 0.2529638548651877},
        {0.43416927899686514, 0.2718044158019051},
        {0.45611285266457674, 0.28855524741653105},
        {0.48746081504702193, 0.317544468768884},
        {0.518808777429467, 0.34944604386333533},
        {0.5517241379310345, 0.37995322484971245},
        {0.5783699059561127, 0.408221111963394},
        {0.5987460815047021, 0.42821188416054184},
        {0.6489028213166144, 0.4768189977077838},
        {0.6818181818181817, 0.5122549526640878},
        {0.713166144200627, 0.550334778823825},
        {0.7727272727272727, 0.6201405335491128},
        {0.7460815047021943, 0.5841739457319345},
        {0.6269592476489028, 0.45456759581431183},
        {0.8040752351097178, 0.658284335115702},
        {0.847962382445141, 0.715659240527625},
        {0.8808777429467083, 0.759663932619414},
        {0.9106583072100314, 0.80640476827233},
        {0.9388714733542318, 0.8560376073759793},
        {0.9733542319749215, 0.9196387919377691},
        {0.9921630094043887, 0.964692083770465},
        {0.9984326018808778, 1.0000188300949049}
    };

    // Sort the vector by the first element of the pair (x value)
    std::sort(dataPoints3pn.begin(), dataPoints3pn.end());

    // Prepare arrays to hold sorted x and y values for TGraph
    const int nPoints3pn = dataPoints3pn.size();
    double x3pn[nPoints3pn], y3pn[nPoints3pn];
    for (int i = 0; i < nPoints3; ++i) {
        x3pn[i] = dataPoints3pn[i].first;
        y3pn[i] = dataPoints3pn[i].second;
    }

    // Create a TGraph
    TGraph *graph3pn = new TGraph(nPoints3pn, x3pn, y3pn);
    graph3pn->SetTitle("Sorted Data Points;X values;Y values");
    //graph3->SetLineColor(kRed);
    //graph3->Draw("same");


    double xMin2pn = std::min(graph2pn->GetX()[0], graph3pn->GetX()[0]);
    double xMax2pn = std::max(graph2pn->GetX()[graph2pn->GetN() - 1], graph3pn->GetX()[graph3pn->GetN() - 1]);
    int numPointspn = 100; // Choose an appropriate number of points
    std::vector<double> xCommonpn(numPointspn), yAvgpn(numPointspn);

    double deltaXpn = (xMax2pn - xMin2pn) / (numPointspn - 1);

    for (int i = 0; i < numPointspn; i++) {
        double xValue = xMin2pn + i * deltaXpn;
        double y1 = interpolate(graph2pn, xValue);
        double y2 = interpolate(graph3pn, xValue);
        yAvgpn[i] = (y1 + y2) / 2.0;
        xCommonpn[i] = xValue;
    }


    TLegend *leg2 = tdrLeg(0.77,0.85-0.1*3,0.95,0.85);
    //leg2->AddEntry(rocCurveSUD, "s vs ud", "L");
    //leg2->AddEntry(graphAvg, "s vs ud (ref)", "L");
    leg2->AddEntry(rocCurveCUDS, "#splitline{c vs uds}{(ctag Run2)}", "L");
    //leg2->AddEntry(rocCurveCUDS_cvl, "c vs udsg (DF)", "L");
    //leg2->AddEntry(rocCurveCUDS_cvlp, "c vs udsg (PN)", "L");

    //leg2->AddEntry(graph1, "c vs uds (ref t#bar{t})", "L");

    
    //leg2->AddEntry(rocCurveCB_cvb, "c vs b (DF)", "L");
    //leg2->AddEntry(rocCurveCB_cvbp, "c vs b (PN)", "L");
    //leg2->AddEntry(rocCurveBUDS_b, "b vs udsg (DF)", "L");
        leg2->AddEntry(rocCurveBC_bp, "#splitline{b vs c}{(ParticleNet Run3)}", "L");
    leg2->AddEntry(rocCurveBUDS_bp, "#splitline{b vs udsg}{(ParticleNet Run3)}", "L");
    //leg2->AddEntry(rocCurveBC_b, "b vs c (DF)", "L");
    //leg2->AddEntry(graph1df, "c vs uds (ref t#bar{t})", "L");

    //leg2->AddEntry(graph1pn, "c vs uds (ref t#bar{t})", "L");

    leg2->SetTextSize(0.03);

    leg2->Draw();

    // Update the canvas to reflect the changes
    gPad->Update();

    //gPad->SetRightMargin(0.10);
    //gPad->SetLeftMargin(0.10);
    //gPad->SetTopMargin(0.10);
    //gPad->SetBottomMargin(0.10);




    // Update canvas to reflect changes
    c2->SetRightMargin(0.23);
    c2->Modified();
    c2->Update();
       // Save the canvas
    c2->SaveAs("pdf/ROC_Curvesall2_test2.pdf");
}