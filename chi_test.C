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

void chi_test() {
    setTDRStyle();
        // Open the output file
    TFile *file = new TFile("output_stag_scaledmass.root", "READ");
    TFile *file2 = new TFile("output_stag_DATA.root", "READ");

    std::vector<double> scale_factors;
    std::vector<double> chi_squared_values;
    std::vector<double> scale_factors_errors;
    std::vector<double> chi_squared_errors;

for (double scale = 0.950; scale <= 1.050; scale += 0.005) {
    // Format the histogram name with 4 decimal places
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3) << scale;
    std::string histName = "h3MassFlavorPairs_DATAMC_0.990_" + oss.str();

    // Retrieve the histogram
    TH3D* h3MassFlavorPairs_DATAMC_MC = (TH3D*)file->Get(histName.c_str());
    if (!h3MassFlavorPairs_DATAMC_MC) {
        std::cerr << "Histogram " << histName << " not found!" << std::endl;
        continue;
    }

        // Project Z for different indices and draw
        TH1D* h3all = h3MassFlavorPairs_DATAMC_MC->ProjectionZ("h3all", 1, 3, 1, 3);

        TH1D* h3gencsall = h3MassFlavorPairs_DATAMC_MC->ProjectionZ("h3gencsall", 1, 1, 1, 3);
        TH1D* h3genudall = h3MassFlavorPairs_DATAMC_MC->ProjectionZ("h3genudall", 2, 2, 1, 3);
        TH1D* h3genxall = h3MassFlavorPairs_DATAMC_MC->ProjectionZ("h3genxall", 3, 3, 1, 3);

        TH1D* h3tagcsall = h3MassFlavorPairs_DATAMC_MC->ProjectionZ("h3tagcsall", 1, 3, 1, 1);
        TH1D* h3tagudall = h3MassFlavorPairs_DATAMC_MC->ProjectionZ("h3tagudall", 1, 3, 2, 2);
        TH1D* h3tagxall = h3MassFlavorPairs_DATAMC_MC->ProjectionZ("h3tagxall", 1, 3, 3, 3);

        TH1D* h3gencstagcs = h3MassFlavorPairs_DATAMC_MC->ProjectionZ("h3gencstagcs", 1, 1, 1, 1);
        TH1D* h3gencstagud = h3MassFlavorPairs_DATAMC_MC->ProjectionZ("h3gencstagud", 1, 1, 2, 2);
        TH1D* h3gencstagx = h3MassFlavorPairs_DATAMC_MC->ProjectionZ("h3gencstagx", 1, 1, 3, 3);

        TH1D* h3genudtagcs = h3MassFlavorPairs_DATAMC_MC->ProjectionZ("h3genudtagcs", 2, 2, 1, 1);
        TH1D* h3genudtagud = h3MassFlavorPairs_DATAMC_MC->ProjectionZ("h3genudtagud", 2, 2, 2, 2);
        TH1D* h3genudtagx = h3MassFlavorPairs_DATAMC_MC->ProjectionZ("h3genudtagx", 2, 2, 3, 3);

        TH1D* h3genxtagcs = h3MassFlavorPairs_DATAMC_MC->ProjectionZ("h3genxtagcs", 3, 3, 1, 1);
        TH1D* h3genxtagud = h3MassFlavorPairs_DATAMC_MC->ProjectionZ("h3genxtagud", 3, 3, 2, 2);
        TH1D* h3genxtagx = h3MassFlavorPairs_DATAMC_MC->ProjectionZ("h3genxtagx", 3, 3, 3, 3);

    
        TH3D* h3MassFlavorPairs_DATAMC_DATA = (TH3D*)file2->Get("h3MassFlavorPairs_DATAMC");

        TH1D* h3all_data = h3MassFlavorPairs_DATAMC_DATA->ProjectionZ("h3all_data", 1, 3, 1, 3);

        TH1D* h3tagcsall_data = h3MassFlavorPairs_DATAMC_DATA->ProjectionZ("h3tagcsall_data", 1, 3, 1, 1);
        TH1D* h3tagudall_data = h3MassFlavorPairs_DATAMC_DATA->ProjectionZ("h3tagudall_data", 1, 3, 2, 2);
        TH1D* h3tagxall_data = h3MassFlavorPairs_DATAMC_DATA->ProjectionZ("h3tagxall_data", 1, 3, 3, 3);


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

        h3gencsall->Scale(1.0 / integral);
        h3genudall->Scale(1.0 / integral);
        h3genxall->Scale(1.0 / integral);

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

    // Calculate chi-squared values
    TH1D *h_tagcsvsdata_scaled = (TH1D*)h3tagcsall_scaled->Clone("h_tagcsvsdata_scaled");
    h_tagcsvsdata_scaled->Divide(h3tagcsall_data);

    // Fit the ratio histogram with a constant function
    TF1* f7 = new TF1("f7", "[0]", 70, 100);
    f7->FixParameter(0, 1);
    TF1* f7m = new TF1("f7m", "[0]", 70, 100);
    f7m->FixParameter(0, 1);

    h_tagcsvsdata_scaled->Fit(f7m, "RN");
    double chi27m = f7m->GetChisquare();
    double ndf = f7m->GetNDF();

    cout << chi27m << endl << flush;


    scale_factors.push_back(scale);
    scale_factors_errors.push_back(0);
    chi_squared_values.push_back(chi27m);
    chi_squared_errors.push_back(sqrt(ndf));
    }

        // Print the points
    std::cout << "Scale Factors and Chi-Squared Values:" << std::endl;
    for (size_t i = 0; i < scale_factors.size(); ++i) {
        std::cout << "Scale Factor: " << scale_factors[i] << ", Chi-Squared: " << chi_squared_values[i] << std::endl;
    }

    lumi_136TeV = "Run3 simulation";
    extraText = "Private";

    // Calculate the minimum and maximum chi-squared values
    double min_chi_squared = *std::min_element(chi_squared_values.begin(), chi_squared_values.end());
    double max_chi_squared = *std::max_element(chi_squared_values.begin(), chi_squared_values.end());

    // Plot the results
    TH1D *h1 = tdrHist("h1","#chi^{2}",1,7000,"R_{cs}",0.95,1.05);
    TCanvas *c1 = tdrCanvas("c1",h1,8,11,kSquare);

    //c1->SetLogy();
    h1->GetXaxis()->SetLabelSize(0.035);
    h1->GetYaxis()->SetLabelSize(0.035);

    TGraphErrors *gr = new TGraphErrors(scale_factors.size(), &scale_factors[0], &chi_squared_values[0],
    &scale_factors_errors[0],&chi_squared_errors[0]);
    gr->SetMarkerStyle(20);  // Set marker style to points
    // Set y-axis range for the graph
    gr->GetYaxis()->SetRangeUser(0.99,1.03);
    gr->SetMarkerSize(1.0);
    gr->Draw("same p");  // Draw points only


    // Fit a parabola to the points
    TF1 *parabola = new TF1("parabola", "[0] + [1]*(x-1) + [2]*(x-1)*(x-1)", 0.978, 1.032);
    parabola->SetParameters(35,0,(350-35)/(0.03*0.03));
    gr->Fit(parabola, "NR");  // Fit within the range of the scale factors

    TF1 *parabola2 = new TF1("parabola2", "[0] + [1]*(x-1) + [2]*(x-1)*(x-1)", 0.992, 1.01);
    parabola2->SetParameters(35,0,(350-35)/(0.03*0.03));
    gr->Fit(parabola2, "NR");  // Fit within the range of the scale factors

