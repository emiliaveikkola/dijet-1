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

void allleadslead() {
    // Open the ROOT file and get the histogram
    TFile *file = new TFile("output_x.root", "READ");
    TH1D *h_all = (TH1D*)file->Get("h_all");
    TH1D *h_all_lead = (TH1D*)file->Get("h_all_lead");
    TH1D *h_s_lead = (TH1D*)file->Get("h_s_lead");
    TH1D *h_all_s_vs_ptslead = (TH1D*)file->Get("h_all_s_vs_ptslead");

       // Create the fitting function over the range of the histogram
    TF1 *f1 = new TF1("f1", "gaus", 0.1, 100);
    TF1 *f2 = new TF1("f2", "gaus", 0.1, 100);
    TF1 *f3 = new TF1("f3", "gaus", 0.1, 100);
    TF1 *f4 = new TF1("f4", "gaus", 0.1, 100);

  /* // Fit the histogram
   h_all->Fit(f1, "R");
   h_all_lead->Fit(f2, "R");
   h_all_s_vs_ptslead->Fit(f3, "R");
   h_s_lead->Fit(f4, "R");
*/
    setTDRStyle();
    lumi_136TeV = "Run3";
    extraText = "Private";
    TH1D *h1 = tdrHist("h1","All jets N fraction ",0 + 1e-4,250,"p_{T,cand} (GeV)",0.1,70);
    TCanvas *c1 = tdrCanvas("c1",h1,8,kSquare);
    c1->SetLogy();
    //c1->SetLogx();

    // Draw the histogram
    tdrDraw(h_all,"histe",kFullCircle,kGreen+2,kSolid,-1,kNone);
    h_all->SetMarkerSize(1.5);

    tdrDraw(h_all_lead,"histe",kFullSquare,kRed,kSolid,-1,kNone);
    h_all_lead->SetMarkerSize(1.5);

    tdrDraw(h_all_s_vs_ptslead,"histe",kFullDiamond,kBlue,kSolid,-1,kNone);
    h_all_s_vs_ptslead->SetMarkerSize(1.75);

    tdrDraw(h_s_lead,"histe",kFullSquare,kBlack,kSolid,-1,kNone);
    h_s_lead->SetMarkerSize(1.5);

    /*// Draw the fit on the same canvas
    f1->SetLineColor(kGreen+2); // Set the fit line color to red for visibility
    f1->Draw("SAME"); // Draw the fit function on top of the histogram

    f2->SetLineColor(kRed); // Set the fit line color to red for visibility
    f2->Draw("SAME"); // Draw the fit function on top of the histogram

    f3->SetLineColor(kBlue); // Set the fit line color to red for visibility
    f3->Draw("SAME"); // Draw the fit function on top of the histogram

    f4->SetLineColor(kBlack); // Set the fit line color to red for visibility
    f4->Draw("SAME"); // Draw the fit function on top of the histogram
*/
    // Create a legend
    TLegend *leg = tdrLeg(0.70,0.9-0.05*6,0.85,0.9);
    leg->AddEntry(h_all, "h_all", "lep");
    //leg->AddEntry(f1, "Fit Function", "l");
    leg->AddEntry(h_all_lead, "h_all_lead", "lep");
    //leg->AddEntry(f2, "Fit Function", "l");
    leg->AddEntry(h_s_lead, "h_s_lead", "lep");
    //leg->AddEntry(f4, "Fit Function", "l");
    leg->AddEntry(h_all_s_vs_ptslead, "h_all_s_vs_ptslead", "lep");
    //leg->AddEntry(f3, "Fit Function", "l");
    leg->Draw();

    // Update the canvas to reflect the changes
    c1->Update();

    // Save the canvas as a .pdf file
    c1->SaveAs("pdf/all,lead,slead.pdf");
}