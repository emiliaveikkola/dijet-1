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

void JetPairs_cs_vs_ud() {
    setTDRStyle();
    // Open the ROOT file and get the histogram
    TFile *file = new TFile("output_stag3.root", "READ");
    TFile *file_cs = new TFile("output_stag_cs_0.2.root", "READ");
    TFile *file_ud = new TFile("output_stag_ud_0.2.root", "READ");

    TH1D *hJetPairs = (TH1D*)file->Get("hJetPairs");
    TH1D *hJetPairs_scaled = (TH1D*)file->Get("hJetPairs_scaled");

    TH1D *cs_hJetPairs = (TH1D*)file_cs->Get("cs_hJetPairs");
    TH1D *cs_hJetPairs_scaled = (TH1D*)file_cs->Get("cs_hJetPairs_scaled");

    TH1D *ud_hJetPairs = (TH1D*)file_ud->Get("ud_hJetPairs");
    TH1D *ud_hJetPairs_scaled = (TH1D*)file_ud->Get("ud_hJetPairs_scaled");


    
    lumi_136TeV = "Run3 simulation";
    extraText = "Private";

    TH1D *h1 = tdrHist("h1","N fraction, reco scaled",0,1.2,"Jet pair",1,8);
    TCanvas *c1 = tdrCanvas("c1",h1,8,11,kSquare);
    //gPad->SetLogy();
    //c1->SetLogx();
    h1->GetXaxis()->SetBinLabel(1, "cs");
    h1->GetXaxis()->SetBinLabel(2, "ud");
    h1->GetXaxis()->SetBinLabel(3, "cd");
    h1->GetXaxis()->SetBinLabel(4, "us");
    h1->GetXaxis()->SetBinLabel(5, "cb");
    h1->GetXaxis()->SetBinLabel(6, "ub");
    h1->GetXaxis()->SetBinLabel(7, "x*");

    // Calculate the sum of bins from 1 to 7
    double sumOfBins1to7 = 0;
    for (int i = 1; i <= 7; ++i) {  // Bins are indexed from 1
        sumOfBins1to7 += hJetPairs->GetBinContent(i);
    }

    // Scale each bin by the sum of bins from 1 to 7
    for (int i = 1; i <= 7; ++i) {
        double originalContent = hJetPairs->GetBinContent(i);
        double scaledContent = originalContent / sumOfBins1to7;
        hJetPairs->SetBinContent(i, scaledContent);
    }

    // Recalculate the sum for bins 1 to 6 after initial scaling
    double sumOfBins1to6 = 0;
    for (int i = 1; i <= 6; ++i) {
        sumOfBins1to6 += hJetPairs->GetBinContent(i);
    }

    // Rescale each bin by the new sum of bins from 1 to 6
    for (int i = 1; i <= 7; ++i) {
        double originalContent = hJetPairs->GetBinContent(i);
        double rescaledContent = originalContent / sumOfBins1to6; // Handle division by zero if needed
        hJetPairs->SetBinContent(i, rescaledContent);
    }

/// SCALING FOR CS

        // Calculate the cssum of bins from 1 to 7
    double cssumOfBins1to7 = 0;
    for (int i = 1; i <= 7; ++i) {  // Bins are indexed from 1
        cssumOfBins1to7 += cs_hJetPairs->GetBinContent(i);
    }


    // Scale each bin by the cssum of bins from 1 to 7
    for (int i = 1; i <= 7; ++i) {
        double originalContent = cs_hJetPairs->GetBinContent(i);
        double scaledContent = originalContent / cssumOfBins1to7;
        cs_hJetPairs->SetBinContent(i, scaledContent);
    }


    // Recalculate the cssum for bins 1 to 6 after initial scaling
    double cssumOfBins1to6 = 0;
    for (int i = 1; i <= 6; ++i) {
        cssumOfBins1to6 += cs_hJetPairs->GetBinContent(i);
    }

    // Rescale each bin by the new cssum of bins from 1 to 6
    for (int i = 1; i <= 7; ++i) {
        double originalContent = cs_hJetPairs->GetBinContent(i);
        double rescaledContent = originalContent / cssumOfBins1to6; // Handle division by zero if needed
        cs_hJetPairs->SetBinContent(i, rescaledContent);
    }

/// SCALING FOR UD


        // Calculate the udsum of bins from 1 to 7
    double udsumOfBins1to7 = 0;
    for (int i = 1; i <= 7; ++i) {  // Bins are indexed from 1
        udsumOfBins1to7 += ud_hJetPairs->GetBinContent(i);
    }

    // Scale each bin by the udsum of bins from 1 to 7
    for (int i = 1; i <= 7; ++i) {
        double originalContent = ud_hJetPairs->GetBinContent(i);
        double scaledContent = originalContent / udsumOfBins1to7;
        ud_hJetPairs->SetBinContent(i, scaledContent);
    }

    // Recalculate the udsum for bins 1 to 6 after initial scaling
    double udsumOfBins1to6 = 0;
    for (int i = 1; i <= 6; ++i) {
        udsumOfBins1to6 += ud_hJetPairs->GetBinContent(i);
    }

    // Rescale each bin by the new udsum of bins from 1 to 6
    for (int i = 1; i <= 7; ++i) {
        double originalContent = ud_hJetPairs->GetBinContent(i);
        double rescaledContent = originalContent / udsumOfBins1to6; // Handle division by zero if needed
        ud_hJetPairs->SetBinContent(i, rescaledContent);
    }



    // Draw the histogram


    tdrDraw(ud_hJetPairs,"HPz",kNone,kGreen-3,kSolid,-1,1001,kGreen-3);
    ud_hJetPairs->SetFillColorAlpha(kGreen-3,0.65);


    tdrDraw(hJetPairs,"HPz",kNone,kRed-7,kSolid,-1,1001,kRed-7);
    hJetPairs->SetFillColorAlpha(kRed-7,0.45);




    // Create a legend
    TLegend *leg1 = tdrLeg(0.48,0.8-0.05*2,0.7,0.82);
    leg1->AddEntry(ud_hJetPairs, "Jet pairs (UD)", "FPLE");
    leg1->AddEntry(hJetPairs, "Jet pairs", "FPLE");
    
    
    //leg->Draw();

    // Update the canvas to reflect the changes
    TLatex *tex1 = new TLatex();
    tex1->SetNDC(); tex1->SetTextSize(0.045);
    tex1->DrawLatex(0.18,0.75,"fitProb > 0.2");
    
    gPad->Update();

    // Save the canvas as a .pdf file
    c1->SaveAs("pdf/jetpairs_ud.pdf");


    TH1D *h3 = tdrHist("h3","N fraction, reco scaled",0,1.2,"Jet pair",1,8);
    TCanvas *c3 = tdrCanvas("c3",h3,8,11,kSquare);
    //gPad->SetLogy();
    //c1->SetLogx();
    h3->GetXaxis()->SetBinLabel(1, "cs");
    h3->GetXaxis()->SetBinLabel(2, "ud");
    h3->GetXaxis()->SetBinLabel(3, "cd");
    h3->GetXaxis()->SetBinLabel(4, "us");
    h3->GetXaxis()->SetBinLabel(5, "cb");
    h3->GetXaxis()->SetBinLabel(6, "ub");
    h3->GetXaxis()->SetBinLabel(7, "x*");



    // Draw the histogram

    tdrDraw(cs_hJetPairs,"HPz",kNone,kAzure+7,kSolid,-1,1001,kAzure+7);
    cs_hJetPairs->SetFillColorAlpha(kAzure+7,0.75);

    tdrDraw(hJetPairs,"HPz",kNone,kRed-7,kSolid,-1,1001,kRed-7);
    hJetPairs->SetFillColorAlpha(kRed-7,0.5);





    // Create a legend
    TLegend *leg3 = tdrLeg(0.48,0.8-0.05*2,0.7,0.82);
    leg3->AddEntry(cs_hJetPairs, "Jet pairs (CS)", "FPLE");
    leg3->AddEntry(hJetPairs, "Jet pairs", "FPLE");
    
    
    //leg->Draw();

    // Update the canvas to reflect the changes
    TLatex *tex3 = new TLatex();
    tex3->SetNDC(); tex3->SetTextSize(0.045);
    tex3->DrawLatex(0.18,0.75,"fitProb > 0.2"); 
    
    gPad->Update();

    // Save the canvas as a .pdf file
    c3->SaveAs("pdf/jetpairs_cs.pdf");






    
    TH1D *h2 = tdrHist("h2","N fraction, reco scaled",0,1.2,"Jet pair",1,8);
    TCanvas *c2 = tdrCanvas("c2",h2,8,11,kSquare);
    //gPad->SetLogy();
    //c1->SetLogx();
    h2->GetXaxis()->SetBinLabel(1, "cs");
    h2->GetXaxis()->SetBinLabel(2, "ud");
    h2->GetXaxis()->SetBinLabel(3, "cd");
    h2->GetXaxis()->SetBinLabel(4, "us");
    h2->GetXaxis()->SetBinLabel(5, "cb");
    h2->GetXaxis()->SetBinLabel(6, "ub");
    h2->GetXaxis()->SetBinLabel(7, "x*");

    // Calculate the sum2 of bins from 1 to 7
    double sum2OfBins1to7 = 0;
    for (int i = 1; i <= 7; ++i) {  // Bins are indexed from 1
        sum2OfBins1to7 += hJetPairs_scaled->GetBinContent(i);
    }

    // Scale each bin by the sum2 of bins from 1 to 7
    for (int i = 1; i <= 7; ++i) {
        double originalContent = hJetPairs_scaled->GetBinContent(i);
        double scaledContent = originalContent / sum2OfBins1to7;
        hJetPairs_scaled->SetBinContent(i, scaledContent);
    }

    // Recalculate the sum2 for bins 1 to 6 after initial scaling
    double sum2OfBins1to6 = 0;
    for (int i = 1; i <= 6; ++i) {
        sum2OfBins1to6 += hJetPairs_scaled->GetBinContent(i);
    }

    // Rescale each bin by the new sum2 of bins from 1 to 6
    for (int i = 1; i <= 7; ++i) {
        double originalContent = hJetPairs_scaled->GetBinContent(i);
        double rescaledContent = originalContent / sum2OfBins1to6; // Handle division by zero if needed
        hJetPairs_scaled->SetBinContent(i, rescaledContent);
    }



/// SCALING FOR CS

        // Calculate the cssum2 of bins from 1 to 7
    double cssum2OfBins1to7 = 0;
    for (int i = 1; i <= 7; ++i) {  // Bins are indexed from 1
        cssum2OfBins1to7 += cs_hJetPairs_scaled->GetBinContent(i);
    }

    // Scale each bin by the cssum2 of bins from 1 to 7
    for (int i = 1; i <= 7; ++i) {
        double originalContent = cs_hJetPairs_scaled->GetBinContent(i);
        double scaledContent = originalContent / cssum2OfBins1to7;
        cs_hJetPairs_scaled->SetBinContent(i, scaledContent);
    }

    // Recalculate the cssum2 for bins 1 to 6 after initial scaling
    double cssum2OfBins1to6 = 0;
    for (int i = 1; i <= 6; ++i) {
        cssum2OfBins1to6 += cs_hJetPairs_scaled->GetBinContent(i);
    }

    // Rescale each bin by the new cssum2 of bins from 1 to 6
    for (int i = 1; i <= 7; ++i) {
        double originalContent = cs_hJetPairs_scaled->GetBinContent(i);
        double rescaledContent = originalContent / cssum2OfBins1to6; // Handle division by zero if needed
        cs_hJetPairs_scaled->SetBinContent(i, rescaledContent);
    }

/// SCALING FOR UD


        // Calculate the udsum2 of bins from 1 to 7
    double udsum2OfBins1to7 = 0;
    for (int i = 1; i <= 7; ++i) {  // Bins are indexed from 1
        udsum2OfBins1to7 += ud_hJetPairs_scaled->GetBinContent(i);
    }

    // Scale each bin by the udsum2 of bins from 1 to 7
    for (int i = 1; i <= 7; ++i) {
        double originalContent = ud_hJetPairs_scaled->GetBinContent(i);
        double scaledContent = originalContent / udsum2OfBins1to7;
        ud_hJetPairs_scaled->SetBinContent(i, scaledContent);
    }

    // Recalculate the udsum2 for bins 1 to 6 after initial scaling
    double udsum2OfBins1to6 = 0;
    for (int i = 1; i <= 6; ++i) {
        udsum2OfBins1to6 += ud_hJetPairs_scaled->GetBinContent(i);
    }

    // Rescale each bin by the new udsum2 of bins from 1 to 6
    for (int i = 1; i <= 7; ++i) {
        double originalContent = ud_hJetPairs_scaled->GetBinContent(i);
        double rescaledContent = originalContent / udsum2OfBins1to6; // Handle division by zero if needed
        ud_hJetPairs_scaled->SetBinContent(i, rescaledContent);
    }



    // Draw the histogram

    tdrDraw(ud_hJetPairs_scaled,"HPz",kNone,kGreen-3,kSolid,-1,1001,kGreen-3);
    ud_hJetPairs_scaled->SetFillColorAlpha(kGreen-3,0.65);

    tdrDraw(hJetPairs_scaled,"HPz",kNone,kRed-7,kSolid,-1,1001,kRed-7);
    hJetPairs_scaled->SetFillColorAlpha(kRed-7,0.45);



    // Create a legend
    TLegend *leg2 = tdrLeg(0.48,0.8-0.05*2,0.7,0.82);
    leg2->AddEntry(ud_hJetPairs_scaled, "Scaled jet pairs (UD)", "FPLE");
    leg2->AddEntry(hJetPairs_scaled, "Scaled jet pairs", "FPLE");

    
    //leg->Draw();

    // Update the canvas to reflect the changes
    TLatex *tex2 = new TLatex();
    tex2->SetNDC(); tex2->SetTextSize(0.045);
    tex2->DrawLatex(0.18,0.75,"fitProb > 0.2"); 
    
    gPad->Update();

    // Save the canvas as a .pdf file
    c2->SaveAs("pdf/jetpairs_scaled_ud.pdf");


    TH1D *h4 = tdrHist("h4","N fraction, reco scaled",0,1.2,"Jet pair",1,8);
    TCanvas *c4 = tdrCanvas("c4",h4,8,11,kSquare);
    //gPad->SetLogy();
    //c1->SetLogx();
    h4->GetXaxis()->SetBinLabel(1, "cs");
    h4->GetXaxis()->SetBinLabel(2, "ud");
    h4->GetXaxis()->SetBinLabel(3, "cd");
    h4->GetXaxis()->SetBinLabel(4, "us");
    h4->GetXaxis()->SetBinLabel(5, "cb");
    h4->GetXaxis()->SetBinLabel(6, "ub");
    h4->GetXaxis()->SetBinLabel(7, "x*");



    // Draw the histogram

    tdrDraw(cs_hJetPairs_scaled,"HPz",kNone,kAzure+7,kSolid,-1,1001,kAzure+7);
    cs_hJetPairs_scaled->SetFillColorAlpha(kAzure+7,0.75);

    tdrDraw(hJetPairs_scaled,"HPz",kNone,kRed-7,kSolid,-1,1001,kRed-7);
    hJetPairs_scaled->SetFillColorAlpha(kRed-7,0.5);

 



    // Create a legend
    TLegend *leg4 = tdrLeg(0.48,0.8-0.05*2,0.7,0.82);
    leg4->AddEntry(cs_hJetPairs_scaled, "Scaled jet pairs (CS)", "FPLE");
    leg4->AddEntry(hJetPairs_scaled, "Scaled jet pairs", "FPLE");

    
    //leg->Draw();

    // Update the canvas to reflect the changes
    TLatex *tex4 = new TLatex();
    tex4->SetNDC(); tex4->SetTextSize(0.045);
    tex4->DrawLatex(0.18,0.75,"fitProb > 0.2"); 
    
    gPad->Update();

    // Save the canvas as a .pdf file
    c4->SaveAs("pdf/jetpairs_scaled_cs.pdf");

}