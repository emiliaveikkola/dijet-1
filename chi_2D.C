#include <TMath.h>
#include <TF1.h>
#include <TH1F.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TProfile2D.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include <TStyle.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <sstream>
#include <TGraphErrors.h>
#include <TLatex.h>
#include "tdrstyle_mod22.C"

void chi_2D() {
    setTDRStyle();

  // Load ROOT libraries
  TFile *file0 = TFile::Open("chi2_hist2_pt.root");
  TFile *file1 = TFile::Open("chi2_hist.root");

  if (!file0 || !file1) {
    std::cerr << "Error: Could not open one or both files." << std::endl;
    return;
  }

  // Access histograms from the files
  TH2D *chi2_hist2 = (TH2D*)file0->Get("chi2_hist2");
  TH2D *chi2_hist = (TH2D*)file1->Get("chi2_hist");

  if (!chi2_hist2 || !chi2_hist) {
    std::cerr << "Error: Could not retrieve one or both histograms." << std::endl;
    return;
  }

  // Clone the first histogram
  TH2D *h2 = (TH2D*)chi2_hist2->Clone("h2");

  // Add the second histogram to the cloned one
  h2->Add(chi2_hist);

  // Draw the combined histogram
  TCanvas *c1 = new TCanvas("c1", "Combined Histogram", 1000, 600);
  c1->SetLogz();
  c1->SetLeftMargin(0.15);
  c1->SetRightMargin(0.2);
  h2->Draw("colz");
  h2->GetZaxis()->SetMoreLogLabels();
  h2->GetZaxis()->SetNoExponent();

TGraph *g2 = new TGraph();

double chi2_min(99999), x_min(-1), y_min(-1);
for (int i = 1; i != chi2_hist2->GetNbinsX()+1; ++i){
    int j = chi2_hist2->GetNbinsY()+1-i;
    double chi2 = chi2_hist2->GetBinContent(i,j);
    double x = chi2_hist2->GetXaxis()->GetBinCenter(i);
    g2->SetPoint(i-1,x,chi2);
    if (chi2 < chi2_min){
        chi2_min = chi2;
        x_min = chi2_hist2->GetXaxis()->GetBinCenter(i);
        y_min = chi2_hist2->GetYaxis()->GetBinCenter(j);
    }
}

//TEllipse *c = new TEllipse(x_min,y_min,0.0025);
//c->Draw();

TGraph *g = new TGraph();
g->SetPoint(0,x_min,y_min);
g->SetMarkerStyle(kFullStar);
g->SetMarkerColor(kOrange+10);
g->SetMarkerSize(3.5);
g->Draw("same p");

    // Move the color axis to the left
  gPad->Update();

  // Save the canvas
  c1->SaveAs("pdf/chi_combined_2D_colz.pdf");

  // Draw the histogram with LEGO2 option
  TCanvas *c2 = new TCanvas("c2", "LEGO2 Histogram", 1000, 600);
  c2->SetLogz();
  h2->Draw("lego2");
  h2->GetZaxis()->SetMoreLogLabels();
  h2->GetZaxis()->SetNoExponent();

  // Adjust axis titles
  h2->GetXaxis()->SetTitleOffset(1.2);
  h2->GetYaxis()->SetTitleOffset(1.4);
  h2->GetZaxis()->SetTitleOffset(1.2);


  // Draw a marker at the minimum point using TGraph2D
  TGraph2D *minMarkerGraph = new TGraph2D();
  minMarkerGraph->SetPoint(0, x_min, y_min, 100);
  minMarkerGraph->SetMarkerStyle(23); // 29 is the star marker style
  minMarkerGraph->SetMarkerColor(kOrange+10);
  minMarkerGraph->SetMarkerSize(2.5);
  minMarkerGraph->Draw("P same");

  // Ensure the marker is drawn
  gPad->Modified();
  gPad->Update();


  gPad->SetTheta(35); // Adjust these values as needed
  gPad->SetPhi(-35);   // Adjust these values as needed
  gPad->SetRightMargin(1);

  gPad->Update();

  // Save the canvas
c2->SaveAs("pdf/chi_combined_2D_lego2.pdf");
}