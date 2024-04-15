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

void JetPairs() {
    setTDRStyle();
    // Open the ROOT file and get the histogram
    TFile *file = new TFile("output_stag.root", "READ");

    TH1D *hJetPairs = (TH1D*)file->Get("hJetPairs");
    
    lumi_136TeV = "Run3 simulation";
    extraText = "Private";
    TH1D *h1 = tdrHist("h1","N fraction",0,1,"Jet pair",1,8);
    TCanvas *c1 = tdrCanvas("c1",h1,8,11,kSquare);
    //gPad->SetLogy();
    //c1->SetLogx();
    h1->GetXaxis()->SetBinLabel(1, "cs");
    h1->GetXaxis()->SetBinLabel(2, "ud");
    h1->GetXaxis()->SetBinLabel(3, "cd");
    h1->GetXaxis()->SetBinLabel(4, "us");
    h1->GetXaxis()->SetBinLabel(5, "cb");
    h1->GetXaxis()->SetBinLabel(6, "ub");
    h1->GetXaxis()->SetBinLabel(7, "x");

    // Calculate the sum of bins up to the 6th bin
    double sumOfBins = 0;
    for (int i = 1; i <= 6; ++i) {  // bins are indexed from 1
        sumOfBins += hJetPairs->GetBinContent(i);
    }

    // Scale each bin by the sum of bins from 1 to 6
    for (int i = 1; i <= 7; ++i) {
        double originalContent = hJetPairs->GetBinContent(i);
        double scaledContent = originalContent / sumOfBins;
        hJetPairs->SetBinContent(i, scaledContent);
    }

    // Draw the histogram
    tdrDraw(hJetPairs,"HPz",kNone,kOrange-2,kSolid,-1,1001,kOrange-2);
    hJetPairs->SetFillColorAlpha(kOrange-2,0.25);



    // Create a legend
    TLegend *leg = tdrLeg(0.5,0.8-0.05*1,0.7,0.82);
    leg->AddEntry(hJetPairs, "Scaled jet pairs", "FPLE");
    
    //leg->Draw();

    // Update the canvas to reflect the changes
    gPad->Update();

    // Save the canvas as a .pdf file
    c1->SaveAs("pdf/jetpairs.pdf");
}