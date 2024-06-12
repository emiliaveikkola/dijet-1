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
  for (int i = 1; i <= 21; ++i) {
        for (int j = 1; j <= 21; ++j) {
            h2->SetBinError(i,j,sqrt(47 + 30));
        }
    }

  // Draw the combined histogram
  TCanvas *c1 = new TCanvas("c1", "Combined Histogram", 1000, 600);
  c1->SetLogz();
  c1->SetLeftMargin(0.15);
  c1->SetRightMargin(0.2);

  h2->Draw("colz");
  h2->GetZaxis()->SetMoreLogLabels();
  h2->GetZaxis()->SetNoExponent();

  TLine *l = new TLine();
  l->DrawLine(0.95-0.0025,0.95-0.0025,1.05+0.0025,1.05+0.0025);
  l->SetLineStyle(kDotted);
  l->DrawLine(1,0.95-0.0025,1,1.05+0.0025);
  l->DrawLine(0.95-0.0025,1.0,1.05+0.0025,1.0);;

  TLine *l2 = new TLine();
  l2->DrawLine(0.95-0.0025,1.05+0.0025,1.05+0.0025,0.95-0.0025);
  l2->SetLineStyle(kDotted);
  l2->DrawLine(1,0.95-0.0025,1,1.05+0.0025);
  l2->DrawLine(0.95-0.0025,1.0,1.05+0.0025,1.0);


  // Find the minimum z-value and its corresponding x and y values
  int minBinX = -1, minBinY = -1;
  double minZ = h2->GetMinimum();
  double minX, minY;
  
  for (int i = 1; i <= h2->GetNbinsX(); ++i) {
    for (int j = 1; j <= h2->GetNbinsY(); ++j) {
      double z = h2->GetBinContent(i, j);
      if (z == minZ) {
        minBinX = i;
        minBinY = j;
        break;
      }
    }
  }

  if (minBinX != -1 && minBinY != -1) {
    minX = h2->GetXaxis()->GetBinCenter(minBinX);
    minY = h2->GetYaxis()->GetBinCenter(minBinY);
    std::cout << "Minimum Z-value: " << minZ << std::endl;
    std::cout << "Corresponding X-value: " << minX << std::endl;
    std::cout << "Corresponding Y-value: " << minY << std::endl;
  } else {
    std::cerr << "Error: Could not find the minimum z-value in the histogram." << std::endl;
  }


TGraph *g = new TGraph();
g->SetPoint(0,minX,minY);
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
  minMarkerGraph->SetPoint(0, minX, minY, 100);
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