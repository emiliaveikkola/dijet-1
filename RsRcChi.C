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

void RsRcChi() {
    setTDRStyle();
        // Open the output file
    TFile *file = new TFile("output_stag_scaledmass.root", "READ");
    TFile *file2 = new TFile("output_stag_DATA.root", "READ");

    std::vector<double> scale_factors_S;
    std::vector<double> chi_squared_values_S;
    std::vector<double> scale_factors_errors_S;
    std::vector<double> chi_squared_errors_S;

    std::vector<double> scale_factors_C;
    std::vector<double> chi_squared_values_C;
    std::vector<double> scale_factors_errors_C;
    std::vector<double> chi_squared_errors_C;

for (double scale_S = 0.950; scale_S <= 1.050; scale_S += 0.0005) {
    // Format the histogram name with 4 decimal places
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(4) << scale_S;
    std::string histName = "h3MassFlavorPairs_DATAMC_S_scale_" + oss.str();

    // Retrieve the histogram
    TH3D* h3MassFlavorPairs_DATAMC_S_MC = (TH3D*)file->Get(histName.c_str());
    if (!h3MassFlavorPairs_DATAMC_S_MC) {
        std::cerr << "Histogram " << histName << " not found!" << std::endl;
        continue;
    }

        // Project Z for different indices and draw
        TH1D* h3Sall = h3MassFlavorPairs_DATAMC_S_MC->ProjectionZ("h3Sall", 1, 3, 1, 3);

        TH1D* h3Stagcsall = h3MassFlavorPairs_DATAMC_S_MC->ProjectionZ("h3Stagcsall", 1, 3, 1, 1);
        TH1D* h3Stagudall = h3MassFlavorPairs_DATAMC_S_MC->ProjectionZ("h3Stagudall", 1, 3, 2, 2);
        TH1D* h3Stagxall = h3MassFlavorPairs_DATAMC_S_MC->ProjectionZ("h3Stagxall", 1, 3, 3, 3);

        TH1D* h3Sgencstagcs = h3MassFlavorPairs_DATAMC_S_MC->ProjectionZ("h3Sgencstagcs", 1, 1, 1, 1);
        TH1D* h3Sgencstagud = h3MassFlavorPairs_DATAMC_S_MC->ProjectionZ("h3Sgencstagud", 1, 1, 2, 2);
        TH1D* h3Sgencstagx = h3MassFlavorPairs_DATAMC_S_MC->ProjectionZ("h3Sgencstagx", 1, 1, 3, 3);

        TH1D* h3Sgenudtagcs = h3MassFlavorPairs_DATAMC_S_MC->ProjectionZ("h3Sgenudtagcs", 2, 2, 1, 1);
        TH1D* h3Sgenudtagud = h3MassFlavorPairs_DATAMC_S_MC->ProjectionZ("h3Sgenudtagud", 2, 2, 2, 2);
        TH1D* h3Sgenudtagx = h3MassFlavorPairs_DATAMC_S_MC->ProjectionZ("h3Sgenudtagx", 2, 2, 3, 3);

        TH1D* h3Sgenxtagcs = h3MassFlavorPairs_DATAMC_S_MC->ProjectionZ("h3Sgenxtagcs", 3, 3, 1, 1);
        TH1D* h3Sgenxtagud = h3MassFlavorPairs_DATAMC_S_MC->ProjectionZ("h3Sgenxtagud", 3, 3, 2, 2);
        TH1D* h3Sgenxtagx = h3MassFlavorPairs_DATAMC_S_MC->ProjectionZ("h3Sgenxtagx", 3, 3, 3, 3);

    
        TH3D* h3MassFlavorPairs_DATAMC_S_DATA = (TH3D*)file2->Get("h3MassFlavorPairs_DATAMC");

        TH1D* h3Sall_data = h3MassFlavorPairs_DATAMC_S_DATA->ProjectionZ("h3Sall_data", 1, 3, 1, 3);

        TH1D* h3Stagcsall_data = h3MassFlavorPairs_DATAMC_S_DATA->ProjectionZ("h3Stagcsall_data", 1, 3, 1, 1);
    


        // Cloning and renaming histograms
        TH1D* h3Sall_scaled = (TH1D*)h3Sall->Clone("h3Sall_scaled");
        TH1D* h3Sall_scaled2 = (TH1D*)h3Sall->Clone("h3Sall_scaled2");

        TH1D* h3Stagcsall_scaled = (TH1D*)h3Stagcsall->Clone("h3Stagcsall_scaled");
        TH1D* h3Stagudall_scaled = (TH1D*)h3Stagudall->Clone("h3Stagudall_scaled");
        TH1D* h3Stagxall_scaled = (TH1D*)h3Stagxall->Clone("h3Stagxall_scaled");

        TH1D* h3Sgencstagcs_scaled = (TH1D*)h3Sgencstagcs->Clone("h3Sgencstagcs_scaled");
        TH1D* h3Sgencstagud_scaled = (TH1D*)h3Sgencstagud->Clone("h3Sgencstagud_scaled");
        TH1D* h3Sgencstagx_scaled = (TH1D*)h3Sgencstagx->Clone("h3Sgencstagx_scaled");

        TH1D* h3Sgenudtagcs_scaled = (TH1D*)h3Sgenudtagcs->Clone("h3Sgenudtagcs_scaled");
        TH1D* h3Sgenudtagud_scaled = (TH1D*)h3Sgenudtagud->Clone("h3Sgenudtagud_scaled");
        TH1D* h3Sgenudtagx_scaled = (TH1D*)h3Sgenudtagx->Clone("h3Sgenudtagx_scaled");

        TH1D* h3Sgenxtagcs_scaled = (TH1D*)h3Sgenxtagcs->Clone("h3Sgenxtagcs_scaled");
        TH1D* h3Sgenxtagud_scaled = (TH1D*)h3Sgenxtagud->Clone("h3Sgenxtagud_scaled");
        TH1D* h3Sgenxtagx_scaled = (TH1D*)h3Sgenxtagx->Clone("h3Sgenxtagx_scaled");

        h3Stagcsall_data->Scale(1./h3Sall_data->Integral());
        h3Sall_data->Scale(1./h3Sall_data->Integral());

        // Scaling histograms
        double integral = h3Sall->Integral();
        h3Sgencstagcs->Scale(1.0 / integral);
        h3Sgencstagud->Scale(1.0 / integral);
        h3Sgencstagx->Scale(1.0 / integral);
        
        h3Sgenudtagcs->Scale(1.0 / integral);
        h3Sgenudtagud->Scale(1.0 / integral);
        h3Sgenudtagx->Scale(1.0 / integral);

        h3Sgenxtagcs->Scale(1.0 / integral);
        h3Sgenxtagud->Scale(1.0 / integral);
        h3Sgenxtagx->Scale(1.0 / integral);

        h3Stagcsall->Scale(1.0 / integral);
        h3Stagudall->Scale(1.0 / integral);
        h3Stagxall->Scale(1.0 / integral);

        h3Sall->Scale(1.0 / integral);

        // Scaling cloned histograms
        h3Sgencstagx_scaled->Scale(1);
        h3Sgenudtagx_scaled->Scale(1);
        h3Sgenxtagx_scaled->Scale(1);

        h3Sgencstagud_scaled->Scale(0.9);
        h3Sgenudtagud_scaled->Scale(0.8);
        h3Sgenxtagud_scaled->Scale(0.8);

        h3Sgencstagcs_scaled->Scale(0.9);
        h3Sgenudtagcs_scaled->Scale(0.8);
        h3Sgenxtagcs_scaled->Scale(0.8);

        // Reset and sum scaled histograms
        h3Sall_scaled->Reset();
        h3Sall_scaled->Add(h3Sgencstagcs_scaled);
        h3Sall_scaled->Add(h3Sgencstagud_scaled);
        h3Sall_scaled->Add(h3Sgencstagx_scaled);
        h3Sall_scaled->Add(h3Sgenudtagcs_scaled);
        h3Sall_scaled->Add(h3Sgenudtagud_scaled);
        h3Sall_scaled->Add(h3Sgenudtagx_scaled);
        h3Sall_scaled->Add(h3Sgenxtagcs_scaled);
        h3Sall_scaled->Add(h3Sgenxtagud_scaled);
        h3Sall_scaled->Add(h3Sgenxtagx_scaled);

        h3Stagcsall_scaled->Reset();
        h3Stagcsall_scaled->Add(h3Sgencstagcs_scaled);
        h3Stagcsall_scaled->Add(h3Sgenudtagcs_scaled);
        h3Stagcsall_scaled->Add(h3Sgenxtagcs_scaled);

        // Final scaling
        double scale_factor2 = 1.0 / h3Sall_scaled->Integral();

        h3Stagcsall_scaled->Scale(scale_factor2);


        h3Sall_scaled->Scale(scale_factor2);

    // Calculate chi-squared values
    TH1D *hS_tagcsvsdata_scaled = (TH1D*)h3Stagcsall_scaled->Clone("hS_tagcsvsdata_scaled");
    hS_tagcsvsdata_scaled->Divide(h3Stagcsall_data);

    // Fit the ratio histogram with a constant function
    TF1* f7s = new TF1("f7s", "[0]", 70, 100);
    f7s->FixParameter(0, 1);

    hS_tagcsvsdata_scaled->Fit(f7s, "RN");
    double chi2s = f7s->GetChisquare();
    double ndfs = f7s->GetNDF();

    cout << chi2s << endl << flush;


    scale_factors_S.push_back(scale_S);
    scale_factors_errors_S.push_back(0);
    chi_squared_values_S.push_back(chi2s);
    chi_squared_errors_S.push_back(sqrt(ndfs));
    }





































    for (double scale_C = 0.950; scale_C <= 1.050; scale_C += 0.0005) {
    // Format the histogram name with 4 decimal places
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(4) << scale_C;
    std::string histName = "h3MassFlavorPairs_DATAMC_C_scale_" + oss.str();

    // Retrieve the histogram
    TH3D* h3MassFlavorPairs_DATAMC_C_MC = (TH3D*)file->Get(histName.c_str());
    if (!h3MassFlavorPairs_DATAMC_C_MC) {
        std::cerr << "Histogram " << histName << " not found!" << std::endl;
        continue;
    }

        // Project Z for different indices and draw
        TH1D* h3Call = h3MassFlavorPairs_DATAMC_C_MC->ProjectionZ("h3Call", 1, 3, 1, 3);

        TH1D* h3Ctagcsall = h3MassFlavorPairs_DATAMC_C_MC->ProjectionZ("h3Ctagcsall", 1, 3, 1, 1);
        TH1D* h3Ctagudall = h3MassFlavorPairs_DATAMC_C_MC->ProjectionZ("h3Ctagudall", 1, 3, 2, 2);
        TH1D* h3Ctagxall = h3MassFlavorPairs_DATAMC_C_MC->ProjectionZ("h3Ctagxall", 1, 3, 3, 3);

        TH1D* h3Cgencstagcs = h3MassFlavorPairs_DATAMC_C_MC->ProjectionZ("h3Cgencstagcs", 1, 1, 1, 1);
        TH1D* h3Cgencstagud = h3MassFlavorPairs_DATAMC_C_MC->ProjectionZ("h3Cgencstagud", 1, 1, 2, 2);
        TH1D* h3Cgencstagx = h3MassFlavorPairs_DATAMC_C_MC->ProjectionZ("h3Cgencstagx", 1, 1, 3, 3);

        TH1D* h3Cgenudtagcs = h3MassFlavorPairs_DATAMC_C_MC->ProjectionZ("h3Cgenudtagcs", 2, 2, 1, 1);
        TH1D* h3Cgenudtagud = h3MassFlavorPairs_DATAMC_C_MC->ProjectionZ("h3Cgenudtagud", 2, 2, 2, 2);
        TH1D* h3Cgenudtagx = h3MassFlavorPairs_DATAMC_C_MC->ProjectionZ("h3Cgenudtagx", 2, 2, 3, 3);

        TH1D* h3Cgenxtagcs = h3MassFlavorPairs_DATAMC_C_MC->ProjectionZ("h3Cgenxtagcs", 3, 3, 1, 1);
        TH1D* h3Cgenxtagud = h3MassFlavorPairs_DATAMC_C_MC->ProjectionZ("h3Cgenxtagud", 3, 3, 2, 2);
        TH1D* h3Cgenxtagx = h3MassFlavorPairs_DATAMC_C_MC->ProjectionZ("h3Cgenxtagx", 3, 3, 3, 3);

    
        TH3D* h3MassFlavorPairs_DATAMC_C_DATA = (TH3D*)file2->Get("h3MassFlavorPairs_DATAMC");

        TH1D* h3Call_data = h3MassFlavorPairs_DATAMC_C_DATA->ProjectionZ("h3Call_data", 1, 3, 1, 3);

        TH1D* h3Ctagcsall_data = h3MassFlavorPairs_DATAMC_C_DATA->ProjectionZ("h3Ctagcsall_data", 1, 3, 1, 1);
        TH1D* h3Ctagudall_data = h3MassFlavorPairs_DATAMC_C_DATA->ProjectionZ("h3Ctagudall_data", 1, 3, 2, 2);
        TH1D* h3Ctagxall_data = h3MassFlavorPairs_DATAMC_C_DATA->ProjectionZ("h3Ctagxall_data", 1, 3, 3, 3);


        // Cloning and renaming histograms
        TH1D* h3Call_scaled = (TH1D*)h3Call->Clone("h3Call_scaled");
        TH1D* h3Call_scaled2 = (TH1D*)h3Call->Clone("h3Call_scaled2");

        TH1D* h3Ctagcsall_scaled = (TH1D*)h3Ctagcsall->Clone("h3Ctagcsall_scaled");
        TH1D* h3Ctagudall_scaled = (TH1D*)h3Ctagudall->Clone("h3Ctagudall_scaled");
        TH1D* h3Ctagxall_scaled = (TH1D*)h3Ctagxall->Clone("h3Ctagxall_scaled");

        TH1D* h3Cgencstagcs_scaled = (TH1D*)h3Cgencstagcs->Clone("h3Cgencstagcs_scaled");
        TH1D* h3Cgencstagud_scaled = (TH1D*)h3Cgencstagud->Clone("h3Cgencstagud_scaled");
        TH1D* h3Cgencstagx_scaled = (TH1D*)h3Cgencstagx->Clone("h3Cgencstagx_scaled");

        TH1D* h3Cgenudtagcs_scaled = (TH1D*)h3Cgenudtagcs->Clone("h3Cgenudtagcs_scaled");
        TH1D* h3Cgenudtagud_scaled = (TH1D*)h3Cgenudtagud->Clone("h3Cgenudtagud_scaled");
        TH1D* h3Cgenudtagx_scaled = (TH1D*)h3Cgenudtagx->Clone("h3Cgenudtagx_scaled");

        TH1D* h3Cgenxtagcs_scaled = (TH1D*)h3Cgenxtagcs->Clone("h3Cgenxtagcs_scaled");
        TH1D* h3Cgenxtagud_scaled = (TH1D*)h3Cgenxtagud->Clone("h3Cgenxtagud_scaled");
        TH1D* h3Cgenxtagx_scaled = (TH1D*)h3Cgenxtagx->Clone("h3Cgenxtagx_scaled");

        h3Ctagcsall_data->Scale(1./h3Call_data->Integral());
        h3Ctagudall_data->Scale(1./h3Call_data->Integral());
        h3Ctagxall_data->Scale(1./h3Call_data->Integral());

        h3Call_data->Scale(1./h3Call_data->Integral());

        // Scaling histograms
        double integral = h3Call->Integral();
        h3Cgencstagcs->Scale(1.0 / integral);
        h3Cgencstagud->Scale(1.0 / integral);
        h3Cgencstagx->Scale(1.0 / integral);
        
        h3Cgenudtagcs->Scale(1.0 / integral);
        h3Cgenudtagud->Scale(1.0 / integral);
        h3Cgenudtagx->Scale(1.0 / integral);

        h3Cgenxtagcs->Scale(1.0 / integral);
        h3Cgenxtagud->Scale(1.0 / integral);
        h3Cgenxtagx->Scale(1.0 / integral);

        h3Ctagcsall->Scale(1.0 / integral);
        h3Ctagudall->Scale(1.0 / integral);
        h3Ctagxall->Scale(1.0 / integral);

        h3Call->Scale(1.0 / integral);

        // Scaling cloned histograms
        h3Cgencstagx_scaled->Scale(1);
        h3Cgenudtagx_scaled->Scale(1);
        h3Cgenxtagx_scaled->Scale(1);

        h3Cgencstagud_scaled->Scale(0.9);
        h3Cgenudtagud_scaled->Scale(0.8);
        h3Cgenxtagud_scaled->Scale(0.8);

        h3Cgencstagcs_scaled->Scale(0.9);
        h3Cgenudtagcs_scaled->Scale(0.8);
        h3Cgenxtagcs_scaled->Scale(0.8);

        // Reset and sum scaled histograms
        h3Call_scaled->Reset();
        h3Call_scaled->Add(h3Cgencstagcs_scaled);
        h3Call_scaled->Add(h3Cgencstagud_scaled);
        h3Call_scaled->Add(h3Cgencstagx_scaled);
        h3Call_scaled->Add(h3Cgenudtagcs_scaled);
        h3Call_scaled->Add(h3Cgenudtagud_scaled);
        h3Call_scaled->Add(h3Cgenudtagx_scaled);
        h3Call_scaled->Add(h3Cgenxtagcs_scaled);
        h3Call_scaled->Add(h3Cgenxtagud_scaled);
        h3Call_scaled->Add(h3Cgenxtagx_scaled);

        h3Ctagcsall_scaled->Reset();
        h3Ctagcsall_scaled->Add(h3Cgencstagcs_scaled);
        h3Ctagcsall_scaled->Add(h3Cgenudtagcs_scaled);
        h3Ctagcsall_scaled->Add(h3Cgenxtagcs_scaled);

        // Final scaling
        double scale_factor2 = 1.0 / h3Call_scaled->Integral();

        h3Ctagcsall_scaled->Scale(scale_factor2);


        h3Call_scaled->Scale(scale_factor2);

    // Calculate chi-squared values
    TH1D *hC_tagcsvsdata_scaled = (TH1D*)h3Ctagcsall_scaled->Clone("hC_tagcsvsdata_scaled");
    hC_tagcsvsdata_scaled->Divide(h3Ctagcsall_data);

    // Fit the ratio histogram with a constant function
    TF1* f7c = new TF1("f7c", "[0]", 70, 100);
    f7c->FixParameter(0, 1);

    hC_tagcsvsdata_scaled->Fit(f7c, "RN");
    double chi2c = f7c->GetChisquare();
    double ndfc = f7c->GetNDF();

    cout << chi2c << endl << flush;


    scale_factors_C.push_back(scale_C);
    scale_factors_errors_C.push_back(0);
    chi_squared_values_C.push_back(chi2c);
    chi_squared_errors_C.push_back(sqrt(ndfc));
    }












    

        // Print the points
    std::cout << "Scale Factors and Chi-Squared Values:" << std::endl;
    for (size_t i = 0; i < scale_factors_S.size(); ++i) {
        std::cout << "Scale Factor: " << scale_factors_S[i] << ", Chi-Squared: " << chi_squared_values_S[i] << std::endl;
    }

            // Print the points
    std::cout << "Scale Factors and Chi-Squared Values:" << std::endl;
    for (size_t i = 0; i < scale_factors_C.size(); ++i) {
        std::cout << "Scale Factor: " << scale_factors_C[i] << ", Chi-Squared: " << chi_squared_values_C[i] << std::endl;
    }

    lumi_136TeV = "Run3 simulation";
    extraText = "Private";

    // Calculate the minimum and maximum chi-squared values
    double min_chi_squared_S = *std::min_element(chi_squared_values_S.begin(), chi_squared_values_S.end());
    double max_chi_squared_S = *std::max_element(chi_squared_values_S.begin(), chi_squared_values_S.end());


    // Plot the results
    TH1D *h1 = tdrHist("h1","#chi^{2}",1,500,"R_{cs}",0.985,1.015);
    TCanvas *c1 = tdrCanvas("c1",h1,8,11,kSquare);

    //c1->SetLogy();
    h1->GetXaxis()->SetLabelSize(0.035);
    h1->GetYaxis()->SetLabelSize(0.035);

    TGraphErrors *grs = new TGraphErrors(scale_factors_S.size(), &scale_factors_S[0], &chi_squared_values_S[0],
    &scale_factors_errors_S[0],&chi_squared_errors_S[0]);
    grs->SetMarkerStyle(20);  // Set marker style to points
    // Set y-axis range for the graph
    grs->GetYaxis()->SetRangeUser(0.99,1.03);
    grs->SetMarkerSize(1.0);
    grs->Draw("same p");  // Draw points only


    // Fit a parabola to the points
    TF1 *parabolas = new TF1("parabolas", "[0] + [1]*(x-1) + [2]*(x-1)*(x-1)", 0.978, 1.032);
    parabolas->SetParameters(35,0,(350-35)/(0.03*0.03));
    grs->Fit(parabolas, "NR");  // Fit within the range of the scale factors

    TF1 *parabola2s = new TF1("parabola2s", "[0] + [1]*(x-1) + [2]*(x-1)*(x-1)", 0.992, 1.01);
    parabola2s->SetParameters(35,0,(350-35)/(0.03*0.03));
    grs->Fit(parabola2s, "NR");  // Fit within the range of the scale factors

// Get minimum y value
double ymins = parabola2s->GetMinimum();
std::cout << "ymin = " << ymins << std::endl;

double xmins =parabola2s->GetMinimumX();
//double xmin = 1.00298;
std::cout << "xmin = " << xmins << std::endl;

// Calculate ymin + error
double ymin_plus_errors = ymins + chi_squared_errors_S[105];
std::cout << "ymin + error = " << ymin_plus_errors << std::endl;

double x_values_mins = parabola2s->GetX(ymin_plus_errors,0.98,xmins);
double x_values_maxs = parabola2s->GetX(ymin_plus_errors,xmins,1.02);

// Print the results
std::cout << "ymin = " << ymins << ", xmin = " << xmins << std::endl;
std::cout << "ymin + error = " << ymin_plus_errors << ", x_values_min: " << x_values_mins 
<< ", x_values_max " << x_values_maxs << endl << flush;


    // Draw the fitted parabola
    parabolas->SetLineColor(kRed);
    parabolas->Draw("same");

    parabola2s->SetLineColor(kAzure+7);
    parabola2s->Draw("same");



    TLegend *leg107 = tdrLeg(0.62,1.1-0.05*3,0.8,0.8);
    //leg107->AddEntry(h_tagcsvsdata, "MC", "PLE");
    //leg107->AddEntry(h_tagcsvsdata_scaled, "scaled MC", "PLE");
    //leg107->AddEntry(h_tagcsvsdata_mass, "scaled mass MC", "PLE");
    

    TLatex *tex107 = new TLatex();
    tex107->SetNDC(); tex107->SetTextSize(0.045);

    // Update the canvas to reflect the changes
    gPad->Update();
    gPad->RedrawAxis();
    c1->SaveAs("pdf/chi_squared_vs_scale_factor_S.pdf");





    double min_chi_squared_C = *std::min_element(chi_squared_values_C.begin(), chi_squared_values_C.end());
    double max_chi_squared_C = *std::max_element(chi_squared_values_C.begin(), chi_squared_values_C.end());
        // Plot the results
    TH1D *h2 = tdrHist("h2","#chi^{2}",1,500,"R_{cs}",0.985,1.015);
    TCanvas *c2 = tdrCanvas("c2",h2,8,11,kSquare);

    //c1->SetLogy();
    h2->GetXaxis()->SetLabelSize(0.035);
    h2->GetYaxis()->SetLabelSize(0.035);

    TGraphErrors *grc = new TGraphErrors(scale_factors_C.size(), &scale_factors_C[0], &chi_squared_values_C[0],
    &scale_factors_errors_C[0],&chi_squared_errors_C[0]);
    grc->SetMarkerStyle(20);  // Set marker style to points
    // Set y-axis range for the graph
    grc->GetYaxis()->SetRangeUser(0.99,1.03);
    grc->SetMarkerSize(1.0);
    grc->Draw("same p");  // Draw points only


    // Fit a parabola to the points
    TF1 *parabolac = new TF1("parabolac", "[0] + [1]*(x-1) + [2]*(x-1)*(x-1)", 0.978, 1.032);
    parabolac->SetParameters(35,0,(350-35)/(0.03*0.03));
    grc->Fit(parabolac, "NR");  // Fit within the range of the scale factors

    TF1 *parabola2c = new TF1("parabola2c", "[0] + [1]*(x-1) + [2]*(x-1)*(x-1)", 0.992, 1.01);
    parabola2c->SetParameters(35,0,(350-35)/(0.03*0.03));
    grc->Fit(parabola2c, "NR");  // Fit within the range of the scale factors

// Get minimum y value
double yminc = parabola2c->GetMinimum();
std::cout << "ymin = " << yminc << std::endl;

double xminc =parabola2c->GetMinimumX();
//double xmin = 1.00298;
std::cout << "xmin = " << xminc << std::endl;

// Calculate ymin + error
double ymin_plus_errorc = yminc + chi_squared_errors_C[105];
std::cout << "ymin + error = " << ymin_plus_errorc << std::endl;

double x_values_minc = parabola2c->GetX(ymin_plus_errorc,0.98,xminc);
double x_values_maxc = parabola2c->GetX(ymin_plus_errorc,xminc,1.02);

// Print the results
std::cout << "ymin = " << yminc << ", xmin = " << xminc << std::endl;
std::cout << "ymin + error = " << ymin_plus_errorc << ", x_values_min: " << x_values_minc 
<< ", x_values_max " << x_values_maxc << endl << flush;


    // Draw the fitted parabola
    parabolac->SetLineColor(kRed);
    parabolac->Draw("same");

    parabola2c->SetLineColor(kAzure+7);
    parabola2c->Draw("same");



    TLegend *leg108 = tdrLeg(0.62,1.1-0.05*3,0.8,0.8);
    //leg107->AddEntry(h_tagcsvsdata, "MC", "PLE");
    //leg107->AddEntry(h_tagcsvsdata_scaled, "scaled MC", "PLE");
    //leg107->AddEntry(h_tagcsvsdata_mass, "scaled mass MC", "PLE");
    

    TLatex *tex108 = new TLatex();
    tex108->SetNDC(); tex108->SetTextSize(0.045);

    // Update the canvas to reflect the changes
    gPad->Update();
    gPad->RedrawAxis();
    c2->SaveAs("pdf/chi_squared_vs_scale_factor_C.pdf");
}