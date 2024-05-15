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

void MCvsDATA_mass() {
    TFile *file = new TFile("output_stag3.root", "READ");
    TH3D* h3MassFlavorPairs_DATAMC = (TH3D*)file->Get("h3MassFlavorPairs_DATAMC");
      // Project Z for different indices and draw
      TH1D* h3 = h3MassFlavorPairs_DATAMC->ProjectionZ("h3", 1, 3, 1, 1);
      TH1D* h3x = h3MassFlavorPairs_DATAMC->ProjectionZ("h3x", 3, 3, 1, 1);
      TH1D* h3cs = h3MassFlavorPairs_DATAMC->ProjectionZ("h3cs", 1, 1, 1, 1);
      TH1D* h3ud = h3MassFlavorPairs_DATAMC->ProjectionZ("h3ud", 2, 2, 1, 1);

      TH1D* h3data = h3MassFlavorPairs_DATAMC->ProjectionZ("h3data", 1, 1, 1, 3);

      TH1D* h3xdata = h3MassFlavorPairs_DATAMC->ProjectionZ("h3xdata", 1, 1, 3, 3);

      TH1D* h3corr = new TH1D("h3corr",";Mass;N",200,0,200);

      TH1D* h3corrdata = new TH1D("h3corrdata",";Mass;N",200,0,200);


    h3->Scale(1./h3->Integral());
    h3x->Scale(1./h3x->Integral());
    h3cs->Scale(1./h3cs->Integral());
    h3ud->Scale(1./h3ud->Integral());
    h3data->Scale(1./h3data->Integral());
    h3xdata->Scale(1./h3xdata->Integral());


    h3corr->Add(h3,h3x,1,-1);

    h3corrdata->Add(h3data,h3xdata,1,-1);

    TH1D *h3div = (TH1D*)h3data->Clone("h3div");
    h3div->Divide(h3);

    TH1D *h3divcorr = (TH1D*)h3corrdata->Clone("h3divcorr");
    h3divcorr->Divide(h3corr);

      
    lumi_136TeV = "Run3 simulation";
    extraText = "Private";
    //TH1D *h1 = tdrHist("h1","N",0,0.05,"Mass (GeV)",0,200);
    //TCanvas *c1 = tdrCanvas("c1",h1,8,11,kSquare);
      
    TH1D *h1 = tdrHist("h1","N fraction",0,0.06-7e-3,"Mass (GeV)",50+1e-1,140);
    TCanvas *c1 = tdrCanvas("c1",h1,8,kSquare);

    TH1D *h2 = tdrHist("h2","Data/MC",-0.5,2.5,"Mass (GeV)",50+1e-1,140);
    TCanvas *c2 = tdrCanvas("c2",h2,8,kSquare);

    TCanvas *c = tdrDiCanvas("c",h1,h2,8,11);

    c->cd(1);

    h1->GetYaxis()->SetTitleOffset(1.2);
    h1->GetYaxis()->SetTitleSize(0.065);

    // Draw the histogram
    tdrDraw(h3,"HPz",kNone,kAzure+7,kSolid,-1,1001,kAzure+7);
    h3->SetFillColorAlpha(kAzure+7,0.25);

    tdrDraw(h3corr,"HPz",kNone,kSpring-5,kSolid,-1,1001,kSpring-5);
    h3corr->SetFillColorAlpha(kSpring-5,0.25);

    tdrDraw(h3corrdata,"Pz",kFullCircle,kViolet+5);
    h3corrdata->SetMarkerSize(0.7);

    //tdrDraw(h3cs,"HPz",kNone,kAzure+7,kSolid,-1,1001,kAzure+7);
    //h3cs->SetFillColorAlpha(kAzure+7,0.25);

    //tdrDraw(h3ud,"HPz",kNone,kAzure+7,kSolid,-1,1001,kAzure+7);
    //h3ud->SetFillColorAlpha(kAzure+7,0.25);

    tdrDraw(h3data,"Pz",kFullCircle,kPink-9);
    h3data->SetMarkerSize(0.8);

    // Create a legend
    TLegend *leg = tdrLeg(0.7,0.8-0.05*4,0.9,0.82);
    leg->AddEntry(h3, "MC", "FPLE");
    leg->AddEntry(h3data, "Data", "PLE");
    leg->AddEntry(h3corr, "MC-X", "FPLE");
    leg->AddEntry(h3corrdata, "Data-X", "PLE");
    //leg->AddEntry(h3x, "x", "FPLE");
    
    //leg->Draw();

    // Update the canvas to reflect the changes
    TLatex *tex1 = new TLatex();
    tex1->SetNDC(); tex1->SetTextSize(0.045); 

    // Update the canvas to reflect the changes
    gPad->Update();

    c->cd(2);

    tdrDraw(h3div,"Pz",kFullCircle,kPink-9);
    h3div->SetMarkerSize(0.8);

    tdrDraw(h3divcorr,"Pz",kFullCircle,kViolet+5);
    h3divcorr->SetMarkerSize(0.8);

    gPad->Update();


    // Save the canvas as a .pdf file
    c->SaveAs("pdf/MCvsDATA_Mass.pdf");
}