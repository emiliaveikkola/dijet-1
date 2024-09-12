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
    TFile *file = new TFile("output_stag3new2_test.root", "READ");

    TH1D *hJetPairs = (TH1D*)file->Get("hJetPairs");
    TH1D *hJetPairs_scaled = (TH1D*)file->Get("hJetPairs_scaled");


    TH1D *hAverageMasses_gen = (TH1D*)file->Get("hAverageMasses_gen");
    TH1D *hAverageMasses_reco = (TH1D*)file->Get("hAverageMasses_reco");

    TH1D *hAverageMasses_reco_scaled = (TH1D*)file->Get("hAverageMasses_reco_scaled");

    TH1D *hAverageMasses_gen_wfp = (TH1D*)file->Get("hAverageMasses_gen_wfp");
    TH1D *hAverageMasses_reco_wfp = (TH1D*)file->Get("hAverageMasses_reco_wfp");

    TH1D *hAverageMasses_reco_wfp_scaled = (TH1D*)file->Get("hAverageMasses_reco_wfp_scaled");


    TH1D *h_cs_gen = (TH1D*)file->Get("h_cs_gen");
    TH1D *h_ud_gen = (TH1D*)file->Get("h_ud_gen");
    TH1D *h_cd_gen = (TH1D*)file->Get("h_cd_gen");
    TH1D *h_us_gen = (TH1D*)file->Get("h_us_gen");
    TH1D *h_cb_gen = (TH1D*)file->Get("h_cb_gen");
    TH1D *h_ub_gen = (TH1D*)file->Get("h_ub_gen");
    TH1D *h_x_gen = (TH1D*)file->Get("h_x_gen");

    TH1D *h_cs_reco = (TH1D*)file->Get("h_cs_reco");
    TH1D *h_ud_reco = (TH1D*)file->Get("h_ud_reco");
    TH1D *h_cd_reco = (TH1D*)file->Get("h_cd_reco");
    TH1D *h_us_reco = (TH1D*)file->Get("h_us_reco");
    TH1D *h_cb_reco = (TH1D*)file->Get("h_cb_reco");
    TH1D *h_ub_reco = (TH1D*)file->Get("h_ub_reco");
    TH1D *h_x_reco = (TH1D*)file->Get("h_x_reco");

    TH1D *h_cs_reco_scaled = (TH1D*)file->Get("h_cs_reco_scaled");
    TH1D *h_ud_reco_scaled = (TH1D*)file->Get("h_ud_reco_scaled");
    TH1D *h_cd_reco_scaled = (TH1D*)file->Get("h_cd_reco_scaled");
    TH1D *h_us_reco_scaled = (TH1D*)file->Get("h_us_reco_scaled");
    TH1D *h_cb_reco_scaled = (TH1D*)file->Get("h_cb_reco_scaled");
    TH1D *h_ub_reco_scaled = (TH1D*)file->Get("h_ub_reco_scaled");
    TH1D *h_x_reco_scaled = (TH1D*)file->Get("h_x_reco_scaled");


    TH1D *h_cs_gen_wfp = (TH1D*)file->Get("h_cs_gen_wfp");
    TH1D *h_ud_gen_wfp = (TH1D*)file->Get("h_ud_gen_wfp");
    TH1D *h_cd_gen_wfp = (TH1D*)file->Get("h_cd_gen_wfp");
    TH1D *h_us_gen_wfp = (TH1D*)file->Get("h_us_gen_wfp");
    TH1D *h_cb_gen_wfp = (TH1D*)file->Get("h_cb_gen_wfp");
    TH1D *h_ub_gen_wfp = (TH1D*)file->Get("h_ub_gen_wfp");
    TH1D *h_x_gen_wfp = (TH1D*)file->Get("h_x_gen_wfp");

    TH1D *h_cs_reco_wfp = (TH1D*)file->Get("h_cs_reco_wfp");
    TH1D *h_ud_reco_wfp = (TH1D*)file->Get("h_ud_reco_wfp");
    TH1D *h_cd_reco_wfp = (TH1D*)file->Get("h_cd_reco_wfp");
    TH1D *h_us_reco_wfp = (TH1D*)file->Get("h_us_reco_wfp");
    TH1D *h_cb_reco_wfp = (TH1D*)file->Get("h_cb_reco_wfp");
    TH1D *h_ub_reco_wfp = (TH1D*)file->Get("h_ub_reco_wfp");
    TH1D *h_x_reco_wfp = (TH1D*)file->Get("h_x_reco_wfp");



    
    lumi_136TeV = "Run3 simulation";
    extraText = "Private";
    TH1D *h1 = tdrHist("h1","N_{reco} fraction",0,1,"Jet pair",1,8);
    TCanvas *c1 = tdrCanvas("c1",h1,4,11,kSquare);
    //gPad->SetLogy();
    //c1->SetLogx();
    h1->GetXaxis()->SetBinLabel(1, "cs");
    h1->GetXaxis()->SetBinLabel(2, "ud");
    h1->GetXaxis()->SetBinLabel(3, "cd");
    h1->GetXaxis()->SetBinLabel(4, "us");
    h1->GetXaxis()->SetBinLabel(5, "cb");
    h1->GetXaxis()->SetBinLabel(6, "ub");
    h1->GetXaxis()->SetBinLabel(7, "x");

    h1->GetXaxis()->SetLabelSize(0.05);
    h1->GetYaxis()->SetLabelSize(0.04);
    h1->GetXaxis()->SetTitleSize(0.045);
    h1->GetXaxis()->SetTitleOffset(1.2);
    h1->GetYaxis()->SetTitleOffset(1.4);
    h1->GetYaxis()->SetTitleSize(0.045);

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
    tdrDraw(hJetPairs,"HPz",kNone,kGreen-6,kSolid,-1,1001,kGreen-6);
    hJetPairs->SetFillColorAlpha(kGreen-7,0.45);



    // Create a legend
    TLegend *leg = tdrLeg(0.5,0.8-0.05*1,0.7,0.82);
    leg->AddEntry(hJetPairs, "Jet pairs", "FPLE");
    leg->SetTextSize(0.035);
    
    //leg->Draw();

    // Update the canvas to reflect the changes
    TLatex *tex1 = new TLatex();
    tex1->SetNDC(); tex1->SetTextSize(0.035); 
    
    gPad->Update();

    // Save the canvas as a .pdf file
    c1->SaveAs("pdf/jetpairs2.pdf");


    TH1D *h12 = tdrHist("h12","N_{reco} fraction",0,1,"Jet pair",1,8);
    TCanvas *c12 = tdrCanvas("c12",h12,4,11,kSquare);
    //gPad->SetLogy();
    //c1->SetLogx();
    h12->GetXaxis()->SetBinLabel(1, "cs");
    h12->GetXaxis()->SetBinLabel(2, "ud");
    h12->GetXaxis()->SetBinLabel(3, "cd");
    h12->GetXaxis()->SetBinLabel(4, "us");
    h12->GetXaxis()->SetBinLabel(5, "cb");
    h12->GetXaxis()->SetBinLabel(6, "ub");
    h12->GetXaxis()->SetBinLabel(7, "x");

    h12->GetXaxis()->SetLabelSize(0.05);
    h12->GetYaxis()->SetLabelSize(0.04);
    h12->GetXaxis()->SetTitleSize(0.045);
    h12->GetXaxis()->SetTitleOffset(1.2);
    h12->GetYaxis()->SetTitleOffset(1.4);
    h12->GetYaxis()->SetTitleSize(0.045);

    // Calculate the sum of bins from 1 to 7
    double sumOfBins1to7 = 0;
    for (int i = 1; i <= 7; ++i) {  // Bins are indexed from 1
        sumOfBins1to7 += hJetPairs_scaled->GetBinContent(i);
    }

    // Scale each bin by the sum of bins from 1 to 7
    for (int i = 1; i <= 7; ++i) {
        double originalContent = hJetPairs_scaled->GetBinContent(i);
        double scaledContent = originalContent / sumOfBins1to7;
        hJetPairs_scaled->SetBinContent(i, scaledContent);
    }

    // Recalculate the sum for bins 1 to 6 after initial scaling
    double sumOfBins1to6 = 0;
    for (int i = 1; i <= 6; ++i) {
        sumOfBins1to6 += hJetPairs_scaled->GetBinContent(i);
    }

    // Rescale each bin by the new sum of bins from 1 to 6
    for (int i = 1; i <= 7; ++i) {
        double originalContent = hJetPairs_scaled->GetBinContent(i);
        double rescaledContent = originalContent / sumOfBins1to6; // Handle division by zero if needed
        hJetPairs_scaled->SetBinContent(i, rescaledContent);
    }

    // Draw the histogram

    tdrDraw(hJetPairs_scaled,"HPz",kNone,kAzure+2,kSolid,-1,1001,kAzure+2);
    hJetPairs_scaled->SetFillColorAlpha(kAzure+7,0.65);
    tdrDraw(hJetPairs,"HPz",kNone,kRed-7,kSolid,-1,1001,kRed-7);
    hJetPairs->SetFillColorAlpha(kRed-7,0.45);



    // Create a legend
    TLegend *leg12 = tdrLeg(0.5,0.8-0.05*2,0.7,0.82);
    leg12->AddEntry(hJetPairs_scaled, "Scaled jet pairs", "FPLE");
    leg12->AddEntry(hJetPairs, "Jet pairs", "FPLE");
    leg12->SetTextSize(0.035);
    
    //leg->Draw();

    // Update the canvas to reflect the changes
    TLatex *tex12 = new TLatex();
    tex12->SetNDC(); tex12->SetTextSize(0.035); 
    
    gPad->Update();

    // Save the canvas as a .pdf file
    c12->SaveAs("pdf/jetpairs_scaled2.pdf");



    TH1D *h2 = tdrHist("h2","Average mass (GeV)",78-1e-1,87-1e-2,"Jet pair, gen",1,8);
    TCanvas *c2 = tdrCanvas("c2",h2,4,11,kSquare);
    //gPad->SetLogy();
    //c1->SetLogx();
    h2->GetXaxis()->SetBinLabel(1, "cs");
    h2->GetXaxis()->SetBinLabel(2, "ud");
    h2->GetXaxis()->SetBinLabel(3, "cd");
    h2->GetXaxis()->SetBinLabel(4, "us");
    h2->GetXaxis()->SetBinLabel(5, "cb");
    h2->GetXaxis()->SetBinLabel(6, "ub");
    h2->GetXaxis()->SetBinLabel(7, "x");

    h2->GetXaxis()->SetLabelSize(0.05);
    h2->GetYaxis()->SetLabelSize(0.04);
    h2->GetXaxis()->SetTitleSize(0.045);
    h2->GetXaxis()->SetTitleOffset(1.2);
    h2->GetYaxis()->SetTitleOffset(1.4);
    h2->GetYaxis()->SetTitleSize(0.045);

    // Draw the histogram
    tdrDraw(hAverageMasses_gen,"Histe",kNone,kAzure+2,kSolid,-1,1001,kAzure+2);
    hAverageMasses_gen->SetFillColorAlpha(kAzure+7,0.45);


    // Create a legend
    TLegend *leg2 = tdrLeg(0.2,0.71-0.05*1,0.35,0.73);
    //leg2->AddEntry(hAverageMasses, "Average mass", "FPLE");
    //leg2->SetTextSize(0.035);
    
    //leg->Draw();

    // Update the canvas to reflect the changes
    TLatex *tex2 = new TLatex();
    tex2->SetNDC(); tex2->SetTextSize(0.03); 
    tex2->DrawLatex(0.31,0.85,"fitProb > 0.2");
    tex2->DrawLatex(0.31,0.81,"genmass > 30 GeV");
    tex2->DrawLatex(0.2,0.74,Form("cs  %1.3f #pm %1.3f",h_cs_gen->GetMean(),h_cs_gen->GetMeanError()));
    tex2->DrawLatex(0.2,0.7,Form("ud  %1.3f #pm %1.3f",h_ud_gen->GetMean(),h_ud_gen->GetMeanError()));
    tex2->DrawLatex(0.2,0.66,Form("cd  %1.3f #pm %1.3f",h_cd_gen->GetMean(),h_cd_gen->GetMeanError()));
    tex2->DrawLatex(0.2,0.62,Form("us  %1.3f #pm %1.3f",h_us_gen->GetMean(),h_us_gen->GetMeanError()));
    tex2->DrawLatex(0.2,0.58,Form("cb  %1.3f #pm %1.3f",h_cb_gen->GetMean(),h_cb_gen->GetMeanError()));
    tex2->DrawLatex(0.2,0.54,Form("ub  %1.3f #pm %1.3f",h_ub_gen->GetMean(),h_ub_gen->GetMeanError()));
    tex2->DrawLatex(0.2,0.5,Form(" x   %1.3f #pm %1.3f",h_x_gen->GetMean(),h_x_gen->GetMeanError()));
    gPad->Update();

    // Save the canvas as a .pdf file
    c2->SaveAs("pdf/jetpairsavmass_gen2.pdf");

    TH1D *h3 = tdrHist("h3","N_{gen} fraction",0,0.1,"Mass (GeV)",30,140);
    TCanvas *c3 = tdrCanvas("c3",h3,4,11,kSquare);
    //gPad->SetLogy();

    h3->GetXaxis()->SetLabelSize(0.05);
    h3->GetYaxis()->SetLabelSize(0.04);
    h3->GetXaxis()->SetTitleSize(0.045);
    h3->GetXaxis()->SetTitleOffset(1.2);
    h3->GetYaxis()->SetTitleOffset(1.4);
    h3->GetYaxis()->SetTitleSize(0.045);

    h_cs_gen->Scale(1./h_cs_gen->Integral());
    h_ud_gen->Scale(1./h_ud_gen->Integral());
    h_cd_gen->Scale(1./h_cd_gen->Integral());
    h_us_gen->Scale(1./h_us_gen->Integral());
    h_cb_gen->Scale(1./h_cb_gen->Integral());
    h_ub_gen->Scale(1./h_ub_gen->Integral());
    h_x_gen->Scale(1./h_x_gen->Integral());

    // Draw the histogram


    tdrDraw(h_x_gen,"Pz",kFullDiamond,kViolet+1);
    h_x_gen->SetMarkerSize(0.8);

    tdrDraw(h_ub_gen,"Pz",kFullDiamond,kRed-4);
    h_ub_gen->SetMarkerSize(0.8);

    tdrDraw(h_cb_gen,"Pz",kFullDiamond,kSpring-5);
    h_cb_gen->SetMarkerSize(0.8);

    tdrDraw(h_us_gen,"Pz",kFullDiamond,kOrange-2);
    h_us_gen->SetMarkerSize(0.8);

    tdrDraw(h_cd_gen,"Pz",kFullDiamond,kGreen+3);
    h_cd_gen->SetMarkerSize(0.8);

    tdrDraw(h_ud_gen,"Pz",kFullDiamond,kAzure+1);
    h_ud_gen->SetMarkerSize(0.8);

    tdrDraw(h_cs_gen,"Pz",kFullDiamond,kOrange+7);
    h_cs_gen->SetMarkerSize(0.8);





    // Create a legend
    TLegend *leg3 = tdrLeg(0.75,0.75-0.05*7,0.9,0.8);
    leg3->AddEntry(h_cs_gen, "CS", "PLE");
    leg3->AddEntry(h_ud_gen, "UD", "PLE");
    leg3->AddEntry(h_cd_gen, "CD", "PLE");
    leg3->AddEntry(h_us_gen, "US", "PLE");
    leg3->AddEntry(h_cb_gen, "CB", "PLE");
    leg3->AddEntry(h_ub_gen, "UB", "PLE");
    leg3->AddEntry(h_x_gen, "X", "PLE");
    leg3->SetTextSize(0.035);

    
    //leg->Draw();

    // Update the canvas to reflect the changes
    TLatex *tex3 = new TLatex();
    tex3->SetNDC(); tex3->SetTextSize(0.035); 
    tex3->DrawLatex(0.18,0.75,"fitProb > 0.2");
    tex3->DrawLatex(0.18,0.71,"genmass > 30 GeV");
    gPad->Update();

    // Save the canvas as a .pdf file
    c3->SaveAs("pdf/jetpairsmass_gen2.pdf");






