#include <TMath.h>
#include <TF1.h>
#include <TH1F.h>
#include <TH1D.h>
#include <TH3D.h>
#include <TProfile2D.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include <TStyle.h>
#include <iostream>
#include <algorithm>
#include "tdrstyle_mod22.C"

void MCvsDATA_pt() {
    TFile *file = new TFile("output_stag3new.root", "READ");
    TH3D* h3PtFlavorPairs_DATAMC_MC = (TH3D*)file->Get("h3PtFlavorPairs_DATAMC");
      // Project Z for different indices and draw
      TH1D* h3all = h3PtFlavorPairs_DATAMC_MC->ProjectionZ("h3all", 1, 3, 1, 3);

      TH1D* h3gencsall = h3PtFlavorPairs_DATAMC_MC->ProjectionZ("h3gencsall", 1, 1, 1, 3);
      TH1D* h3genudall = h3PtFlavorPairs_DATAMC_MC->ProjectionZ("h3genudall", 2, 2, 1, 3);
      TH1D* h3genxall = h3PtFlavorPairs_DATAMC_MC->ProjectionZ("h3genxall", 3, 3, 1, 3);

      TH1D* h3tagcsall = h3PtFlavorPairs_DATAMC_MC->ProjectionZ("h3tagcsall", 1, 3, 1, 1);
      TH1D* h3tagudall = h3PtFlavorPairs_DATAMC_MC->ProjectionZ("h3tagudall", 1, 3, 2, 2);
      TH1D* h3tagxall = h3PtFlavorPairs_DATAMC_MC->ProjectionZ("h3tagxall", 1, 3, 3, 3);

      TH1D* h3gencstagcs = h3PtFlavorPairs_DATAMC_MC->ProjectionZ("h3gencstagcs", 1, 1, 1, 1);
      TH1D* h3gencstagud = h3PtFlavorPairs_DATAMC_MC->ProjectionZ("h3gencstagud", 1, 1, 2, 2);
      TH1D* h3gencstagx = h3PtFlavorPairs_DATAMC_MC->ProjectionZ("h3gencstagx", 1, 1, 3, 3);
      
      TH1D* h3genudtagcs = h3PtFlavorPairs_DATAMC_MC->ProjectionZ("h3genudtagcs", 2, 2, 1, 1);
      TH1D* h3genudtagud = h3PtFlavorPairs_DATAMC_MC->ProjectionZ("h3genudtagud", 2, 2, 2, 2);
      TH1D* h3genudtagx = h3PtFlavorPairs_DATAMC_MC->ProjectionZ("h3genudtagx", 2, 2, 3, 3);
      
      TH1D* h3genxtagcs = h3PtFlavorPairs_DATAMC_MC->ProjectionZ("h3genxtagcs", 3, 3, 1, 1);
      TH1D* h3genxtagud = h3PtFlavorPairs_DATAMC_MC->ProjectionZ("h3genxtagud", 3, 3, 2, 2);
      TH1D* h3genxtagx = h3PtFlavorPairs_DATAMC_MC->ProjectionZ("h3genxtagx", 3, 3, 3, 3);

      TFile *file3 = new TFile("output_stag3_scaledmass.root", "READ");
      TH3D* h3PtFlavorPairs_DATAMC_SCALEDMASS = (TH3D*)file3->Get("h3PtFlavorPairs_DATAMC");

      TFile *file2 = new TFile("output_stag_DATA2.root", "READ");
      TH3D* h3PtFlavorPairs_DATAMC_DATA = (TH3D*)file2->Get("h3PtFlavorPairs_DATAMC");

      TH1D* h3all_data = h3PtFlavorPairs_DATAMC_DATA->ProjectionZ("h3all_data", 1, 3, 1, 3);

      TH1D* h3tagcsall_data = h3PtFlavorPairs_DATAMC_DATA->ProjectionZ("h3tagcsall_data", 1, 3, 1, 1);
      TH1D* h3tagudall_data = h3PtFlavorPairs_DATAMC_DATA->ProjectionZ("h3tagudall_data", 1, 3, 2, 2);
      TH1D* h3tagxall_data = h3PtFlavorPairs_DATAMC_DATA->ProjectionZ("h3tagxall_data", 1, 3, 3, 3);

      TH1D* h3corr = new TH1D("h3corr",";Mass;N",200,0,200);

      TH1D* h3corrdata = new TH1D("h3corrdata",";Mass;N",200,0,200);


      // Cloning and renaming histograms
TH1D* h3all_scaled = (TH1D*)h3all->Clone("h3all_scaled");
TH1D* h3all_scaled2 = (TH1D*)h3all->Clone("h3all_scaled2");

TH1D* h3gencsall_scaled = (TH1D*)h3gencsall->Clone("h3gencsall_scaled");
TH1D* h3genudall_scaled = (TH1D*)h3genudall->Clone("h3genudall_scaled");
TH1D* h3genxall_scaled = (TH1D*)h3genxall->Clone("h3genxall_scaled");

TH1D* h3tagcsall_scaled = (TH1D*)h3tagcsall->Clone("h3tagcsall_scaled");
TH1D* h3tagudall_scaled = (TH1D*)h3tagudall->Clone("h3tagudall_scaled");
TH1D* h3tagxall_scaled = (TH1D*)h3tagxall->Clone("h3tagxall_scaled");

TH1D* h3gencstagcs_scaled = (TH1D*)h3gencstagcs->Clone("h3gencstagcs_scaled");
TH1D* h3gencstagud_scaled = (TH1D*)h3gencstagud->Clone("h3gencstagud_scaled");
TH1D* h3gencstagx_scaled = (TH1D*)h3gencstagx->Clone("h3gencstagx_scaled");

TH1D* h3genudtagcs_scaled = (TH1D*)h3genudtagcs->Clone("h3genudtagcs_scaled");
TH1D* h3genudtagud_scaled = (TH1D*)h3genudtagud->Clone("h3genudtagud_scaled");
TH1D* h3genudtagx_scaled = (TH1D*)h3genudtagx->Clone("h3genudtagx_scaled");

TH1D* h3genxtagcs_scaled = (TH1D*)h3genxtagcs->Clone("h3genxtagcs_scaled");
TH1D* h3genxtagud_scaled = (TH1D*)h3genxtagud->Clone("h3genxtagud_scaled");
TH1D* h3genxtagx_scaled = (TH1D*)h3genxtagx->Clone("h3genxtagx_scaled");


    
    h3gencstagcs->Scale(1./h3all->Integral());
    h3gencstagud->Scale(1./h3all->Integral());
    h3gencstagx->Scale(1./h3all->Integral());
    
    h3genudtagcs->Scale(1./h3all->Integral());
    h3genudtagud->Scale(1./h3all->Integral());
    h3genudtagx->Scale(1./h3all->Integral());

    h3genxtagcs->Scale(1./h3all->Integral());
    h3genxtagud->Scale(1./h3all->Integral());
    h3genxtagx->Scale(1./h3all->Integral());

    h3gencsall->Scale(1./h3all->Integral());
    h3genudall->Scale(1./h3all->Integral());
    h3genxall->Scale(1./h3all->Integral());

    h3tagcsall->Scale(1./h3all->Integral());
    h3tagudall->Scale(1./h3all->Integral());
    h3tagxall->Scale(1./h3all->Integral());

    h3all->Scale(1./h3all->Integral());

    h3tagcsall_data->Scale(1./h3all_data->Integral());
    h3tagudall_data->Scale(1./h3all_data->Integral());
    h3tagxall_data->Scale(1./h3all_data->Integral());

    h3all_data->Scale(1./h3all_data->Integral());

    // Scaling histograms

h3gencstagx_scaled->Scale(1);
h3genudtagx_scaled->Scale(1);
h3genxtagx_scaled->Scale(1);

h3gencstagud_scaled->Scale(0.9);
h3genudtagud_scaled->Scale(0.8);
h3genxtagud_scaled->Scale(0.8);

h3gencstagcs_scaled->Scale(0.9);
h3genudtagcs_scaled->Scale(0.8);
h3genxtagcs_scaled->Scale(0.8);

// Reset h3all_scaled to zero
h3all_scaled->Reset();
// Summing the scaled histograms
h3all_scaled->Add(h3gencstagcs_scaled);
h3all_scaled->Add(h3gencstagud_scaled);
h3all_scaled->Add(h3gencstagx_scaled);
h3all_scaled->Add(h3genudtagcs_scaled);
h3all_scaled->Add(h3genudtagud_scaled);
h3all_scaled->Add(h3genudtagx_scaled);
h3all_scaled->Add(h3genxtagcs_scaled);
h3all_scaled->Add(h3genxtagud_scaled);
h3all_scaled->Add(h3genxtagx_scaled);

h3tagcsall_scaled->Reset();
h3tagcsall_scaled->Add(h3gencstagcs_scaled);
h3tagcsall_scaled->Add(h3genudtagcs_scaled);
h3tagcsall_scaled->Add(h3genxtagcs_scaled);

h3tagudall_scaled->Reset();
h3tagudall_scaled->Add(h3gencstagud_scaled);
h3tagudall_scaled->Add(h3genudtagud_scaled);
h3tagudall_scaled->Add(h3genxtagud_scaled);

h3tagxall_scaled->Reset();
h3tagxall_scaled->Add(h3gencstagx_scaled);
h3tagxall_scaled->Add(h3genudtagx_scaled);
h3tagxall_scaled->Add(h3genxtagx_scaled);

h3gencsall_scaled->Reset();
h3gencsall_scaled->Add(h3gencstagcs_scaled);
h3gencsall_scaled->Add(h3gencstagud_scaled);
h3gencsall_scaled->Add(h3gencstagx_scaled);

h3genudall_scaled->Reset();
h3genudall_scaled->Add(h3genudtagcs_scaled);
h3genudall_scaled->Add(h3genudtagud_scaled);
h3genudall_scaled->Add(h3genudtagx_scaled);

h3genxall_scaled->Reset();
h3genxall_scaled->Add(h3genxtagcs_scaled);
h3genxall_scaled->Add(h3genxtagud_scaled);
h3genxall_scaled->Add(h3genxtagx_scaled);

// Final scaling

double scale_factor2 = 1.0 / h3all_scaled->Integral();

h3gencstagx_scaled->Scale(scale_factor2);
h3genudtagx_scaled->Scale(scale_factor2);
h3genxtagx_scaled->Scale(scale_factor2);

h3gencstagud_scaled->Scale(scale_factor2);
h3genudtagud_scaled->Scale(scale_factor2);
h3genxtagud_scaled->Scale(scale_factor2);

h3gencstagcs_scaled->Scale(scale_factor2);
h3genudtagcs_scaled->Scale(scale_factor2);
h3genxtagcs_scaled->Scale(scale_factor2);

h3gencsall_scaled->Scale(scale_factor2);
h3genudall_scaled->Scale(scale_factor2);
h3genxall_scaled->Scale(scale_factor2);

h3tagcsall_scaled->Scale(scale_factor2);
h3tagudall_scaled->Scale(scale_factor2);
h3tagxall_scaled->Scale(scale_factor2);

h3all_scaled->Scale(scale_factor2);



    //h3corr->Add(h3,h3x,1,-1);

    //h3corrdata->Add(h3data,h3x,1,-1);

    TH1D *h3divcs = (TH1D*)h3tagcsall->Clone("h3divcs");
    h3divcs->Divide(h3gencsall);

    TH1D *h3divud = (TH1D*)h3tagudall->Clone("h3divud");
    h3divud->Divide(h3genudall);

    TH1D *h3divx = (TH1D*)h3tagxall->Clone("h3divx");
    h3divx->Divide(h3genxall);

    //TH1D *h3divcorr = (TH1D*)h3corrdata->Clone("h3divcorr");
    //h3divcorr->Divide(h3corr);

      
    lumi_136TeV = "Run3 simulation";
    extraText = "Private";

        // Create a canvas
    TCanvas *c3 = new TCanvas("c3", "Canvas with 3x3 Grid", 2560, 1440);

    // Divide the canvas into a 3x3 grid
    c3->Divide(4, 4);
    gStyle->SetOptStat(0);
    c3->cd(1);

    gPad->SetLeftMargin(0.1);
    gPad->SetRightMargin(0.01);
    gPad->SetBottomMargin(0.08);
    gPad->SetTopMargin(0);

    // Draw the histogram
    tdrDraw(h3gencstagx,"HPz",kNone,kAzure+7,kSolid,-1,1001,kAzure+7);
    h3gencstagx->SetFillColorAlpha(kAzure+7,0.25);

    tdrDraw(h3gencstagx_scaled,"HPz",kNone,kSpring-5,kSolid,-1,1001,kSpring-5);
    h3gencstagx_scaled->SetFillColorAlpha(kSpring-5,0.25);

    h3gencstagx->GetXaxis()->SetTitle("(s-c)/(s+c)");
    h3gencstagx->GetYaxis()->SetTitle("N frac");

    // Set the x-axis range
    //h3gencstagx->GetXaxis()->SetRangeUser(55, 115); // Adjust the range as needed
    h3gencstagx->GetYaxis()->SetRangeUser(0, 0.0101);
    h3gencstagx->SetTitle("");

     // Update the canvas to reflect the changes
    TLatex *tex1 = new TLatex();
    tex1->SetNDC(); tex1->SetTextSize(0.045);
    tex1->DrawLatex(0.17,0.85,"gencs,tagx");

    // Update the canvas to reflect the changes
    gPad->Update();

    c3->cd(2);

    gPad->SetLeftMargin(0.1);
    gPad->SetRightMargin(0.01);
    gPad->SetBottomMargin(0.08);
    gPad->SetTopMargin(0);


        // Draw the histogram
    tdrDraw(h3genudtagx,"HPz",kNone,kAzure+7,kSolid,-1,1001,kAzure+7);
    h3genudtagx->SetFillColorAlpha(kAzure+7,0.25);

    tdrDraw(h3genudtagx_scaled,"HPz",kNone,kSpring-5,kSolid,-1,1001,kSpring-5);
    h3genudtagx_scaled->SetFillColorAlpha(kSpring-5,0.25);

    h3genudtagx->GetXaxis()->SetTitle("(s-c)/(s+c)");
    h3genudtagx->GetYaxis()->SetTitle("N frac");

    // Set the x-axis range
    h3genudtagx->GetYaxis()->SetRangeUser(0, 0.0135); // Adjust the range as needed
    h3genudtagx->SetTitle("");

    TLatex *tex2 = new TLatex();
    tex2->SetNDC(); tex2->SetTextSize(0.045);
    tex2->DrawLatex(0.17,0.85,"genud,tagx");
    // Update the canvas to reflect the changes
    gPad->Update();

    c3->cd(3);

    gPad->SetLeftMargin(0.1);
    gPad->SetRightMargin(0.01);
    gPad->SetBottomMargin(0.08);
    gPad->SetTopMargin(0);

    // Draw the histogram
    tdrDraw(h3genxtagx,"HPz",kNone,kAzure+7,kSolid,-1,1001,kAzure+7);
    h3genxtagx->SetFillColorAlpha(kAzure+7,0.25);

    tdrDraw(h3genxtagx_scaled,"HPz",kNone,kSpring-5,kSolid,-1,1001,kSpring-5);
    h3genxtagx_scaled->SetFillColorAlpha(kSpring-5,0.25);

    h3genxtagx->GetXaxis()->SetTitle("(s-c)/(s+c)");
    h3genxtagx->GetYaxis()->SetTitle("N frac");

        // Set the x-axis range
    h3genxtagx->GetYaxis()->SetRangeUser(0, 0.014); // Adjust the range as needed
    h3genxtagx->SetTitle("");

    TLatex *tex3 = new TLatex();
    tex3->SetNDC(); tex3->SetTextSize(0.045);
    tex3->DrawLatex(0.17,0.85,"genx,tagx");

    // Update the canvas to reflect the changes
    gPad->Update();


    c3->cd(4);

    gPad->SetLeftMargin(0.1);
    gPad->SetRightMargin(0.01);
    gPad->SetBottomMargin(0.08);
    gPad->SetTopMargin(0);

    // Draw the histogram
    tdrDraw(h3tagxall,"HPz",kNone,kAzure+7,kSolid,-1,1001,kAzure+7);
    h3tagxall->SetFillColorAlpha(kAzure+7,0.25);

    tdrDraw(h3tagxall_scaled,"HPz",kNone,kSpring-5,kSolid,-1,1001,kSpring-5);
    h3tagxall_scaled->SetFillColorAlpha(kSpring-5,0.25);

    tdrDraw(h3tagxall_data,"Pz",kFullCircle,kPink-9);
    h3tagxall_data->SetMarkerSize(1);

    h3tagxall->GetXaxis()->SetTitle("Mass (GeV)");
    h3tagxall->GetYaxis()->SetTitle("N frac");

        // Set the x-axis range
    //h3tagxall->GetXaxis()->SetRangeUser(55, 115); // Adjust the range as needed
    h3tagxall->GetYaxis()->SetRangeUser(0, 0.041); // Adjust the range as needed
    h3tagxall->SetTitle("");

    TLegend *leg4 = tdrLeg(0.8,0.8-0.05*2,0.9,0.82);
    leg4->AddEntry(h3tagxall, "MC", "FPLE");
    leg4->AddEntry(h3tagxall_scaled, "scaled MC", "FPLE");
    leg4->AddEntry(h3tagxall_data, "DATA", "PLE");

    TLatex *tex4 = new TLatex();
    tex4->SetNDC(); tex4->SetTextSize(0.045);
    tex4->DrawLatex(0.17,0.85,"genall,tagx");

    // Update the canvas to reflect the changes
    gPad->Update();



    c3->cd(5);

    gPad->SetLeftMargin(0.1);
    gPad->SetRightMargin(0.01);
    gPad->SetBottomMargin(0.08);
    gPad->SetTopMargin(0);

    // Draw the histogram
    tdrDraw(h3gencstagud,"HPz",kNone,kAzure+7,kSolid,-1,1001,kAzure+7);
    h3gencstagud->SetFillColorAlpha(kAzure+7,0.25);

    tdrDraw(h3gencstagud_scaled,"HPz",kNone,kSpring-5,kSolid,-1,1001,kSpring-5);
    h3gencstagud_scaled->SetFillColorAlpha(kSpring-5,0.25);

    h3gencstagud->GetXaxis()->SetTitle("(s-c)/(s+c)");
    h3gencstagud->GetYaxis()->SetTitle("N frac");

        // Set the x-axis range
    h3gencstagud->GetYaxis()->SetRangeUser(0, 0.00125); // Adjust the range as needed
    h3gencstagud->SetTitle("");
    TLatex *tex5 = new TLatex();
    tex5->SetNDC(); tex5->SetTextSize(0.045);
    tex5->DrawLatex(0.17,0.85,"gencs,tagud");

    // Update the canvas to reflect the changes
    gPad->Update();

    c3->cd(6);

    gPad->SetLeftMargin(0.1);
    gPad->SetRightMargin(0.01);
    gPad->SetBottomMargin(0.08);
    gPad->SetTopMargin(0);

    // Draw the histogram
    tdrDraw(h3genudtagud,"HPz",kNone,kAzure+7,kSolid,-1,1001,kAzure+7);
    h3genudtagud->SetFillColorAlpha(kAzure+7,0.25);

    tdrDraw(h3genudtagud_scaled,"HPz",kNone,kSpring-5,kSolid,-1,1001,kSpring-5);
    h3genudtagud_scaled->SetFillColorAlpha(kSpring-5,0.25);

    h3genudtagud->GetXaxis()->SetTitle("(s-c)/(s+c)");
    h3genudtagud->GetYaxis()->SetTitle("N frac");

        // Set the x-axis range
    h3genudtagud->GetYaxis()->SetRangeUser(0, 0.0038); // Adjust the range as needed
    h3genudtagud->SetTitle("");

    TLatex *tex6 = new TLatex();
    tex6->SetNDC(); tex6->SetTextSize(0.045);
    tex6->DrawLatex(0.17,0.85,"genud,tagud");

    // Update the canvas to reflect the changes
    gPad->Update();

    c3->cd(7);

    gPad->SetLeftMargin(0.1);
    gPad->SetRightMargin(0.01);
    gPad->SetBottomMargin(0.08);
    gPad->SetTopMargin(0);

    // Draw the histogram
    tdrDraw(h3genxtagud,"HPz",kNone,kAzure+7,kSolid,-1,1001,kAzure+7);
    h3genxtagud->SetFillColorAlpha(kAzure+7,0.25);

    tdrDraw(h3genxtagud_scaled,"HPz",kNone,kSpring-5,kSolid,-1,1001,kSpring-5);
    h3genxtagud_scaled->SetFillColorAlpha(kSpring-5,0.25);

    h3genxtagud->GetXaxis()->SetTitle("(s-c)/(s+c)");
    h3genxtagud->GetYaxis()->SetTitle("N frac");

        // Set the x-axis range
    h3genxtagud->GetYaxis()->SetRangeUser(0, 0.003); // Adjust the range as needed
    h3genxtagud->SetTitle("");

    TLatex *tex7 = new TLatex();
    tex7->SetNDC(); tex7->SetTextSize(0.045);
    tex7->DrawLatex(0.17,0.85,"genx,tagud");

    // Update the canvas to reflect the changes
    gPad->Update();

    c3->cd(8);

    gPad->SetLeftMargin(0.1);
    gPad->SetRightMargin(0.01);
    gPad->SetBottomMargin(0.08);
    gPad->SetTopMargin(0);

    // Draw the histogram
    tdrDraw(h3tagudall,"HPz",kNone,kAzure+7,kSolid,-1,1001,kAzure+7);
    h3tagudall->SetFillColorAlpha(kAzure+7,0.25);

    tdrDraw(h3tagudall_scaled,"HPz",kNone,kSpring-5,kSolid,-1,1001,kSpring-5);
    h3tagudall_scaled->SetFillColorAlpha(kSpring-5,0.25);

    tdrDraw(h3tagudall_data,"Pz",kFullCircle,kPink-9);
    h3tagudall_data->SetMarkerSize(1);

    h3tagudall->GetXaxis()->SetTitle("(s-c)/(s+c)");
    h3tagudall->GetYaxis()->SetTitle("N frac");

        // Set the x-axis range
    h3tagudall->GetYaxis()->SetRangeUser(0, 0.0075); // Adjust the range as needed
    h3tagudall->SetTitle("");

    TLegend *leg8 = tdrLeg(0.8,0.8-0.05*2,0.9,0.82);
    leg8->AddEntry(h3tagudall, "MC", "FPLE");
    leg8->AddEntry(h3tagudall_scaled, "scaled MC", "FPLE");
    leg8->AddEntry(h3tagudall_data, "DATA", "PLE");


    TLatex *tex8 = new TLatex();
    tex8->SetNDC(); tex8->SetTextSize(0.045);
    tex8->DrawLatex(0.17,0.85,"genall,tagud");

    // Update the canvas to reflect the changes
    gPad->Update();

    c3->cd(9);

    gPad->SetLeftMargin(0.1);
    gPad->SetRightMargin(0.01);
    gPad->SetBottomMargin(0.08);
    gPad->SetTopMargin(0);

    // Draw the histogram
    tdrDraw(h3gencstagcs,"HPz",kNone,kAzure+7,kSolid,-1,1001,kAzure+7);
    h3gencstagcs->SetFillColorAlpha(kAzure+7,0.25);

    tdrDraw(h3gencstagcs_scaled,"HPz",kNone,kSpring-5,kSolid,-1,1001,kSpring-5);
    h3gencstagcs_scaled->SetFillColorAlpha(kSpring-5,0.25);

    h3gencstagcs->GetXaxis()->SetTitle("(s-c)/(s+c)");
    h3gencstagcs->GetYaxis()->SetTitle("N frac");

    h3gencstagcs->GetYaxis()->SetRangeUser(0, 0.0028); // Adjust the range as needed
    h3gencstagcs->SetTitle("");

    TLatex *tex9 = new TLatex();
    tex9->SetNDC(); tex9->SetTextSize(0.045);
    tex9->DrawLatex(0.17,0.85,"gencs,tagcs");

    // Update the canvas to reflect the changes
    gPad->Update();

    c3->cd(10);

    gPad->SetLeftMargin(0.1);
    gPad->SetRightMargin(0.01);
    gPad->SetBottomMargin(0.08);
    gPad->SetTopMargin(0);

    // Draw the histogram
    tdrDraw(h3genudtagcs,"HPz",kNone,kAzure+7,kSolid,-1,1001,kAzure+7);
    h3genudtagcs->SetFillColorAlpha(kAzure+7,0.25);

    tdrDraw(h3genudtagcs_scaled,"HPz",kNone,kSpring-5,kSolid,-1,1001,kSpring-5);
    h3genudtagcs_scaled->SetFillColorAlpha(kSpring-5,0.25);

    h3genudtagcs->GetXaxis()->SetTitle("(s-c)/(s+c)");
    h3genudtagcs->GetYaxis()->SetTitle("N frac");

        // Set the x-axis range
    h3genudtagcs->SetMinimum(0);
    //h3genudtagcs->GetYaxis()->SetRangeUser(0, 0.25); // Adjust the range as needed
    h3genudtagcs->SetTitle("");

    TLatex *tex10 = new TLatex();
    tex10->SetNDC(); tex10->SetTextSize(0.045);
    tex10->DrawLatex(0.17,0.85,"genud,tagcs");

    // Update the canvas to reflect the changes
    gPad->Update();

    c3->cd(11);

    gPad->SetLeftMargin(0.1);
    gPad->SetRightMargin(0.01);
    gPad->SetBottomMargin(0.08);
    gPad->SetTopMargin(0);

    // Draw the histogram
    tdrDraw(h3genxtagcs,"HPz",kNone,kAzure+7,kSolid,-1,1001,kAzure+7);
    h3genxtagcs->SetFillColorAlpha(kAzure+7,0.25);

    tdrDraw(h3genxtagcs_scaled,"HPz",kNone,kSpring-5,kSolid,-1,1001,kSpring-5);
    h3genxtagcs_scaled->SetFillColorAlpha(kSpring-5,0.25);

    h3genxtagcs->GetXaxis()->SetTitle("(s-c)/(s+c)");
    h3genxtagcs->GetYaxis()->SetTitle("N frac");

        // Set the x-axis range
    h3genxtagcs->GetYaxis()->SetRangeUser(0, 0.00145); // Adjust the range as needed
    h3genxtagcs->SetTitle("");

    TLatex *tex11 = new TLatex();
    tex11->SetNDC(); tex11->SetTextSize(0.045);
    tex11->DrawLatex(0.17,0.85,"genx,tagcs");

    // Update the canvas to reflect the changes
    gPad->Update();

    c3->cd(12);

    gPad->SetLeftMargin(0.1);
    gPad->SetRightMargin(0.01);
    gPad->SetBottomMargin(0.08);
    gPad->SetTopMargin(0);

    // Draw the histogram
    tdrDraw(h3tagcsall,"HPz",kNone,kAzure+7,kSolid,-1,1001,kAzure+7);
    h3tagcsall->SetFillColorAlpha(kAzure+7,0.25);

    tdrDraw(h3tagcsall_scaled,"HPz",kNone,kSpring-5,kSolid,-1,1001,kSpring-5);
    h3tagcsall_scaled->SetFillColorAlpha(kSpring-5,0.25);

    tdrDraw(h3tagcsall_data,"Pz",kFullCircle,kPink-9);
    h3tagcsall_data->SetMarkerSize(1);

    h3tagcsall->GetXaxis()->SetTitle("(s-c)/(s+c)");
    h3tagcsall->GetYaxis()->SetTitle("N frac");

        // Set the x-axis range
    h3tagcsall->GetYaxis()->SetRangeUser(0, 0.0039); // Adjust the range as needed
    h3tagcsall->SetTitle("");

    TLegend *leg12 = tdrLeg(0.8,0.8-0.05*2,0.9,0.82);
    leg12->AddEntry(h3tagcsall, "MC", "FPLE");
    leg12->AddEntry(h3tagcsall_scaled, "scaled MC", "FPLE");
    leg12->AddEntry(h3tagcsall_data, "DATA", "PLE");

    TLatex *tex12 = new TLatex();
    tex12->SetNDC(); tex12->SetTextSize(0.045);
    tex12->DrawLatex(0.17,0.85,"genall,tagcs");

    // Update the canvas to reflect the changes
    gPad->Update();

    c3->cd(13);

    gPad->SetLeftMargin(0.1);
    gPad->SetRightMargin(0.01);
    gPad->SetBottomMargin(0.08);
    gPad->SetTopMargin(0);

    // Draw the histogram
    tdrDraw(h3gencsall,"HPz",kNone,kAzure+7,kSolid,-1,1001,kAzure+7);
    h3gencsall->SetFillColorAlpha(kAzure+7,0.25);

    tdrDraw(h3gencsall_scaled,"HPz",kNone,kSpring-5,kSolid,-1,1001,kSpring-5);
    h3gencsall_scaled->SetFillColorAlpha(kSpring-5,0.25);

    h3gencsall->GetXaxis()->SetTitle("(s-c)/(s+c)");
    h3gencsall->GetYaxis()->SetTitle("N frac");

        // Set the x-axis range
    h3gencsall->GetYaxis()->SetRangeUser(0, 0.0135); // Adjust the range as needed
    h3gencsall->SetTitle("");

    TLatex *tex13 = new TLatex();
    tex13->SetNDC(); tex13->SetTextSize(0.045);
    tex13->DrawLatex(0.17,0.85,"gencs,tagall");

    // Update the canvas to reflect the changes
    gPad->Update();

    c3->cd(14);

    gPad->SetLeftMargin(0.1);
    gPad->SetRightMargin(0.01);
    gPad->SetBottomMargin(0.08);
    gPad->SetTopMargin(0);

    // Draw the histogram
    tdrDraw(h3genudall,"HPz",kNone,kAzure+7,kSolid,-1,1001,kAzure+7);
    h3genudall->SetFillColorAlpha(kAzure+7,0.25);

    tdrDraw(h3genudall_scaled,"HPz",kNone,kSpring-5,kSolid,-1,1001,kSpring-5);
    h3genudall_scaled->SetFillColorAlpha(kSpring-5,0.25);

    h3genudall->GetXaxis()->SetTitle("(s-c)/(s+c)");
    h3genudall->GetYaxis()->SetTitle("N frac");

        // Set the x-axis range
    h3genudall->GetYaxis()->SetRangeUser(0, 0.017); // Adjust the range as needed
    h3genudall->SetTitle("");

    TLatex *tex14 = new TLatex();
    tex14->SetNDC(); tex14->SetTextSize(0.045);
    tex14->DrawLatex(0.17,0.85,"genud,tagall");

    // Update the canvas to reflect the changes
    gPad->Update();


    c3->cd(15);

    gPad->SetLeftMargin(0.1);
    gPad->SetRightMargin(0.01);
    gPad->SetBottomMargin(0.08);
    gPad->SetTopMargin(0);

    // Draw the histogram
    tdrDraw(h3genxall,"HPz",kNone,kAzure+7,kSolid,-1,1001,kAzure+7);
    h3genxall->SetFillColorAlpha(kAzure+7,0.25);

    tdrDraw(h3genxall_scaled,"HPz",kNone,kSpring-5,kSolid,-1,1001,kSpring-5);
    h3genxall_scaled->SetFillColorAlpha(kSpring-5,0.25);

    h3genxall->GetXaxis()->SetTitle("(s-c)/(s+c)");
    h3genxall->GetYaxis()->SetTitle("N frac");

        // Set the x-axis range
    h3genxall->GetYaxis()->SetRangeUser(0, 0.017); // Adjust the range as needed
    h3genxall->SetTitle("");

    TLatex *tex15 = new TLatex();
    tex15->SetNDC(); tex15->SetTextSize(0.045);
    tex15->DrawLatex(0.17,0.85,"genx,tagall");

    // Update the canvas to reflect the changes
    gPad->Update();


    c3->cd(16);

    gPad->SetLeftMargin(0.1);
    gPad->SetRightMargin(0.01);
    gPad->SetBottomMargin(0.08);
    gPad->SetTopMargin(0);

    // Draw the histogram
    tdrDraw(h3all,"HPz",kNone,kAzure+7,kSolid,-1,1001,kAzure+7);
    h3all->SetFillColorAlpha(kAzure+7,0.25);

    tdrDraw(h3all_scaled,"HPz",kNone,kSpring-5,kSolid,-1,1001,kSpring-5);
    h3all_scaled->SetFillColorAlpha(kSpring-5,0.25);

    tdrDraw(h3all_data,"Pz",kFullCircle,kPink-9);
    h3all_data->SetMarkerSize(1);

    h3all->GetXaxis()->SetTitle("(s-c)/(s+c)");
    h3all->GetYaxis()->SetTitle("N frac");

        // Set the x-axis range
    h3all->GetYaxis()->SetRangeUser(0, 0.048); // Adjust the range as needed
    h3all->SetTitle("");

    TLegend *leg16 = tdrLeg(0.8,0.8-0.05*3,0.9,0.82);
    leg16->AddEntry(h3all, "MC", "FPLE");
    leg16->AddEntry(h3all_scaled, "scaled MC", "FPLE");
    leg16->AddEntry(h3all_data, "DATA", "PLE");
    

    TLatex *tex16 = new TLatex();
    tex16->SetNDC(); tex16->SetTextSize(0.045);
    tex16->DrawLatex(0.17,0.85,"all");

    // Update the canvas to reflect the changes
    gPad->Update();


    // Save the canvas as a .pdf file
    c3->SaveAs("pdf/MCvsDATA_Pt.pdf");








setTDRStyle();
        // Create a canvas
    TCanvas *c100 = new TCanvas("c100", "Canvas with 3x3 Grid", 2560, 1140);
    

    // Divide the canvas into a 3x3 grid
    c100->Divide(4, 2);

    c100->cd(1);
    
    //TH1D *h101 = tdrHist("h101","Average mass (GeV)",0,0.1,"Jet pair, reco",55,115);
    //TCanvas *c101 = tdrCanvas("c101",h101,8,11,kSquare);

    gPad->SetLeftMargin(0.13);
    gPad->SetRightMargin(0.01);
    gPad->SetBottomMargin(0.1);
    gPad->SetTopMargin(0);

    // Draw the histogram
    tdrDraw(h3tagcsall,"HPz",kNone,kAzure+7,kSolid,-1,1001,kAzure+7);
    h3tagcsall->SetFillColorAlpha(kAzure+7,0.25);

    tdrDraw(h3tagcsall_scaled,"HPz",kNone,kSpring-5,kSolid,-1,1001,kSpring-5);
    h3tagcsall_scaled->SetFillColorAlpha(kSpring-5,0.25);

    tdrDraw(h3tagcsall_data,"Pz",kFullCircle,kPink-9);
    h3tagcsall_data->SetMarkerSize(1);

    h3tagcsall->GetXaxis()->SetTitle("(s-c)/(s+c)");
    h3tagcsall->GetYaxis()->SetTitle("N frac");

        // Set the x-axis range
    h3tagcsall->GetXaxis()->SetRangeUser(55, 115); // Adjust the range as needed
    h3tagcsall->GetYaxis()->SetRangeUser(0, 0.0049);
    h3tagcsall->GetYaxis()->SetTitleSize(0.045);
    h3tagcsall->GetXaxis()->SetTitleSize(0.045);
    h3tagcsall->GetYaxis()->SetLabelSize(0.045);
    h3tagcsall->GetXaxis()->SetLabelSize(0.045);
    // Adjust the y-axis title location
    h3tagcsall->GetYaxis()->SetTitleOffset(1.5);

    TLegend *leg103 = tdrLeg(0.72,1.15-0.05*4,0.9,0.78);
    leg103->AddEntry(h3tagcsall, "MC", "FPLE");
    leg103->AddEntry(h3tagcsall_scaled, "scaled MC", "FPLE");
    leg103->AddEntry(h3tagcsall_data, "DATA", "PLE");
    //leg103->SetTextSize(0.037);

    TLatex *tex103 = new TLatex();
    tex103->SetNDC(); tex103->SetTextSize(0.045);
    tex103->DrawLatex(0.17,0.92,"genall,tagcs");

    // Update the canvas to reflect the changes
    gPad->Update();

    c100->cd(2);

    gPad->SetLeftMargin(0.13);
    gPad->SetRightMargin(0.01);
    gPad->SetBottomMargin(0.1);
    gPad->SetTopMargin(0);

    // Draw the histogram
    tdrDraw(h3tagudall,"HPz",kNone,kAzure+7,kSolid,-1,1001,kAzure+7);
    h3tagudall->SetFillColorAlpha(kAzure+7,0.25);

    tdrDraw(h3tagudall_scaled,"HPz",kNone,kSpring-5,kSolid,-1,1001,kSpring-5);
    h3tagudall_scaled->SetFillColorAlpha(kSpring-5,0.25);

    tdrDraw(h3tagudall_data,"Pz",kFullCircle,kPink-9);
    h3tagudall_data->SetMarkerSize(1);

    h3tagudall->GetXaxis()->SetTitle("(s-c)/(s+c)");
    h3tagudall->GetYaxis()->SetTitle("N frac");

        // Set the x-axis range
    h3tagudall->GetXaxis()->SetRangeUser(55, 115); // Adjust the range as needed
    h3tagudall->GetYaxis()->SetTitleSize(0.045);
    h3tagudall->GetXaxis()->SetTitleSize(0.045);
    h3tagudall->GetYaxis()->SetLabelSize(0.045);
    h3tagudall->GetXaxis()->SetLabelSize(0.045);
    // Adjust the y-axis title location
    h3tagudall->GetYaxis()->SetTitleOffset(1.65);

    TLegend *leg102 = tdrLeg(0.72,1.15-0.05*4,0.9,0.78);
    leg102->AddEntry(h3tagudall, "MC", "FPLE");
    leg102->AddEntry(h3tagudall_scaled, "scaled MC", "FPLE");
    leg102->AddEntry(h3tagudall_data, "DATA", "PLE");


    TLatex *tex102 = new TLatex();
    tex102->SetNDC(); tex102->SetTextSize(0.045);
    tex102->DrawLatex(0.17,0.92,"genall,tagud");

    // Update the canvas to reflect the changes
    gPad->Update();

    c100->cd(3);

    gPad->SetLeftMargin(0.13);
    gPad->SetRightMargin(0.01);
    gPad->SetBottomMargin(0.1);
    gPad->SetTopMargin(0);

    // Draw the histogram
    tdrDraw(h3tagxall,"HPz",kNone,kAzure+7,kSolid,-1,1001,kAzure+7);
    h3tagxall->SetFillColorAlpha(kAzure+7,0.25);

    tdrDraw(h3tagxall_scaled,"HPz",kNone,kSpring-5,kSolid,-1,1001,kSpring-5);
    h3tagxall_scaled->SetFillColorAlpha(kSpring-5,0.25);

    tdrDraw(h3tagxall_data,"Pz",kFullCircle,kPink-9);
    h3tagxall_data->SetMarkerSize(1);

    h3tagxall->GetXaxis()->SetTitle("(s-c)/(s+c)");
    h3tagxall->GetYaxis()->SetTitle("N frac");
    h3tagxall->GetYaxis()->SetTitleSize(0.045);
    h3tagxall->GetXaxis()->SetTitleSize(0.045);
    h3tagxall->GetYaxis()->SetLabelSize(0.045);
    h3tagxall->GetXaxis()->SetLabelSize(0.045);
    // Adjust the y-axis title location
    h3tagxall->GetYaxis()->SetTitleOffset(1.65);
    

    // Set the x-axis range
    h3tagxall->GetXaxis()->SetRangeUser(55, 115); // Adjust the range as needed
    h3tagxall->GetYaxis()->SetRangeUser(0, 0.047); // Adjust the range as needed

    TLegend *leg101 = tdrLeg(0.72,1.15-0.05*4,0.9,0.78);
    leg101->AddEntry(h3tagxall, "MC", "FPLE");
    leg101->AddEntry(h3tagxall_scaled, "scaled MC", "FPLE");
    leg101->AddEntry(h3tagxall_data, "DATA", "PLE");

    TLatex *tex101 = new TLatex();
    tex101->SetNDC(); tex101->SetTextSize(0.045);
    tex101->DrawLatex(0.17,0.92,"genall,tagx");

    // Update the canvas to reflect the changes
    gPad->Update();

    c100->cd(4);

    gPad->SetLeftMargin(0.13);
    gPad->SetRightMargin(0.01);
    gPad->SetBottomMargin(0.1);
    gPad->SetTopMargin(0);

    // Draw the histogram
    tdrDraw(h3all,"HPz",kNone,kAzure+7,kSolid,-1,1001,kAzure+7);
    h3all->SetFillColorAlpha(kAzure+7,0.25);

    tdrDraw(h3all_scaled,"HPz",kNone,kSpring-5,kSolid,-1,1001,kSpring-5);
    h3all_scaled->SetFillColorAlpha(kSpring-5,0.25);

    tdrDraw(h3all_data,"Pz",kFullCircle,kPink-9);
    h3all_data->SetMarkerSize(1);

    h3all->GetXaxis()->SetTitle("(s-c)/(s+c)");
    h3all->GetYaxis()->SetTitle("N frac");
    h3all->GetYaxis()->SetTitleSize(0.045);
    h3all->GetXaxis()->SetTitleSize(0.045);
    h3all->GetYaxis()->SetLabelSize(0.045);
    h3all->GetXaxis()->SetLabelSize(0.045);
    // Adjust the y-axis title location
    h3all->GetYaxis()->SetTitleOffset(1.65);

    // Set the x-axis range
    h3all->GetXaxis()->SetRangeUser(55, 115); // Adjust the range as needed
    h3all_data->GetXaxis()->SetRangeUser(55, 115); // Adjust the range as needed

    TLegend *leg104 = tdrLeg(0.72,1.15-0.05*4,0.9,0.78);
    leg104->AddEntry(h3all, "MC", "FPLE");
    leg104->AddEntry(h3all_scaled, "scaled MC", "FPLE");
    leg104->AddEntry(h3all_data, "DATA", "PLE");
    

    TLatex *tex104 = new TLatex();
    tex104->SetNDC(); tex104->SetTextSize(0.045);
    tex104->DrawLatex(0.17,0.92,"all");

    // Update the canvas to reflect the changes
    gPad->Update();


    c100->cd(5);

    gPad->SetLeftMargin(0.13);
    gPad->SetRightMargin(0.01);
    gPad->SetBottomMargin(0.1);
    gPad->SetTopMargin(0);

    TH1D *h_tagcsvsdata = (TH1D*)h3tagcsall->Clone("h_tagcsvsdata");
    h_tagcsvsdata->Divide(h3tagcsall_data);

    TH1D *h_tagcsvsdata_scaled = (TH1D*)h3tagcsall_scaled->Clone("h_tagcsvsdata_scaled");
    h_tagcsvsdata_scaled->Divide(h3tagcsall_data);

    tdrDraw(h_tagcsvsdata,"Pz",kFullCircle,kAzure+7);
    h_tagcsvsdata->SetMarkerSize(1);

    tdrDraw(h_tagcsvsdata_scaled,"Pz",kFullCircle,kSpring-5);
    h_tagcsvsdata_scaled->SetMarkerSize(1);

    h_tagcsvsdata->GetYaxis()->SetRangeUser(0, 3.1); // Adjust the range as needed
    h_tagcsvsdata->GetYaxis()->SetTitle("MC/DATA");
    h_tagcsvsdata->GetXaxis()->SetTitle("(s-c)/(s+c)");
    h_tagcsvsdata->GetYaxis()->SetTitleSize(0.045);
    h_tagcsvsdata->GetXaxis()->SetTitleSize(0.045);
    h_tagcsvsdata->GetYaxis()->SetLabelSize(0.045);
    h_tagcsvsdata->GetXaxis()->SetLabelSize(0.045);
    // Adjust the y-axis title location
    h_tagcsvsdata->GetYaxis()->SetTitleOffset(1.5);

    TLine *line107 = new TLine(55, 1, 115, 1);
    line107->SetLineColor(kGray);
    line107->SetLineStyle(kDashed);
    line107->Draw();

    tdrDraw(h_tagcsvsdata,"Pz",kFullCircle,kAzure+7);
    h_tagcsvsdata->SetMarkerSize(1);

    tdrDraw(h_tagcsvsdata_scaled,"Pz",kFullCircle,kSpring-5);
    h_tagcsvsdata_scaled->SetMarkerSize(1);

    // Fit the ratio histogram with a constant function
    TF1* f7 = new TF1("f7", "[0]", -0.7, 0.7);
    f7->FixParameter(0, 1);
    TF1* f7m = new TF1("f7m", "[0]", -0.7, 0.7);
    f7m->FixParameter(0, 1);
    TF1* f7f = new TF1("f7f", "[0]", -0.7, 0.7);
    f7f->FixParameter(0, 1);

    h_tagcsvsdata->Fit(f7, "RN");
    double chi27 = f7->GetChisquare();
    int ndf7 = f7->GetNDF();
    h_tagcsvsdata_scaled->Fit(f7m, "RN");
    double chi27m = f7m->GetChisquare();
    int ndf7m = f7m->GetNDF();

    // Draw the chi2/ndf value on the plot
    tex103->DrawLatex(0.17, 0.85, Form("#chi_{MC}^{2} / NDF = %1.1f / %d", chi27, ndf7));
    tex103->DrawLatex(0.17, 0.78, Form("#chi_{mod.MC}^{2} / NDF = %1.1f / %d", chi27m, ndf7m));

    TLegend *leg107 = tdrLeg(0.62,1.1-0.05*3,0.8,0.8);
    leg107->AddEntry(h_tagcsvsdata, "MC", "PLE");
    leg107->AddEntry(h_tagcsvsdata_scaled, "scaled MC", "PLE");    

    TLatex *tex107 = new TLatex();
    tex107->SetNDC(); tex107->SetTextSize(0.045);
    tex107->DrawLatex(0.17,0.92,"genall,tagcs");

    // Update the canvas to reflect the changes
    gPad->Update();
    gPad->RedrawAxis();

    c100->cd(6);

    gPad->SetLeftMargin(0.13);
    gPad->SetRightMargin(0.01);
    gPad->SetBottomMargin(0.1);
    gPad->SetTopMargin(0);

    TH1D *h_tagudvsdata = (TH1D*)h3tagudall->Clone("h_tagudvsdata");
    h_tagudvsdata->Divide(h3tagudall_data);

    TH1D *h_tagudvsdata_scaled = (TH1D*)h3tagudall_scaled->Clone("h_tagudvsdata_scaled");
    h_tagudvsdata_scaled->Divide(h3tagudall_data);

    tdrDraw(h_tagudvsdata,"Pz",kFullCircle,kAzure+7);
    h_tagudvsdata->SetMarkerSize(1);


    tdrDraw(h_tagudvsdata_scaled,"Pz",kFullCircle,kSpring-5);
    h_tagudvsdata_scaled->SetMarkerSize(1);
    

    h_tagudvsdata->GetYaxis()->SetRangeUser(0, 3.1); // Adjust the range as needed
    h_tagudvsdata->GetYaxis()->SetTitle("MC/DATA");
    h_tagudvsdata->GetXaxis()->SetTitle("(s-c)/(s+c)");
    // Adjust the y-axis title location
    h_tagudvsdata->GetYaxis()->SetTitleOffset(1.5);

    TLine *line106 = new TLine(55, 1, 115, 1);
    line106->SetLineColor(kGray);
    line106->SetLineStyle(kDashed);
    line106->Draw();

    tdrDraw(h_tagudvsdata,"Pz",kFullCircle,kAzure+7);
    h_tagudvsdata->SetMarkerSize(1);

    tdrDraw(h_tagudvsdata_scaled,"Pz",kFullCircle,kSpring-5);
    h_tagudvsdata_scaled->SetMarkerSize(1);

    // Fit the ratio histogram with a constant function
    TF1* f6 = new TF1("f6", "[0]", -0.7, 0.7);
    f6->FixParameter(0, 1);
    TF1* f6m = new TF1("f6m", "[0]", -0.7, 0.7);
    f6m->FixParameter(0, 1);

    h_tagudvsdata->Fit(f6, "RN");
    double chi26 = f6->GetChisquare();
    int ndf6 = f6->GetNDF();
    h_tagudvsdata_scaled->Fit(f6m, "RN");
    double chi26m = f6m->GetChisquare();
    int ndf6m = f6m->GetNDF();


    TLegend *leg106 = tdrLeg(0.62,1.05-0.05*2,0.8,0.85);
    leg106->AddEntry(h_tagudvsdata, "MC", "PLE");
    leg106->AddEntry(h_tagudvsdata_scaled, "scaled MC", "PLE");
    

    TLatex *tex106 = new TLatex();
    tex106->SetNDC(); tex106->SetTextSize(0.045);
    tex106->DrawLatex(0.17,0.92,"genall,tagud");

    // Draw the chi2/ndf value on the plot
    tex106->DrawLatex(0.17, 0.85, Form("#chi_{MC}^{2} / NDF = %1.1f / %d", chi26, ndf6));
    tex106->DrawLatex(0.17, 0.78, Form("#chi_{mod.MC}^{2} / NDF = %1.1f / %d", chi26m, ndf6m));

    // Update the canvas to reflect the changes
    gPad->Update();

    c100->cd(7);

    gPad->SetLeftMargin(0.13);
    gPad->SetRightMargin(0.01);
    gPad->SetBottomMargin(0.1);
    gPad->SetTopMargin(0);

    TH1D *h_tagxvsdata = (TH1D*)h3tagxall->Clone("h_tagxvsdata");
    h_tagxvsdata->Divide(h3tagxall_data);

    TH1D *h_tagxvsdata_scaled = (TH1D*)h3tagxall_scaled->Clone("h_tagxvsdata_scaled");
    h_tagxvsdata_scaled->Divide(h3tagxall_data);

    tdrDraw(h_tagxvsdata,"Pz",kFullCircle,kAzure+7);
    h_tagxvsdata->SetMarkerSize(1);

    tdrDraw(h_tagxvsdata_scaled,"Pz",kFullCircle,kSpring-5);
    h_tagxvsdata_scaled->SetMarkerSize(1);

    h_tagxvsdata->GetYaxis()->SetRangeUser(0, 2.1); // Adjust the range as needed
    h_tagxvsdata->GetYaxis()->SetTitle("MC/DATA");
    h_tagxvsdata->GetXaxis()->SetTitle("(s-c)/(s+c)");
    // Adjust the y-axis title location
    h_tagxvsdata->GetYaxis()->SetTitleOffset(1.5);

    // Add reference line at y = 1
    TLine *line105 = new TLine(55, 1, 115, 1);
    line105->SetLineColor(kGray);
    line105->SetLineStyle(kDashed);
    line105->Draw();

    tdrDraw(h_tagxvsdata,"Pz",kFullCircle,kAzure+7);
    h_tagxvsdata->SetMarkerSize(1);

    tdrDraw(h_tagxvsdata_scaled,"Pz",kFullCircle,kSpring-5);
    h_tagxvsdata_scaled->SetMarkerSize(1);

    // Fit the ratio histogram with a constant function
    TF1* f5 = new TF1("f5", "[0]", -0.7, 0.7);
    f5->FixParameter(0, 1);
    TF1* f5m = new TF1("f5m", "[0]", -0.7, 0.7);
    f5m->FixParameter(0, 1);

    h_tagxvsdata->Fit(f5, "RN");
    double chi25 = f5->GetChisquare();
    int ndf5 = f5->GetNDF();
    h_tagxvsdata_scaled->Fit(f5m, "RN");
    double chi25m = f5m->GetChisquare();
    int ndf5m = f5m->GetNDF();

    TLegend *leg105 = tdrLeg(0.62,1.05-0.05*2,0.8,0.85);
    leg105->AddEntry(h_tagxvsdata, "MC", "PLE");
    leg105->AddEntry(h_tagxvsdata_scaled, "scaled MC", "PLE");
    

    TLatex *tex105 = new TLatex();
    tex105->SetNDC(); tex105->SetTextSize(0.045);
    tex105->DrawLatex(0.17,0.92,"genall,tagx");

    // Draw the chi2/ndf value on the plot
    tex105->DrawLatex(0.17, 0.85, Form("#chi_{MC}^{2} / NDF = %1.1f / %d", chi25, ndf5));
    tex105->DrawLatex(0.17, 0.78, Form("#chi_{mod.MC}^{2} / NDF = %1.1f / %d", chi25m, ndf5m));

    // Update the canvas to reflect the changes
    gPad->Update();


    c100->cd(8);

    gPad->SetLeftMargin(0.13);
    gPad->SetRightMargin(0.01);
    gPad->SetBottomMargin(0.1);
    gPad->SetTopMargin(0);

    TH1D *h_allvsdata = (TH1D*)h3all->Clone("h_allvsdata");
    h_allvsdata->Divide(h3all_data);

    TH1D *h_allvsdata_scaled = (TH1D*)h3all_scaled->Clone("h_allvsdata_scaled");
    h_allvsdata_scaled->Divide(h3all_data);

    tdrDraw(h_allvsdata,"Pz",kFullCircle,kAzure+7);
    h_allvsdata->SetMarkerSize(1);

    tdrDraw(h_allvsdata_scaled,"Pz",kFullCircle,kSpring-5);
    h_allvsdata_scaled->SetMarkerSize(1);

    h_allvsdata->GetYaxis()->SetRangeUser(0, 2.6); // Adjust the range as needed
    h_allvsdata->GetYaxis()->SetTitle("MC/DATA");
    h_allvsdata->GetXaxis()->SetTitle("(s-c)/(s+c)");
    // Adjust the y-axis title location
    h_allvsdata->GetYaxis()->SetTitleOffset(1.5);

    // Add reference line at y = 1
    TLine *line108 = new TLine(55, 1, 115, 1);
    line108->SetLineColor(kGray);
    line108->SetLineStyle(kDashed);
    line108->Draw();

    tdrDraw(h_allvsdata,"Pz",kFullCircle,kAzure+7);
    h_allvsdata->SetMarkerSize(1);


    tdrDraw(h_allvsdata_scaled,"Pz",kFullCircle,kSpring-5);
    h_allvsdata_scaled->SetMarkerSize(1);

    // Fit the ratio histogram with a constant function
    TF1* f8 = new TF1("f8", "[0]", -0.7, 0.7);
    f8->FixParameter(0, 1);
    TF1* f8m = new TF1("f8m", "[0]", -0.7, 0.7);
    f8m->FixParameter(0, 1);

    h_allvsdata->Fit(f8, "RN");
    h_allvsdata_scaled->Fit(f8m, "RN");
    double chi28 = f8->GetChisquare();
    int ndf8 = f8->GetNDF();
    double chi28m = f8m->GetChisquare();
    int ndf8m = f8m->GetNDF();

    // Draw the chi2/ndf value on the plot
    tex103->DrawLatex(0.17, 0.85, Form("#chi_{MC}^{2} / NDF = %1.1f / %d", chi28, ndf8));
    tex103->DrawLatex(0.17, 0.78, Form("#chi_{mod.MC}^{2} / NDF = %1.1f / %d", chi28m, ndf8m));


    TLegend *leg108 = tdrLeg(0.62,1.05-0.05*2,0.8,0.85);
    leg108->AddEntry(h_allvsdata, "MC", "PLE");
    leg108->AddEntry(h_allvsdata_scaled, "scaled MC", "PLE");
    

    TLatex *tex108 = new TLatex();
    tex108->SetNDC(); tex108->SetTextSize(0.045);
    tex108->DrawLatex(0.17,0.92,"all");

    // Update the canvas to reflect the changes
    gPad->Update();



    // Save the canvas as a .pdf file
    c100->SaveAs("pdf/MCvsDATA_Pt_scaled.pdf");

}