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

void CharmvsStrangept() {
    // Open the ROOT file and get the histogram
    TFile *file = new TFile("output_stag3.root", "READ");
    TFile *file2 = new TFile("output_stag_DATA.root", "READ");
    TFile *file3 = new TFile("output_stag_scaledmass2.root", "READ");

    TH1D *h_s = (TH1D*)file->Get("h_s");
    TH1D *h_s_scaled = (TH1D*)file->Get("h_s_scaled");

    TH1D *h_c = (TH1D*)file->Get("h_c");
    TH1D *h_c_scaled = (TH1D*)file->Get("h_c_scaled");

    TH1D *h_s_gen = (TH1D*)file->Get("h_s_gen");
    TH1D *h_s_scaled_gen = (TH1D*)file->Get("h_s_scaled_gen");

    TH1D *h_c_gen = (TH1D*)file->Get("h_c_gen");
    TH1D *h_c_scaled_gen = (TH1D*)file->Get("h_c_scaled_gen");

    TH1D *h_u = (TH1D*)file->Get("h_u");
    TH1D *h_d = (TH1D*)file->Get("h_d");

    TH1D *h_s_data = (TH1D*)file2->Get("h_s");
    TH1D *h_s_scaled_data = (TH1D*)file2->Get("h_s_scaled");

    TH1D *h_c_data = (TH1D*)file2->Get("h_c");
    TH1D *h_c_scaled_data = (TH1D*)file2->Get("h_c_scaled");

    h_s->Scale(1.0/h_s->Integral(), "width");
    h_s_scaled->Scale(1.0/h_s_scaled->Integral(), "width");
    h_c->Scale(1.0/h_c->Integral(), "width");
    h_c_scaled->Scale(1.0/h_c_scaled->Integral(), "width");

    h_u->Scale(1.0/h_u->Integral(), "width");
    h_d->Scale(1.0/h_d->Integral(), "width");

    h_s_gen->Scale(1.0/h_s_gen->Integral(), "width");
    h_s_scaled_gen->Scale(1.0/h_s_scaled_gen->Integral(), "width");
    h_c_gen->Scale(1.0/h_c_gen->Integral(), "width");
    h_c_scaled_gen->Scale(1.0/h_c_scaled_gen->Integral(), "width");

    h_s_data->Scale(1.0/h_s_data->Integral(), "width");
    h_s_scaled_data->Scale(1.0/h_s_scaled_data->Integral(), "width");
    h_c_data->Scale(1.0/h_c_data->Integral(), "width");
    h_c_scaled_data->Scale(1.0/h_c_scaled_data->Integral(), "width");

    setTDRStyle();
    lumi_136TeV = "Run3 simulation";
    extraText = "Private";
    TH1D *h1 = tdrHist("h1","N fraction",0,0.04,"p_{T} (GeV)",25,200);
    TCanvas *c1 = tdrCanvas("c1",h1,8,11,kSquare);
    h1->GetYaxis()->SetTitleOffset(1.65);
    h1->GetYaxis()->SetTitleSize(0.05);
    h1->GetXaxis()->SetTitleSize(0.05);
    h1->GetYaxis()->SetLabelSize(0.045);
    h1->GetXaxis()->SetLabelSize(0.045);
    
    //gPad->SetLogy();
    //c1->SetLogx();

    // Draw the histogram
    tdrDraw(h_s,"Pz",kFullCircle,kOrange-3);
    h_s->SetMarkerSize(0.7);
    tdrDraw(h_s_scaled,"Pz",kFullDiamond,kPink-9);
    h_s_scaled->SetMarkerSize(0.9);
    tdrDraw(h_c,"Pz",kFullCircle,kSpring-5);
    h_c->SetMarkerSize(0.7);
    tdrDraw(h_c_scaled,"Pz",kFullDiamond,kAzure+7);
    h_c_scaled->SetMarkerSize(0.9);

    tdrDraw(h_s_gen,"Pz",kOpenCircle,kOrange-3);
    h_s_gen->SetMarkerSize(0.7);
    //tdrDraw(h_s_scaled_gen,"Pz",kOpenDiamond,kPink-9);
    //h_s_scaled_gen->SetMarkerSize(0.9);
    tdrDraw(h_c_gen,"Pz",kOpenCircle,kSpring-5);
    h_c_gen->SetMarkerSize(0.7);
    //tdrDraw(h_c_scaled_gen,"Pz",kOpenDiamond,kAzure+7)
    //h_c_scaled_gen->SetMarkerSize(0.9);

    tdrDraw(h_u,"Pz",kOpenCircle,kGray+1);
    h_u->SetMarkerSize(0.7);
    tdrDraw(h_d,"Pz",kOpenCircle,kBlack);
    h_d->SetMarkerSize(0.7);

    tdrDraw(h_s_data,"Pz",kFullCircle,kOrange-2);
    h_s_data->SetMarkerSize(0.8);
    tdrDraw(h_s_scaled_data,"Pz",kFullDiamond,kPink-8);
    h_s_scaled_data->SetMarkerSize(1);
    tdrDraw(h_c_data,"Pz",kFullCircle,kSpring-4);
    h_c_data->SetMarkerSize(0.8);
    tdrDraw(h_c_scaled_data,"Pz",kFullDiamond,kAzure+6);
    h_c_scaled_data->SetMarkerSize(1);



    // Create a legend
    TLegend *leg = tdrLeg(0.5,1.05-0.05*13,0.7,0.82);
    leg->AddEntry(h_s_gen, "s, gen, MC", "PLE");
    leg->AddEntry(h_s, "s, tag, MC", "PLE");
    leg->AddEntry(h_s_scaled, "scaled s, tag, MC", "PLE");
    leg->AddEntry(h_s_data, "s, data", "PLE");
    leg->AddEntry(h_s_scaled_data, "scaled s, data", "PLE");
    leg->AddEntry(h_c_gen, "c, gen, MC", "PLE");
    leg->AddEntry(h_c, "c, tag, MC", "PLE");
    leg->AddEntry(h_c_scaled, "scaled c, tag, MC", "PLE");
    leg->AddEntry(h_c_data, "c, data", "PLE");
    leg->AddEntry(h_c_scaled_data, "scaled c, data", "PLE");

    leg->AddEntry(h_u, "u, gen, MC", "PLE");
    leg->AddEntry(h_d, "d, gen, MC", "PLE");
    leg->SetTextSize(0.035);

    //leg->Draw();

    // Update the canvas to reflect the changes
    TLatex *tex1 = new TLatex();
    tex1->SetNDC(); tex1->SetTextSize(0.045); 

    //c1->SetLeftMargin(0.165);
    gPad->RedrawAxis();
    gPad->Update();

    // Save the canvas as a .pdf file
    c1->SaveAs("pdf/charmvsstrangept2.pdf");

    TH1D *h_s_vs_c = (TH1D*)file->Get("h_s_vs_c");
    TH1D *h2 = tdrHist("h2","s-c/s+c",-0.15,0.1,"p_{T} (GeV)",25,200);
    TCanvas *c2 = tdrCanvas("c2",h2,8,11,kSquare);

    h2->GetYaxis()->SetTitleOffset(1.65);
    h2->GetYaxis()->SetTitleSize(0.05);
    h2->GetXaxis()->SetTitleSize(0.05);
    h2->GetYaxis()->SetLabelSize(0.045);
    h2->GetXaxis()->SetLabelSize(0.045);

    tdrDraw(h_s_vs_c,"Pz",kFullCircle,kAzure+7);
    h_s_vs_c->SetMarkerSize(0.8);
    double mean = h_s_vs_c->GetMean();

    TLegend *leg2 = tdrLeg(0.5,0.85-0.05*1,0.7,0.7);
    leg2->AddEntry(h_s_vs_c, Form("#splitline{s vs c, tag, MC}{Mean = %.2f}",mean), "PLE");

    gPad->RedrawAxis();
    gPad->Update();

    // Save the canvas as a .pdf file
    c2->SaveAs("pdf/cvssprofile2.pdf");


    TH1D *hPtFlavorPairs_DATAMC = (TH1D*)file3->Get("hPtFlavorPairs_DATAMC_0.995_1.015");
    TH1D *h3 = tdrHist("h3","N",0.1,3000,"(s-c)/(s+c)",-1,1);
    TCanvas *c3 = tdrCanvas("c3",h3,8,11,kSquare);

    h3->GetYaxis()->SetTitleOffset(1.65);
    h3->GetYaxis()->SetTitleSize(0.05);
    h3->GetXaxis()->SetTitleSize(0.05);
    h3->GetYaxis()->SetLabelSize(0.045);
    h3->GetXaxis()->SetLabelSize(0.045);
    //c3->SetLogy();

    tdrDraw(hPtFlavorPairs_DATAMC,"HPz",kNone,kAzure+7,kSolid,-1,1001,kAzure+7);
    hPtFlavorPairs_DATAMC->SetFillColorAlpha(kAzure+7,0.25);

    double RMS = hPtFlavorPairs_DATAMC->GetRMS();

    TLegend *leg3 = tdrLeg(0.65,0.9-0.05*1,0.8,0.75);
    leg3->AddEntry(hPtFlavorPairs_DATAMC, Form("RMS = %.3f", RMS),"PLE");

    gPad->RedrawAxis();
    gPad->Update();

    // Save the canvas as a .pdf file
    c3->SaveAs("pdf/s-cprofile2.pdf");


    TH1D *hMassFlavorPairs_DATAMC = (TH1D*)file3->Get("hMassFlavorPairs_DATAMC_0.995_1.015");
    TH1D *h4 = tdrHist("h4","N",0,3000,"Mass (GeV)",55,120);
    TCanvas *c4 = tdrCanvas("c4",h4,8,11,kSquare);

    h4->GetYaxis()->SetTitleOffset(1.65);
    h4->GetYaxis()->SetTitleSize(0.05);
    h4->GetXaxis()->SetTitleSize(0.05);
    h4->GetYaxis()->SetLabelSize(0.045);
    h4->GetXaxis()->SetLabelSize(0.045);
    //c3->SetLogy();

    tdrDraw(hMassFlavorPairs_DATAMC,"HPz",kNone,kAzure+7,kSolid,-1,1001,kAzure+7);
    hMassFlavorPairs_DATAMC->SetFillColorAlpha(kAzure+7,0.25);

    double RMS2 = hMassFlavorPairs_DATAMC->GetRMS();

    TLegend *leg4 = tdrLeg(0.65,0.9-0.05*1,0.8,0.75);
    leg4->AddEntry(hMassFlavorPairs_DATAMC, Form("RMS = %.3f", RMS2),"PLE");

    gPad->RedrawAxis();
    gPad->Update();

    // Save the canvas as a .pdf file
    c4->SaveAs("pdf/Mass_profile2.pdf");
}