///////RECOJETS////////







    TH1D *h4 = tdrHist("h4","Average mass (GeV)",82+2e-1,86,"Jet pair, reco",1,8);
    TCanvas *c4 = tdrCanvas("c4",h4,4,11,kSquare);
    //gPad->SetLogy();
    //c1->SetLogx();
    h4->GetXaxis()->SetBinLabel(1, "cs");
    h4->GetXaxis()->SetBinLabel(2, "ud");
    h4->GetXaxis()->SetBinLabel(3, "cd");
    h4->GetXaxis()->SetBinLabel(4, "us");
    h4->GetXaxis()->SetBinLabel(5, "cb");
    h4->GetXaxis()->SetBinLabel(6, "ub");
    h4->GetXaxis()->SetBinLabel(7, "x");

    h4->GetXaxis()->SetLabelSize(0.05);
    h4->GetYaxis()->SetLabelSize(0.04);
    h4->GetXaxis()->SetTitleSize(0.045);
    h4->GetXaxis()->SetTitleOffset(1.2);
    h4->GetYaxis()->SetTitleOffset(1.4);
    h4->GetYaxis()->SetTitleSize(0.045);

    // Draw the histogram
    tdrDraw(hAverageMasses_reco,"HPz",kNone,kAzure+2,kSolid,-1,1001,kAzure+2);
    hAverageMasses_reco->SetFillColorAlpha(kAzure+7,0.45);
    



    // Create a legend
    TLegend *leg4 = tdrLeg(0.2,0.71-0.05*1,0.35,0.73);
    //leg4->AddEntry(hAverageMasses, "Average mass", "FPLE");
    //leg4->SetTextSize(0.035);
    
    //leg->Draw();

    // Update the canvas to reflect the changes
    TLatex *tex4 = new TLatex();
    tex4->SetNDC(); tex4->SetTextSize(0.03); 
    tex4->DrawLatex(0.31,0.85,"fitProb > 0.2");
    tex4->DrawLatex(0.31,0.81,"recomass > 30 GeV");
    tex4->DrawLatex(0.2,0.74,Form("cs  %1.3f #pm %1.3f",h_cs_reco->GetMean(),h_cs_reco->GetMeanError()));
    tex4->DrawLatex(0.2,0.7,Form("ud  %1.3f #pm %1.3f",h_ud_reco->GetMean(),h_ud_reco->GetMeanError()));
    tex4->DrawLatex(0.2,0.66,Form("cd  %1.3f #pm %1.3f",h_cd_reco->GetMean(),h_cd_reco->GetMeanError()));
    tex4->DrawLatex(0.2,0.62,Form("us  %1.3f #pm %1.3f",h_us_reco->GetMean(),h_us_reco->GetMeanError()));
    tex4->DrawLatex(0.2,0.58,Form("cb  %1.3f #pm %1.3f",h_cb_reco->GetMean(),h_cb_reco->GetMeanError()));
    tex4->DrawLatex(0.2,0.54,Form("ub  %1.3f #pm %1.3f",h_ub_reco->GetMean(),h_ub_reco->GetMeanError()));
    tex4->DrawLatex(0.2,0.5,Form(" x   %1.3f #pm %1.3f",h_x_reco->GetMean(),h_x_reco->GetMeanError()));
    gPad->Update();

    // Save the canvas as a .pdf file
    c4->SaveAs("pdf/jetpairsavmass_reco2.pdf");

    
    TH1D *h5 = tdrHist("h5","N_{reco} fraction",0,0.06-1e-3,"Mass (GeV)",30,140);
    TCanvas *c5 = tdrCanvas("c5",h5,4,11,kSquare);
    //gPad->SetLogy();

    h5->GetXaxis()->SetLabelSize(0.04);
    h5->GetYaxis()->SetLabelSize(0.04);
    h5->GetXaxis()->SetTitleSize(0.045);
    h5->GetXaxis()->SetTitleOffset(1.2);
    h5->GetYaxis()->SetTitleOffset(1.4);
    h5->GetYaxis()->SetTitleSize(0.045);

    h_cs_reco->Scale(1./h_cs_reco->Integral());
    h_ud_reco->Scale(1./h_ud_reco->Integral());
    h_cd_reco->Scale(1./h_cd_reco->Integral());
    h_us_reco->Scale(1./h_us_reco->Integral());
    h_cb_reco->Scale(1./h_cb_reco->Integral());
    h_ub_reco->Scale(1./h_ub_reco->Integral());
    h_x_reco->Scale(1./h_x_reco->Integral());

    // Draw the histogram


    tdrDraw(h_x_reco,"Pz",kFullDiamond,kViolet+1);
    h_x_reco->SetMarkerSize(0.8);

    tdrDraw(h_ub_reco,"Pz",kFullDiamond,kRed-4);
    h_ub_reco->SetMarkerSize(0.8);

    tdrDraw(h_cb_reco,"Pz",kFullDiamond,kSpring-5);
    h_cb_reco->SetMarkerSize(0.8);

    tdrDraw(h_us_reco,"Pz",kFullDiamond,kOrange-2);
    h_us_reco->SetMarkerSize(0.8);

    tdrDraw(h_cd_reco,"Pz",kFullDiamond,kGreen+3);
    h_cd_reco->SetMarkerSize(0.8);

    tdrDraw(h_ud_reco,"Pz",kFullDiamond,kAzure+1);
    h_ud_reco->SetMarkerSize(0.8);

    tdrDraw(h_cs_reco,"Pz",kFullDiamond,kOrange+7);
    h_cs_reco->SetMarkerSize(0.8);


    // Create a legend
    TLegend *leg5 = tdrLeg(0.75,0.75-0.05*7,0.9,0.8);
    leg5->AddEntry(h_cs_reco, "CS", "PLE");
    leg5->AddEntry(h_ud_reco, "UD", "PLE");
    leg5->AddEntry(h_cd_reco, "CD", "PLE");
    leg5->AddEntry(h_us_reco, "US", "PLE");
    leg5->AddEntry(h_cb_reco, "CB", "PLE");
    leg5->AddEntry(h_ub_reco, "UB", "PLE");
    leg5->AddEntry(h_x_reco, "X", "PLE");
    leg5->SetTextSize(0.035);

    
    //leg->Draw();

    // Update the canvas to reflect the changes
    TLatex *tex5 = new TLatex();
    tex5->SetNDC(); tex5->SetTextSize(0.035); 
    tex5->DrawLatex(0.18,0.75,"fitProb > 0.2");
    tex5->DrawLatex(0.18,0.71,"recomass > 30 GeV");
    gPad->Update();

    // Save the canvas as a .pdf file
    c5->SaveAs("pdf/jetpairsmass_reco2.pdf");