// Get minimum y value
double ymin = parabola2->GetMinimum();
std::cout << "ymin = " << ymin << std::endl;

double xmin =parabola2->GetMinimumX();
//double xmin = 1.00298;
std::cout << "xmin = " << xmin << std::endl;

// Calculate ymin + error
double ymin_plus_error = ymin + chi_squared_errors[105];
std::cout << "ymin + error = " << ymin_plus_error << std::endl;

double x_values_min = parabola2->GetX(ymin_plus_error,0.98,xmin);
double x_values_max = parabola2->GetX(ymin_plus_error,xmin,1.02);
/*
// Check for multiple x values for ymin_plus_error
std::vector<double> x_values_max;
double step = 0.0001;  // Smaller step for finer search
for (double x = 0.98; x <= 1.02; x += step) {
    if (std::abs(parabola2->Eval(x) - ymin_plus_error) < 1e-5) {
        x_values_max.push_back(x);
    }
}
*/
// Print the results
std::cout << "ymin = " << ymin << ", xmin = " << xmin << std::endl;
std::cout << "ymin + error = " << ymin_plus_error << ", x_values_min: " << x_values_min 
<< ", x_values_max " << x_values_max << endl << flush;


    // Draw the fitted parabola
    parabola->SetLineColor(kRed);
    parabola->Draw("same");

    parabola2->SetLineColor(kAzure+7);
    parabola2->Draw("same");



    TLegend *leg107 = tdrLeg(0.62,1.1-0.05*3,0.8,0.8);
    //leg107->AddEntry(h_tagcsvsdata, "MC", "PLE");
    //leg107->AddEntry(h_tagcsvsdata_scaled, "scaled MC", "PLE");
    //leg107->AddEntry(h_tagcsvsdata_mass, "scaled mass MC", "PLE");
    

    TLatex *tex107 = new TLatex();
    tex107->SetNDC(); tex107->SetTextSize(0.045);

    // Update the canvas to reflect the changes
    gPad->Update();
    gPad->RedrawAxis();
    c1->SaveAs("pdf/chi_squared_TEST.pdf");
}