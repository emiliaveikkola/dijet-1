#include <TH1.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include <TList.h>
#include "tdrstyle_mod22.C"

void energyfraction_test() {
    // Open the ROOT file containing the histograms
    TFile *file = new TFile("output_z2.root", "READ");

    setTDRStyle();
    lumi_136TeV = "Run3";
    extraText = "Private";

    // Set up the canvas
   TH1D *h = tdrHist("h","Down energy fraction",0,1,"p_{T} (GeV)",10, 5200);
   TCanvas *c = tdrCanvas("c",h,8,11,kSquare);
    c->SetLogx();
    h->GetXaxis()->SetLabelSize(0.04);
    h->GetYaxis()->SetLabelSize(0.04);
    h->GetXaxis()->SetTitleSize(0.045);
    h->GetXaxis()->SetTitleOffset(1.2);
    h->GetYaxis()->SetTitleSize(0.045);

    // Retrieve histograms from the file
    TH1D *h_hadron_nh = (TH1D*)file->Get("h_all_d_fhnh_vs_ptjet");
    TH1D *h_leading_nh = (TH1D*)file->Get("h_all_d_flnh_vs_ptjet");

    TH1D *h_hadron_ne = (TH1D*)file->Get("h_all_d_fhne_vs_ptjet");
    TH1D *h_leading_ne = (TH1D*)file->Get("h_all_d_flne_vs_ptjet");

    TH1D *h_hadron_ch = (TH1D*)file->Get("h_all_d_fhch_vs_ptjet");
    TH1D *h_leading_ch = (TH1D*)file->Get("h_all_d_flch_vs_ptjet");



    tdrDraw(h_hadron_ch,"histe", kFullSquare, kRed, kSolid,-1,kNone);
    tdrDraw(h_leading_ch,"histe", kOpenSquare, kRed+3, kSolid,-1,kNone);

    tdrDraw(h_hadron_nh,"histe", kFullCircle, kGreen+2, kSolid,-1,kNone);
    tdrDraw(h_leading_nh,"histe", kOpenCircle, kGreen+3, kSolid,-1,kNone);

    tdrDraw(h_hadron_ne,"histe", kFullDiamond, kBlue, kSolid,-1,kNone);
    tdrDraw(h_leading_ne,"histe", kOpenDiamond, kBlue+2, kSolid,-1,kNone);
    h_hadron_ne->SetMarkerSize(1.25);
    h_leading_ne->SetMarkerSize(1.25);

    // Add a legend
    TLegend *leg = tdrLeg(0.67,0.9-0.035*6,0.85,0.91);
    leg->AddEntry(h_hadron_ne, " #gamma", "ple");
    leg->AddEntry(h_hadron_ch, "CH", "ple");
    leg->AddEntry(h_hadron_nh, "NH", "ple");

    leg->AddEntry(h_leading_ne, "Leading #gamma", "ple");
    leg->AddEntry(h_leading_ch, "Leading CH", "ple");
    leg->AddEntry(h_leading_nh, "Leading NH", "ple");
    leg->SetTextSize(0.03);
    leg->Draw();

    // Add labels
    TLatex *tex1 = new TLatex();
    tex1->SetNDC();
    tex1->SetTextSize(0.04);
    tex1->DrawLatex(0.19, 0.75, "|#eta| < 1.3");

    // Update and save the canvas
    c->RedrawAxis();
    c->Modified();
    c->Update();
    c->SaveAs("energy_and_leading_fraction3.pdf");

    // Clean up
    delete c;
    file->Close();
    delete file;
}