////// SCALED RECOJETS ////////////


    TH1D *h10 = tdrHist("h10","Average mass (GeV)",78-1e-1,87-1e-2,"Jet pair",1,8);
    TCanvas *c10 = tdrCanvas("c10",h10,4,11,kSquare);
    //gPad->SetLogy();
    //c1->SetLogx();
    h10->GetXaxis()->SetBinLabel(1, "cs");
    h10->GetXaxis()->SetBinLabel(2, "ud");
    h10->GetXaxis()->SetBinLabel(3, "cd");
    h10->GetXaxis()->SetBinLabel(4, "us");
    h10->GetXaxis()->SetBinLabel(5, "cb");
    h10->GetXaxis()->SetBinLabel(6, "ub");
    h10->GetXaxis()->SetBinLabel(7, "x");

    h10->GetXaxis()->SetLabelSize(0.05);
    h10->GetYaxis()->SetLabelSize(0.04);
    h10->GetXaxis()->SetTitleSize(0.045);
    h10->GetXaxis()->SetTitleOffset(1.2);
    h10->GetYaxis()->SetTitleOffset(1.4);
    h10->GetYaxis()->SetTitleSize(0.045);

    // Draw the histogram
    tdrDraw(hAverageMasses_gen,"HPz",kNone,kRed-7,kSolid,-1,1001,kRed-7);
    hAverageMasses_gen->SetFillColorAlpha(kRed-7,0.75);
    tdrDraw(hAverageMasses_reco,"HPz",kNone,kGreen-6,kSolid,-1,1001,kGreen-6);
    hAverageMasses_reco->SetFillColorAlpha(kGreen-6,0.45);
    tdrDraw(hAverageMasses_reco_scaled,"HPz",kNone,kAzure+2,kSolid,-1,1001,kAzure+2);
    hAverageMasses_reco_scaled->SetFillColorAlpha(kAzure+7,0.35);




    // Create a legend
    TLegend *leg10 = tdrLeg(0.5,0.4-0.05*3,0.75,0.4);
    leg10->AddEntry(hAverageMasses_gen, "Jet pairs (gen)", "FPLE");
    leg10->AddEntry(hAverageMasses_reco, "Jet pairs (reco)", "FPLE");
    leg10->AddEntry(hAverageMasses_reco_scaled, "Scaled jet pairs (reco)", "FPLE");

    leg10->SetTextSize(0.035);
    
    //leg->Draw();

    // Update the canvas to reflect the changes
    TLatex *tex10 = new TLatex();
    tex10->SetNDC(); tex10->SetTextSize(0.03); 
    tex10->DrawLatex(0.31,0.85,"fitProb > 0.2");
    tex10->DrawLatex(0.31,0.81,"jet pair mass > 30 GeV");
    tex10->DrawLatex(0.2,0.5,Form("cs  %1.3f #pm %1.3f",h_cs_reco_scaled->GetMean(),h_cs_reco_scaled->GetMeanError()));
    tex10->DrawLatex(0.2,0.46,Form("ud  %1.3f #pm %1.3f",h_ud_reco_scaled->GetMean(),h_ud_reco_scaled->GetMeanError()));
    tex10->DrawLatex(0.2,0.42,Form("cd  %1.3f #pm %1.3f",h_cd_reco_scaled->GetMean(),h_cd_reco_scaled->GetMeanError()));
    tex10->DrawLatex(0.2,0.38,Form("us  %1.3f #pm %1.3f",h_us_reco_scaled->GetMean(),h_us_reco_scaled->GetMeanError()));
    tex10->DrawLatex(0.2,0.34,Form("cb  %1.3f #pm %1.3f",h_cb_reco_scaled->GetMean(),h_cb_reco_scaled->GetMeanError()));
    tex10->DrawLatex(0.2,0.3,Form("ub  %1.3f #pm %1.3f",h_ub_reco_scaled->GetMean(),h_ub_reco_scaled->GetMeanError()));
    tex10->DrawLatex(0.2,0.26,Form(" x   %1.3f #pm %1.3f",h_x_reco_scaled->GetMean(),h_x_reco_scaled->GetMeanError()));
    gPad->Update();

    // Save the canvas as a .pdf file
    c10->SaveAs("pdf/jetpairsavmass_reco_scaled2.pdf");

    
    TH1D *h11 = tdrHist("h11","N_{scal.} fraction",0,0.1-1e-3,"Jet pair mass (GeV)",30,140);
    TCanvas *c11 = tdrCanvas("c11",h11,4,11,kSquare);

    h11->GetXaxis()->SetLabelSize(0.04);
    h11->GetYaxis()->SetLabelSize(0.04);
    h11->GetXaxis()->SetTitleSize(0.045);
    h11->GetXaxis()->SetTitleOffset(1.2);
    h11->GetYaxis()->SetTitleOffset(1.4);
    h11->GetYaxis()->SetTitleSize(0.045);
    //gPad->SetLogy();

    h_cs_reco_scaled->Scale(1./h_cs_reco_scaled->Integral());
    h_ud_reco_scaled->Scale(1./h_ud_reco_scaled->Integral());
    h_cd_reco_scaled->Scale(1./h_cd_reco_scaled->Integral());
    h_us_reco_scaled->Scale(1./h_us_reco_scaled->Integral());
    h_cb_reco_scaled->Scale(1./h_cb_reco_scaled->Integral());
    h_ub_reco_scaled->Scale(1./h_ub_reco_scaled->Integral());
    h_x_reco_scaled->Scale(1./h_x_reco_scaled->Integral());

    // Draw the histogram

    tdrDraw(h_ud_gen,"HPz",kNone,kPink-8,kSolid,-1,1001,kPink-8);
    h_ud_gen->SetFillColorAlpha(kPink-8,0.1);

    tdrDraw(h_cs_gen,"HPz",kNone,kAzure+2,kSolid,-1,1001,kAzure+2);
    h_cs_gen->SetFillColorAlpha(kAzure+2,0.1);

    tdrDraw(h_x_gen,"HPz",kNone,kGreen-2,kSolid,-1,1001,kGreen-2);
    h_x_gen->SetFillColorAlpha(kGreen-2,0.1);


    tdrDraw(h_x_reco,"Pz",kFullDiamond,kGreen-3);
    h_x_reco->SetMarkerSize(0.8);

    tdrDraw(h_ub_reco,"Pz",kFullDiamond,kGreen-3);
    h_ub_reco->SetMarkerSize(0.8);

    tdrDraw(h_cb_reco,"Pz",kFullDiamond,kGreen-3);
    h_cb_reco->SetMarkerSize(0.8);

    tdrDraw(h_us_reco,"Pz",kFullDiamond,kPink-9);
    h_us_reco->SetMarkerSize(0.8);

    tdrDraw(h_cd_reco,"Pz",kFullDiamond,kAzure+7);
    h_cd_reco->SetMarkerSize(0.8);

    tdrDraw(h_ud_reco,"Pz",kFullDiamond,kPink-9);
    h_ud_reco->SetMarkerSize(0.8);

    tdrDraw(h_cs_reco,"Pz",kFullDiamond,kAzure+7);
    h_cs_reco->SetMarkerSize(0.8);


    // Create a legend
    TLegend *leg11 = tdrLeg(0.6,0.85-0.05*6,0.8,0.85);
    leg11->AddEntry(h_ud_gen, "ud + us (gen)", "FPLE");
    leg11->AddEntry(h_cs_gen, "cs + cd (gen)", "FPLE");
    leg11->AddEntry(h_x_gen, "x + cb + ub (gen)", "FPLE");
    leg11->AddEntry(h_ud_reco, "ud + us (reco)", "PLE");
    leg11->AddEntry(h_cs_reco, "cs + cd (reco)", "PLE");
    //leg11->AddEntry(h_ub_reco_scaled, "UB", "PLE");
    leg11->AddEntry(h_x_reco, "x + cb + ub (reco)", "PLE");
    leg11->SetTextSize(0.035);

    
    //leg->Draw();

    // Update the canvas to reflect the changes
    TLatex *tex11 = new TLatex();
    tex11->SetNDC(); tex11->SetTextSize(0.035); 
    tex11->DrawLatex(0.18,0.75,"fitProb > 0.2");
    //tex11->DrawLatex(0.18,0.71,"jet pair mass > 30 GeV");
    gPad->Update();

    // Save the canvas as a .pdf file
    c11->SaveAs("pdf/jetpairsmass_reco_scaled2.pdf");



