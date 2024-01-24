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

// Define the formula based on the equation
Double_t myfunction(Double_t *x, Double_t *par) {
   Double_t pT = x[0]; // Transverse momentum
   Double_t m = par[3]; //0.135; // Pion mass
   Double_t n = par[1]; //7.7; // Power coefficient
   Double_t T = par[2]; //0.13; // Inverse slope parameter
   double c0 = par[0];
   double cjet = par[4];
   double njet = par[5];
   
   // Calculate mT from the equation
   Double_t mT = sqrt(m*m + pT*pT);
   
   // Calculate C from the equation
   Double_t C = ((n - 1)*(n - 2)) / (n * T * (n * T + (n - 2) * m ));
   
   // Return the function value
   Double_t f = c0 * C * pT * pow(1 + (mT - m) / (n * T), -n);
   double fjet = cjet * pow(pT,njet);
   return f + fjet;
}

void myfit() {
    // Open the ROOT file and get the histogram
   TFile *file = new TFile("output.root", "READ");
   TH1D *h = (TH1D*)file->Get("h");

   // Create the fitting function over the range of the histogram
   TF1 *f1 = new TF1("myfunc", myfunction, 0.1, 100,5);
   f1->SetParameters(1e6,6.6, 0.145, 0.135,1e5,-2);
   f1->FixParameter(3,0.135);

   // Fit the histogram
   h->Fit(f1, "R");

   setTDRStyle();
   lumi_136TeV = "Run3";
   extraText = "Private";
   TH1D *h1 = tdrHist("h1","All jets N fraction ",0 + 1e-4,3000000 -1e-4,"p_{T,cand} (GeV)",0.1,100);
   TCanvas *c1 = tdrCanvas("c1",h1,8,kSquare);
   c1->SetLogy();
   c1->SetLogx();

   // Draw the histogram
   tdrDraw(h,"histe",kFullCircle,kBlack,kSolid,-1,kNone);
   h->SetMarkerSize(0.7);

   // Draw the fit on the same canvas
   f1->SetLineColor(kRed); // Set the fit line color to red for visibility
   f1->Draw("SAME"); // Draw the fit function on top of the histogram

   // Create a legend
   TLegend *leg = tdrLeg(0.70,0.9-0.05*2,0.85,0.9);
   leg->AddEntry(h, "Data", "lep");
   leg->AddEntry(f1, "Fit Function", "l");
   leg->Draw();

   // Update the canvas to reflect the changes
   c1->Update();

   // Save the canvas as a .pdf file
   c1->SaveAs("fit_result.pdf");
}