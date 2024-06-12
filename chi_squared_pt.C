#include <TMath.h>
#include <TF1.h>
#include <TH1F.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TProfile2D.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include <TStyle.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <sstream>
#include <TGraphErrors.h>
#include <TLatex.h>
#include "tdrstyle_mod22.C"

void chi_squared_pt() {
    setTDRStyle();

    // Open the output files
    TFile *file = new TFile("output_stag_scaledmass2.root", "READ");
    TFile *file2 = new TFile("output_stag_DATA2.root", "READ");

    std::vector<double> scaleFactors;
    for (double scale = 0.95; scale <= 1.05; scale += 0.005) {
        scaleFactors.push_back(scale);
    }

    // Create a TH2D histogram to store chi-squared values
    int nBins = scaleFactors.size();
    double dx = 0.005/2;
    TH2D* chi2_hist2 = new TH2D("chi2_hist2", ";R_{c};R_{s};#chi^{2}",
                               nBins, 0.95-dx, 1.05+dx, nBins, 0.95-dx, 1.05+dx);


TH1D *h_tagcsvsdata_scaled_00(0), *h_tagcsvsdata_scaled_11(0), *h_tagcsvsdata_scaled_22(0);
    for (size_t i = 0; i < scaleFactors.size(); ++i) {
        for (size_t j = 0; j < scaleFactors.size(); ++j) {
            double scale1 = scaleFactors[i];
            double scale2 = scaleFactors[j];
            
            // Format the histogram name with 4 decimal places
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(3) << scale1 << "_" << scale2;
            std::string histName = "h3PtFlavorPairs_DATAMC_" + oss.str();

            // Retrieve the histogram
            TH3D* h3PtFlavorPairs_DATAMC_MC = (TH3D*)file->Get(histName.c_str());
            if (!h3PtFlavorPairs_DATAMC_MC) {
                std::cerr << "Histogram " << histName << " not found!" << std::endl;
                continue;
            }
            h3PtFlavorPairs_DATAMC_MC = (TH3D*)h3PtFlavorPairs_DATAMC_MC->Clone(Form("file1_%d_%d",(int)i,(int)j));

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

    
        TH3D* h3PtFlavorPairs_DATAMC_DATA = (TH3D*)file2->Get("h3PtFlavorPairs_DATAMC");
        h3PtFlavorPairs_DATAMC_DATA = (TH3D*)h3PtFlavorPairs_DATAMC_DATA->Clone(Form("file2_%d_%d",0,0));


        TH1D* h3all_data = h3PtFlavorPairs_DATAMC_DATA->ProjectionZ("h3all_data", 1, 3, 1, 3);

        TH1D* h3tagcsall_data = h3PtFlavorPairs_DATAMC_DATA->ProjectionZ("h3tagcsall_data", 1, 3, 1, 1);
        TH1D* h3tagudall_data = h3PtFlavorPairs_DATAMC_DATA->ProjectionZ("h3tagudall_data", 1, 3, 2, 2);
        TH1D* h3tagxall_data = h3PtFlavorPairs_DATAMC_DATA->ProjectionZ("h3tagxall_data", 1, 3, 3, 3);


        // Cloning and renaming histograms
        TH1D* h3all_scaled = (TH1D*)h3all->Clone("h3all_scaled");
        TH1D* h3all_scaled2 = (TH1D*)h3all->Clone("h3all_scaled2");

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

        h3tagcsall_data->Scale(1./h3all_data->Integral());
        h3tagudall_data->Scale(1./h3all_data->Integral());
        h3tagxall_data->Scale(1./h3all_data->Integral());

        h3all_data->Scale(1./h3all_data->Integral());

        // Scaling histograms
        double integral = h3all->Integral();
        h3gencstagcs->Scale(1.0 / integral);
        h3gencstagud->Scale(1.0 / integral);
        h3gencstagx->Scale(1.0 / integral);
        
        h3genudtagcs->Scale(1.0 / integral);
        h3genudtagud->Scale(1.0 / integral);
        h3genudtagx->Scale(1.0 / integral);

        h3genxtagcs->Scale(1.0 / integral);
        h3genxtagud->Scale(1.0 / integral);
        h3genxtagx->Scale(1.0 / integral);

        h3tagcsall->Scale(1.0 / integral);
        h3tagudall->Scale(1.0 / integral);
        h3tagxall->Scale(1.0 / integral);

        h3all->Scale(1.0 / integral);

        // Scaling cloned histograms
        h3gencstagx_scaled->Scale(1);
        h3genudtagx_scaled->Scale(1);
        h3genxtagx_scaled->Scale(1);

        h3gencstagud_scaled->Scale(0.9);
        h3genudtagud_scaled->Scale(0.8);
        h3genxtagud_scaled->Scale(0.8);

        h3gencstagcs_scaled->Scale(0.9);
        h3genudtagcs_scaled->Scale(0.8);
        h3genxtagcs_scaled->Scale(0.8);

        // Reset and sum scaled histograms
        h3all_scaled->Reset();
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

        // Final scaling
        double scale_factor2 = 1.0 / h3all_scaled->Integral();

        h3tagcsall_scaled->Scale(scale_factor2);
        h3tagudall_scaled->Scale(scale_factor2);
        h3tagxall_scaled->Scale(scale_factor2);

        h3all_scaled->Scale(scale_factor2);

            // Calculate chi-squared values
            TH1D *h_tagcsvsdata_scaled = (TH1D*)h3tagcsall_scaled->Clone("h_tagcsvsdata_scaled");
            h_tagcsvsdata_scaled->Divide(h3tagcsall_data);

            // Fit the ratio histogram with a constant function
            TF1* f7m = new TF1("f7m", "[0]", -0.7, 0.7);
            f7m->FixParameter(0, 1);
            h_tagcsvsdata_scaled->Fit(f7m, "RN");
            if(scale1 == 0.950 && scale2 == 0.950) h_tagcsvsdata_scaled_00 = h_tagcsvsdata_scaled;
            if(scale1 == 0.955 && scale2 == 0.955) h_tagcsvsdata_scaled_11 = h_tagcsvsdata_scaled;
            if(scale1 == 1.000 && scale2 == 1.000) h_tagcsvsdata_scaled_22 = h_tagcsvsdata_scaled;
            
            double chi27m = f7m->GetChisquare();

            // Fill the TH2D histogram
            if(f7m->GetNDF() > 0){
                chi2_hist2->Fill(scale1, scale2, chi27m);
            }
            cout << "scale1 = " << scale1 << ", scale2 = " << scale2 << ", chi27m = " << chi27m << endl << flush;
        }
    }


// Draw the TH2D histogram
TCanvas* c2 = new TCanvas("c2", "Chi-squared values", 1000, 600);
c2->SetRightMargin(0.17);
c2->SetLogz();
chi2_hist2->Draw("COLZ");
chi2_hist2->GetZaxis()->SetMoreLogLabels();
chi2_hist2->GetZaxis()->SetNoExponent();


TLine *l = new TLine();
l->DrawLine(0.95,1.05,1.05,0.95);
l->SetLineStyle(kDotted);
l->DrawLine(1,0.95,1,1.05);
l->DrawLine(0.95,1.0,1.05,1.0);

TGraph *g2 = new TGraph();


double chi2_min(99999), x_min(-1), y_min(-1);
for (int i = 1; i != chi2_hist2->GetNbinsX()+1; ++i){
    int j = chi2_hist2->GetNbinsY()+1-i;
    double chi2 = chi2_hist2->GetBinContent(i,j);
    double x = chi2_hist2->GetXaxis()->GetBinCenter(i);
    g2->SetPoint(i-1,x,chi2);
    if (chi2 < chi2_min){
        chi2_min = chi2;
        x_min = chi2_hist2->GetXaxis()->GetBinCenter(i);
        y_min = chi2_hist2->GetYaxis()->GetBinCenter(j);
    }
}

//TEllipse *c = new TEllipse(x_min,y_min,0.0025);
//c->Draw();

TGraph *g = new TGraph();
g->SetPoint(0,x_min,y_min);
g->SetMarkerStyle(kFullStar);
g->SetMarkerSize(2.5);
g->Draw("same p");

cout << chi2_min << endl << flush;

// Save the canvas
c2->SaveAs("pdf/chi_squared_2D_pt.pdf");


// Save the chi2_hist2 to a ROOT file
TFile* outputFile = new TFile("chi2_hist2_pt.root", "RECREATE");
chi2_hist2->Write();
h_tagcsvsdata_scaled_00->Write("h00");
h_tagcsvsdata_scaled_11->Write("h11");
h_tagcsvsdata_scaled_22->Write("h22");
g2->Write();
outputFile->Close();

}