///////////Without fitProb //////////
/*




    TH1D *h6 = tdrHist("h6","Average mass (GeV)",77-1e-1,105-1e-2,"Jet pair, gen wfp",1,8);
    TCanvas *c6 = tdrCanvas("c6",h6,8,11,kSquare);
    //gPad->SetLogy();
    //c1->SetLogx();
    h6->GetXaxis()->SetBinLabel(1, "cs");
    h6->GetXaxis()->SetBinLabel(2, "ud");
    h6->GetXaxis()->SetBinLabel(3, "cd");
    h6->GetXaxis()->SetBinLabel(4, "us");
    h6->GetXaxis()->SetBinLabel(5, "cb");
    h6->GetXaxis()->SetBinLabel(6, "ub");
    h6->GetXaxis()->SetBinLabel(7, "x");

    // Draw the histogram
    tdrDraw(hAverageMasses_gen_wfp,"Histe",kNone,kAzure+2,kSolid,-1,1001,kAzure+2);
    hAverageMasses_gen_wfp->SetFillColorAlpha(kAzure+7,0.45);


    // Create a legend
    TLegend *leg6 = tdrLeg(0.2,0.71-0.05*1,0.35,0.73);
    //leg2->AddEntry(hAverageMasses, "Average mass", "FPLE");
    //leg2->SetTextSize(0.035);
    
    //leg->Draw();

    // Update the canvas to reflect the changes
    TLatex *tex6 = new TLatex();
    tex6->SetNDC(); tex6->SetTextSize(0.035); 
    tex6->DrawLatex(0.31,0.85,"without fitProb");
    tex6->DrawLatex(0.31,0.81,"genmass > 30 GeV");
    tex6->DrawLatex(0.2,0.74,Form("cs  %1.3f #pm %1.3f",h_cs_gen_wfp->GetMean(),h_cs_gen_wfp->GetMeanError()));
    tex6->DrawLatex(0.2,0.7,Form("ud  %1.3f #pm %1.3f",h_ud_gen_wfp->GetMean(),h_ud_gen_wfp->GetMeanError()));
    tex6->DrawLatex(0.2,0.66,Form("cd  %1.3f #pm %1.3f",h_cd_gen_wfp->GetMean(),h_cd_gen_wfp->GetMeanError()));
    tex6->DrawLatex(0.2,0.62,Form("us  %1.3f #pm %1.3f",h_us_gen_wfp->GetMean(),h_us_gen_wfp->GetMeanError()));
    tex6->DrawLatex(0.2,0.58,Form("cb  %1.3f #pm %1.3f",h_cb_gen_wfp->GetMean(),h_cb_gen_wfp->GetMeanError()));
    tex6->DrawLatex(0.2,0.54,Form("ub  %1.3f #pm %1.3f",h_ub_gen_wfp->GetMean(),h_ub_gen_wfp->GetMeanError()));
    tex6->DrawLatex(0.2,0.5,Form(" x   %1.3f #pm %1.3f",h_x_gen_wfp->GetMean(),h_x_gen_wfp->GetMeanError()));
    gPad->Update();

    // Save the canvas as a .pdf file
    c6->SaveAs("pdf/jetpairsavmass_gen_without_fitprob2.pdf");

    TH1D *h7 = tdrHist("h7","Normalised N, gen",0,0.1,"Mass (GeV)",30,140);
    TCanvas *c7 = tdrCanvas("c7",h7,8,11,kSquare);
    //gPad->SetLogy();

    h_cs_gen_wfp->Scale(1./h_cs_gen_wfp->Integral());
    h_ud_gen_wfp->Scale(1./h_ud_gen_wfp->Integral());
    h_cd_gen_wfp->Scale(1./h_cd_gen_wfp->Integral());
    h_us_gen_wfp->Scale(1./h_us_gen_wfp->Integral());
    h_cb_gen_wfp->Scale(1./h_cb_gen_wfp->Integral());
    h_ub_gen_wfp->Scale(1./h_ub_gen_wfp->Integral());
    h_x_gen_wfp->Scale(1./h_x_gen_wfp->Integral());

    // Draw the histogram


    tdrDraw(h_x_gen_wfp,"Pz",kFullDiamond,kViolet+1);
    h_x_gen_wfp->SetMarkerSize(0.8);

    tdrDraw(h_ub_gen_wfp,"Pz",kFullDiamond,kRed-4);
    h_ub_gen_wfp->SetMarkerSize(0.8);

    tdrDraw(h_cb_gen_wfp,"Pz",kFullDiamond,kSpring-5);
    h_cb_gen_wfp->SetMarkerSize(0.8);

    tdrDraw(h_us_gen_wfp,"Pz",kFullDiamond,kOrange-2);
    h_us_gen_wfp->SetMarkerSize(0.8);

    tdrDraw(h_cd_gen_wfp,"Pz",kFullDiamond,kGreen+3);
    h_cd_gen_wfp->SetMarkerSize(0.8);

    tdrDraw(h_ud_gen_wfp,"Pz",kFullDiamond,kAzure+1);
    h_ud_gen_wfp->SetMarkerSize(0.8);

    tdrDraw(h_cs_gen_wfp,"Pz",kFullDiamond,kOrange+7);
    h_cs_gen_wfp->SetMarkerSize(0.8);


    // Create a legend
    TLegend *leg7 = tdrLeg(0.75,0.7-0.05*7,0.9,0.8);
    leg7->AddEntry(h_cs_gen_wfp, "CS", "PLE");
    leg7->AddEntry(h_ud_gen_wfp, "UD", "PLE");
    leg7->AddEntry(h_cd_gen_wfp, "CD", "PLE");
    leg7->AddEntry(h_us_gen_wfp, "US", "PLE");
    leg7->AddEntry(h_cb_gen_wfp, "CB", "PLE");
    leg7->AddEntry(h_ub_gen_wfp, "UB", "PLE");
    leg7->AddEntry(h_x_gen_wfp, "X", "PLE");
    leg7->SetTextSize(0.035);

    
    //leg->Draw();

    // Update the canvas to reflect the changes
    TLatex *tex7 = new TLatex();
    tex7->SetNDC(); tex7->SetTextSize(0.035); 
    tex7->DrawLatex(0.18,0.75,"without fitProb");
    tex7->DrawLatex(0.18,0.71,"genmass > 30 GeV");
    gPad->Update();

    // Save the canvas as a .pdf file
    c7->SaveAs("pdf/jetpairsmass_gen_without_fitprob2.pdf");




    TH1D *h8 = tdrHist("h8","Average mass (GeV)",80+2e-1,105,"Jet pair, reco wfp",1,8);
    TCanvas *c8 = tdrCanvas("c8",h8,8,11,kSquare);
    //gPad->SetLogy();
    //c1->SetLogx();
    h8->GetXaxis()->SetBinLabel(1, "cs");
    h8->GetXaxis()->SetBinLabel(2, "ud");
    h8->GetXaxis()->SetBinLabel(3, "cd");
    h8->GetXaxis()->SetBinLabel(4, "us");
    h8->GetXaxis()->SetBinLabel(5, "cb");
    h8->GetXaxis()->SetBinLabel(6, "ub");
    h8->GetXaxis()->SetBinLabel(7, "x");

    // Draw the histogram
    tdrDraw(hAverageMasses_reco_wfp,"HPz",kNone,kAzure+2,kSolid,-1,1001,kAzure+2);
    hAverageMasses_reco_wfp->SetFillColorAlpha(kAzure+7,0.45);



    // Create a legend
    TLegend *leg8 = tdrLeg(0.2,0.71-0.05*1,0.35,0.73);
    //leg4->AddEntry(hAverageMasses, "Average mass", "FPLE");
    //leg4->SetTextSize(0.035);
    
    //leg->Draw();

    // Update the canvas to reflect the changes
    TLatex *tex8 = new TLatex();
    tex8->SetNDC(); tex8->SetTextSize(0.035); 
    tex8->DrawLatex(0.31,0.85,"without fitProb");
    tex8->DrawLatex(0.31,0.81,"recomass > 30 GeV");
    tex8->DrawLatex(0.2,0.74,Form("cs  %1.3f #pm %1.3f",h_cs_reco_wfp->GetMean(),h_cs_reco_wfp->GetMeanError()));
    tex8->DrawLatex(0.2,0.7,Form("ud  %1.3f #pm %1.3f",h_ud_reco_wfp->GetMean(),h_ud_reco_wfp->GetMeanError()));
    tex8->DrawLatex(0.2,0.66,Form("cd  %1.3f #pm %1.3f",h_cd_reco_wfp->GetMean(),h_cd_reco_wfp->GetMeanError()));
    tex8->DrawLatex(0.2,0.62,Form("us  %1.3f #pm %1.3f",h_us_reco_wfp->GetMean(),h_us_reco_wfp->GetMeanError()));
    tex8->DrawLatex(0.2,0.58,Form("cb  %1.3f #pm %1.3f",h_cb_reco_wfp->GetMean(),h_cb_reco_wfp->GetMeanError()));
    tex8->DrawLatex(0.2,0.54,Form("ub  %1.3f #pm %1.3f",h_ub_reco_wfp->GetMean(),h_ub_reco_wfp->GetMeanError()));
    tex8->DrawLatex(0.2,0.5,Form(" x   %1.3f #pm %1.3f",h_x_reco_wfp->GetMean(),h_x_reco_wfp->GetMeanError()));
    gPad->Update();

    // Save the canvas as a .pdf file
    c8->SaveAs("pdf/jetpairsavmass_reco_without_fitprob2.pdf");

    
    TH1D *h9 = tdrHist("h9","Normalised N, reco",0,0.06-1e-3,"Mass (GeV)",30,140);
    TCanvas *c9 = tdrCanvas("c9",h9,8,11,kSquare);
    //gPad->SetLogy();
    h_cs_reco_wfp->Scale(1./h_cs_reco_wfp->Integral());
    h_ud_reco_wfp->Scale(1./h_ud_reco_wfp->Integral());
    h_cd_reco_wfp->Scale(1./h_cd_reco_wfp->Integral());
    h_us_reco_wfp->Scale(1./h_us_reco_wfp->Integral());
    h_cb_reco_wfp->Scale(1./h_cb_reco_wfp->Integral());
    h_ub_reco_wfp->Scale(1./h_ub_reco_wfp->Integral());
    h_x_reco_wfp->Scale(1./h_x_reco_wfp->Integral());

    // Draw the histogram


    tdrDraw(h_x_reco_wfp,"Pz",kFullDiamond,kViolet+1);
    h_x_reco_wfp->SetMarkerSize(0.8);

    tdrDraw(h_ub_reco_wfp,"Pz",kFullDiamond,kRed-4);
    h_ub_reco_wfp->SetMarkerSize(0.8);

    tdrDraw(h_cb_reco_wfp,"Pz",kFullDiamond,kSpring-5);
    h_cb_reco_wfp->SetMarkerSize(0.8);

    tdrDraw(h_us_reco_wfp,"Pz",kFullDiamond,kOrange-2);
    h_us_reco_wfp->SetMarkerSize(0.8);

    tdrDraw(h_cd_reco_wfp,"Pz",kFullDiamond,kGreen+3);
    h_cd_reco_wfp->SetMarkerSize(0.8);

    tdrDraw(h_ud_reco_wfp,"Pz",kFullDiamond,kAzure+1);
    h_ud_reco_wfp->SetMarkerSize(0.8);

    tdrDraw(h_cs_reco_wfp,"Pz",kFullDiamond,kOrange+7);
    h_cs_reco_wfp->SetMarkerSize(0.8);


    // Create a legend
    TLegend *leg9 = tdrLeg(0.75,0.7-0.05*7,0.9,0.8);
    leg9->AddEntry(h_cs_reco_wfp, "CS", "PLE");
    leg9->AddEntry(h_ud_reco_wfp, "UD", "PLE");
    leg9->AddEntry(h_cd_reco_wfp, "CD", "PLE");
    leg9->AddEntry(h_us_reco_wfp, "US", "PLE");
    leg9->AddEntry(h_cb_reco_wfp, "CB", "PLE");
    leg9->AddEntry(h_ub_reco_wfp, "UB", "PLE");
    leg9->AddEntry(h_x_reco_wfp, "X", "PLE");
    leg9->SetTextSize(0.035);

    
    //leg->Draw();

    // Update the canvas to reflect the changes
    TLatex *tex9 = new TLatex();
    tex9->SetNDC(); tex9->SetTextSize(0.035);
    tex9->DrawLatex(0.18,0.75,"without fitProb");
    tex9->DrawLatex(0.18,0.71,"recomass > 30 GeV");
    gPad->Update();

    // Save the canvas as a .pdf file
    c9->SaveAs("pdf/jetpairsmass_reco_without_fitprob2.pdf");
    */
}