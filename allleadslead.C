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
    setTDRStyle();
    // Open the ROOT file and get the histogram
    TFile *file = new TFile("output_z.root", "READ");

    TH1D *h_all = (TH1D*)file->Get("h_all");
    TH1D *h_all_s = (TH1D*)file->Get("h_all_s");
    TH1D *h_all_ud = (TH1D*)file->Get("h_all_ud");

    TH1D *h_s = (TH1D*)file->Get("h_s");
    TH1D *h_s_s = (TH1D*)file->Get("h_s_s");
    TH1D *h_s_ud = (TH1D*)file->Get("h_s_ud");

    TH1D *h_ud = (TH1D*)file->Get("h_ud");
    TH1D *h_ud_s = (TH1D*)file->Get("h_ud_s");
    TH1D *h_ud_ud = (TH1D*)file->Get("h_ud_ud");
    
    TH1D *h_g = (TH1D*)file->Get("h_g");
    TH1D *h_g_s = (TH1D*)file->Get("h_g_s");
    TH1D *h_g_ud = (TH1D*)file->Get("h_g_ud");

    TH1D *h_all_lead = (TH1D*)file->Get("h_all_lead");
    TH1D *h_all_slead = (TH1D*)file->Get("h_all_slead");
    TH1D *h_all_udlead = (TH1D*)file->Get("h_all_udlead");

    TH1D *h_all_lead_is_slead = (TH1D*)file->Get("h_all_lead_is_slead");
    //TH1D *h_all_lead_is_udlead = (TH1D*)file->Get("h_all_lead_is_udlead");

    TH1D *h_s_lead = (TH1D*)file->Get("h_s_lead");
    TH1D *h_s_slead = (TH1D*)file->Get("h_s_slead");
    TH1D *h_s_udlead = (TH1D*)file->Get("h_s_udlead");

    TH1D *h_s_lead_is_slead = (TH1D*)file->Get("h_s_lead_is_slead");
    TH1D *h_s_lead_is_udlead = (TH1D*)file->Get("h_s_lead_is_udlead");


    
    TH1D *h_ud_lead = (TH1D*)file->Get("h_ud_lead");
    TH1D *h_ud_slead = (TH1D*)file->Get("h_ud_slead");
    TH1D *h_ud_udlead = (TH1D*)file->Get("h_ud_udlead");

    TH1D *h_g_lead = (TH1D*)file->Get("h_g_lead");
    TH1D *h_g_slead = (TH1D*)file->Get("h_g_slead");
    TH1D *h_g_udlead = (TH1D*)file->Get("h_g_udlead");

    
    lumi_136TeV = "Run3 simulation";
    extraText = "Private";
    TH1D *h1 = tdrHist("h1","All jets N",0 + 1e-2,1000,"p_{T,cand} (GeV)",0.1,100);
    TCanvas *c1 = tdrCanvas("c1",h1,8,11,kSquare);
    gPad->SetLogy();
    //c1->SetLogx();

    // Draw the histogram
    tdrDraw(h_all,"HPz",kNone,kOrange-2,kSolid,-1,1001,kOrange-2);
    h_all->SetFillColorAlpha(kOrange-2,0.25);

    tdrDraw(h_all_ud,"HPz",kNone,kOrange+10,kSolid,-1,1001,kOrange+10);
    h_all_ud->SetFillColorAlpha(kOrange+10,0.25);

    tdrDraw(h_all_s,"HPz",kNone,kPink-9,kSolid,-1,1001,kPink-9);
    h_all_s->SetFillColorAlpha(kPink-9,0.25);

    tdrDraw(h_all_lead,"Pz",kFullCircle,kGreen-3);
    h_all_lead->SetMarkerSize(1.5);

    tdrDraw(h_all_udlead,"Pz",kFullSquare,kBlue-9);
    h_all_udlead->SetMarkerSize(1.35);

    tdrDraw(h_all_slead,"Pz",kFullDiamond,kViolet+1);
    h_all_slead->SetMarkerSize(1.75);

    // Create a legend
    TLegend *leg = tdrLeg(0.5,0.8-0.05*6,0.7,0.87);
    leg->AddEntry(h_all, "all-jets, all-ptcl", "FPLE");
    leg->AddEntry(h_all_ud, "all-jets, ud-ptcl", "FPLE");
    leg->AddEntry(h_all_s, "all-jets, s-ptcl", "FPLE");
    leg->AddEntry(h_all_lead, "all-jets, lead-ptcl, all-ptcl", "PLE");
    leg->AddEntry(h_all_udlead, "all-jets, lead of ud-ptcl", "PLE");
    leg->AddEntry(h_all_slead, "all-jets, lead of s-ptcl", "PLE");
    
    leg->Draw();

    // Update the canvas to reflect the changes
    gPad->Update();

    // Save the canvas as a .pdf file
    c1->SaveAs("pdf/alljetslead.pdf");

    TH1D *h2 = tdrHist("h2","S jets N",0 + 1e-2,50,"p_{T,cand} (GeV)",0.1,100);
    TCanvas *c2 = tdrCanvas("c2",h2,8,11,kSquare);
    c2->SetLogy();
    //c1->SetLogx();

    // Draw the histogram
    tdrDraw(h_s,"HPz",kNone,kOrange-2,kSolid,-1,1001,kOrange-2);
    h_s->SetFillColorAlpha(kOrange-2,0.25);

    tdrDraw(h_s_ud,"HPz",kNone,kOrange+10,kSolid,-1,1001,kOrange+10);
    h_s_ud->SetFillColorAlpha(kOrange+10,0.25);

    tdrDraw(h_s_s,"HPz",kNone,kPink-9,kSolid,-1,1001,kPink-9);
    h_s_s->SetFillColorAlpha(kPink-9,0.25);

    tdrDraw(h_s_lead,"Pz",kFullCircle,kGreen-3);
    h_s_lead->SetMarkerSize(1.5);

    tdrDraw(h_s_udlead,"Pz",kFullSquare,kBlue-9);
    h_s_udlead->SetMarkerSize(1.35);

    tdrDraw(h_s_slead,"Pz",kFullDiamond,kViolet+1);
    h_s_slead->SetMarkerSize(1.75);

    // Create a legend
    TLegend *leg2 = tdrLeg(0.5,0.8-0.05*6,0.7,0.87);
    leg2->AddEntry(h_s, "s-jets, all-ptcl", "FPLE");
    leg2->AddEntry(h_s_ud, "s-jets, ud-ptcl", "FPLE");
    leg2->AddEntry(h_s_s, "s-jets, s-ptcl", "FPLE");
    leg2->AddEntry(h_s_lead, "s-jets, lead-ptcl, all-ptcl", "PLE");
    leg2->AddEntry(h_s_udlead, "s-jets, lead of ud-ptcl", "PLE");
    leg2->AddEntry(h_s_slead, "s-jets, lead of s-ptcl", "PLE");
    
    leg2->Draw();

    // Update the canvas to reflect the changes
    c2->Update();

    // Save the canvas as a .pdf file
    c2->SaveAs("pdf/sjetslead.pdf");

    TH1D *h3 = tdrHist("h3","UD jets N",0 + 1e-2,100,"p_{T,cand} (GeV)",0.1,100);
    TCanvas *c3 = tdrCanvas("c3",h3,8,11,kSquare);
    c3->SetLogy();
    //c1->SetLogx();

    // Draw the histogram
    tdrDraw(h_ud,"HPz",kNone,kOrange-2,kSolid,-1,1001,kOrange-2);
    h_ud->SetFillColorAlpha(kOrange-2,0.25);

    tdrDraw(h_ud_ud,"HPz",kNone,kOrange+10,kSolid,-1,1001,kOrange+10);
    h_ud_ud->SetFillColorAlpha(kOrange+10,0.25);

    tdrDraw(h_ud_s,"HPz",kNone,kPink-9,kSolid,-1,1001,kPink-9);
    h_ud_s->SetFillColorAlpha(kPink-9,0.25);

    tdrDraw(h_ud_lead,"Pz",kFullCircle,kGreen-3);
    h_ud_lead->SetMarkerSize(1.5);

    tdrDraw(h_ud_udlead,"Pz",kFullSquare,kBlue-9);
    h_ud_udlead->SetMarkerSize(1.35);

    tdrDraw(h_ud_slead,"Pz",kFullDiamond,kViolet+1);
    h_ud_slead->SetMarkerSize(1.75);

    // Create a legend
    TLegend *leg3 = tdrLeg(0.5,0.8-0.05*6,0.7,0.87);
    leg3->AddEntry(h_ud, "ud-jets, all-ptcl", "FPLE");
    leg3->AddEntry(h_ud_ud, "ud-jets, ud-ptcl", "FPLE");
    leg3->AddEntry(h_ud_s, "ud-jets, s-ptcl", "FPLE");
    leg3->AddEntry(h_ud_lead, "ud-jets, lead-ptcl, all-ptcl", "PLE");
    leg3->AddEntry(h_ud_udlead, "ud-jets, lead of ud-ptcl", "PLE");
    leg3->AddEntry(h_ud_slead, "ud-jets, lead of s-ptcl", "PLE");
    
    leg3->Draw();

    // Update the canvas to reflect the changes
    c3->Update();

    // Save the canvas as a .pdf file
    c3->SaveAs("pdf/udjetslead.pdf");

    TH1D *h4 = tdrHist("h4","G jets N",0 + 1e-2,1000,"p_{T,cand} (GeV)",0.1,100);
    TCanvas *c4 = tdrCanvas("c4",h4,8,11,kSquare);
    c4->SetLogy();
    //c1->SetLogx();

    // Draw the histogram
    tdrDraw(h_g,"HPz",kNone,kOrange-2,kSolid,-1,1001,kOrange-2);
    h_g->SetFillColorAlpha(kOrange-2,0.25);

    tdrDraw(h_g_ud,"HPz",kNone,kOrange+10,kSolid,-1,1001,kOrange+10);
    h_g_ud->SetFillColorAlpha(kOrange+10,0.25);

    tdrDraw(h_g_s,"HPz",kNone,kPink-9,kSolid,-1,1001,kPink-9);
    h_g_s->SetFillColorAlpha(kPink-9,0.25);

    tdrDraw(h_g_lead,"Pz",kFullCircle,kGreen-3);
    h_g_lead->SetMarkerSize(1.5);

    tdrDraw(h_g_slead,"Pz",kFullDiamond,kViolet+1);
    h_g_slead->SetMarkerSize(1.75);

    tdrDraw(h_g_udlead,"Pz",kFullSquare,kBlue-9);
    h_g_udlead->SetMarkerSize(1.35);

    // Create a legend
    TLegend *leg4 = tdrLeg(0.5,0.8-0.05*6,0.7,0.87);
    leg4->AddEntry(h_g, "g-jets, all-ptcl", "FPLE");
    leg4->AddEntry(h_g_ud, "g-jets, ud-ptcl", "FPLE");
    leg4->AddEntry(h_g_s, "g-jets, s-ptcl", "FPLE");
    leg4->AddEntry(h_g_lead, "g-jets, lead-ptcl, all-ptcl", "PLE");
    leg4->AddEntry(h_g_udlead, "g-jets, lead of ud-ptcl", "PLE");
    leg4->AddEntry(h_g_slead, "g-jets, lead of s-ptcl", "PLE");
    
    leg4->Draw();

    // Update the canvas to reflect the changes
    c4->Update();

    // Save the canvas as a .pdf file
    c4->SaveAs("pdf/gjetslead.pdf");

    TH1D *h6 = tdrHist("h6","N_{cand} #times MC weight",0.0005 + 1e-5,2000,"p_{T,cand} (GeV)",0.1,100);
    TCanvas *c6 = tdrCanvas("c6",h6,8,11,kSquare);
    gPad->SetLogy();
    //c6->SetLogx();
  
    // Draw the histogram
    tdrDraw(h_all,"HPz",kNone,kOrange-2,kSolid,-1,1001,kOrange-2);
    h_all->SetFillColorAlpha(kOrange-2,0.25);

    tdrDraw(h_s,"HPz",kNone,kOrange+1,kSolid,-1,1001,kOrange+1);
    h_s->SetFillColorAlpha(kOrange+1,0.25);

    tdrDraw(h_all_lead,"Pz",kOpenSquare,kOrange+10);
    h_all_lead->SetMarkerSize(0.7);

    tdrDraw(h_all_slead,"Pz",kOpenCircle,kViolet+7);
    h_all_slead->SetMarkerSize(0.7);

    tdrDraw(h_all_lead_is_slead,"Pz",kOpenDiamond,kGreen+1);
    h_all_lead_is_slead->SetMarkerSize(0.81);

    //tdrDraw(h_s_lead_is_slead,"Pz",kFullDiamond,kViolet);
    //h_s_lead_is_slead->SetMarkerSize(1.75);

    tdrDraw(h_s_lead,"Pz",kFullSquare,kOrange+10);
    h_s_lead->SetMarkerSize(0.7);

    tdrDraw(h_s_slead,"Pz",kFullCircle,kViolet+7);
    h_s_slead->SetMarkerSize(0.7);

    tdrDraw(h_s_lead_is_slead,"Pz",kFullDiamond,kGreen+1);
    h_s_lead_is_slead->SetMarkerSize(0.81);

 



    // Create a legend
    TLegend *leg6 = tdrLeg(0.65,0.8-0.05*6,0.8,0.87);
    leg6->AddEntry(h_all, "all jets, all", "FPLE");
    leg6->AddEntry(h_all_lead, "all jets, lead", "PLE");
    leg6->AddEntry(h_all_slead, "all jets, lead s", "PLE");
    //leg6->AddEntry(h_all_lead_is_udlead, "all jets, leading ptcl is ud-ptcl", "PLE");
    leg6->AddEntry(h_all_lead_is_slead, "all jets, lead is s", "PLE");
    leg6->AddEntry(h_s, "s jets, all", "FPLE");
    leg6->AddEntry(h_s_lead, "s jets, lead", "PLE");
    leg6->AddEntry(h_s_slead, "s jets, lead s", "PLE");
    //leg6->AddEntry(h_s_lead_is_udlead, "s jets, leading ptcl is ud-ptcl", "PLE");
    leg6->AddEntry(h_s_lead_is_slead, "s jets, lead is s", "PLE");
    leg6->SetTextSize(0.035);
 
    leg6->Draw();

    TLatex *tex1 = new TLatex();
    tex1->SetNDC(); tex1->SetTextSize(0.035);
    tex1->DrawLatex(0.32,0.84,"|#eta| < 1.3");  
    tex1->DrawLatex(0.32,0.8,"80 < p_{T,genjet} < 100 GeV");
    

    // Update the canvas to reflect the changes
    gPad->Update();

    gPad->RedrawAxis();

    // Save the canvas as a .pdf file
    c6->SaveAs("pdf/slead.pdf");






    TH1D *h5 = tdrHist("h5","N_{cand} fraction, lead is s", 0.05,1.8,"p_{T,cand} (GeV)",0.1,100);
    TCanvas *c5 = tdrCanvas("c5",h5,8,11,kSquare);
    //c5->SetLogy();
    TGaxis::SetMaxDigits(10);

    TH1D *hc_all_lead_is_slead = (TH1D*)h_all_lead_is_slead->Clone("hc_all_lead_is_slead");
    hc_all_lead_is_slead->Divide(h_all_lead);

    TH1D *hc_s_lead_is_slead = (TH1D*)h_s_lead_is_slead->Clone("hc_s_lead_is_slead");
    hc_s_lead_is_slead->Divide(h_s_lead);

    //TH1D *hc_all_udlead = (TH1D*)h_all_udlead->Clone("hc_all_udlead");
    //hc_all_udlead->Divide(h_all_lead);

    //TH1D *hc_ud_lead = (TH1D*)h_ud_lead->Clone("hc_ud_lead");
    //hc_ud_lead->Divide(h_all_lead);

    tdrDraw(hc_all_lead_is_slead,"Pz",kFullCircle,kViolet+7);
    hc_all_lead_is_slead->SetMarkerSize(1.25);

    tdrDraw(hc_s_lead_is_slead,"Pz",kFullDiamond,kGreen+1);
    hc_s_lead_is_slead->SetMarkerSize(1.5);

    //tdrDraw(hc_ud_lead,"Pz",kOpenCircle,kBlue);
    //hc_ud_lead->SetMarkerSize(1.5);

    //tdrDraw(hc_all_udlead,"Pz",kOpenDiamond,kOrange+10);
    //hc_all_udlead->SetMarkerSize(1.75);

    TLegend *leg5 = tdrLeg(0.5,0.85-0.05*2,0.6,0.9);
    //leg5->AddEntry(hc_all_udlead, "Highest pt ud/all lead", "ple");

    //leg5->AddEntry(hc_ud_lead, "Leading ud/all lead", "ple");
    leg5->AddEntry(hc_s_lead_is_slead, "Strange jets", "ple");
    leg5->AddEntry(hc_all_lead_is_slead, "All jets", "ple");
    leg5->SetTextSize(0.035);
    
    leg5->Draw();
    // Update the canvas to reflect the changes
    TLatex *tex2 = new TLatex();
    tex2->SetNDC(); tex2->SetTextSize(0.035);
    tex2->DrawLatex(0.19,0.76,"|#eta| < 1.3");  
    tex2->DrawLatex(0.19,0.72,"80 < p_{T,genjet} < 100 GeV");
    c5->Update();

    // Save the canvas as a .pdf file
    c5->SaveAs("pdf/allvssleadratio.pdf");
}