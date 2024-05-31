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
#include <vector>
#include <utility>
#include "tdrstyle_mod22.C"

TH1D* GetProjectionZ(TH3D* hist, const char* name, int x1, int x2, int y1, int y2) {
    TH1D* proj = hist->ProjectionZ(name, x1, x2, y1, y2);
    proj->SetName(name);
    proj->SetTitle("");
    proj->SetStats(0); // Turn off statistics box
    return proj;
}

void MCDATA_mass() {
    TFile *file = new TFile("output_stag3.root", "READ");
    TH3D* h3MassFlavorPairs_DATAMC_MC = (TH3D*)file->Get("h3MassFlavorPairs_DATAMC");

    TFile *file2 = new TFile("output_stag_DATA.root", "READ");
    TH3D* h3MassFlavorPairs_DATAMC_DATA = (TH3D*)file2->Get("h3MassFlavorPairs_DATAMC");

    // Create and store histograms in vectors
    std::vector<std::pair<TH1D*, const char*>> histograms = {
        {GetProjectionZ(h3MassFlavorPairs_DATAMC_MC, "h3gencstagx", 1, 1, 3, 3), "gencs,tagx"},
        {GetProjectionZ(h3MassFlavorPairs_DATAMC_MC, "h3genudtagx", 2, 2, 3, 3), "genud,tagx"},
        {GetProjectionZ(h3MassFlavorPairs_DATAMC_MC, "h3genxtagx", 3, 3, 3, 3), "genx,tagx"},
        {GetProjectionZ(h3MassFlavorPairs_DATAMC_MC, "h3tagxall", 1, 3, 3, 3), "genall,tagx"},
        {GetProjectionZ(h3MassFlavorPairs_DATAMC_MC, "h3gencstagud", 1, 1, 2, 2), "gencs,tagud"},
        {GetProjectionZ(h3MassFlavorPairs_DATAMC_MC, "h3genudtagud", 2, 2, 2, 2), "genud,tagud"},
        {GetProjectionZ(h3MassFlavorPairs_DATAMC_MC, "h3genxtagud", 3, 3, 2, 2), "genx,tagud"},
        {GetProjectionZ(h3MassFlavorPairs_DATAMC_MC, "h3tagudall", 1, 3, 2, 2), "genall,tagud"},
        {GetProjectionZ(h3MassFlavorPairs_DATAMC_MC, "h3gencstagcs", 1, 1, 1, 1), "gencs,tagcs"},
        {GetProjectionZ(h3MassFlavorPairs_DATAMC_MC, "h3genudtagcs", 2, 2, 1, 1), "genud,tagcs"},
        {GetProjectionZ(h3MassFlavorPairs_DATAMC_MC, "h3genxtagcs", 3, 3, 1, 1), "genx,tagcs"},
        {GetProjectionZ(h3MassFlavorPairs_DATAMC_MC, "h3tagcsall", 1, 3, 1, 1), "genall,tagcs"},
        {GetProjectionZ(h3MassFlavorPairs_DATAMC_MC, "h3gencsall", 1, 1, 1, 3), "gencs,tagall"},
        {GetProjectionZ(h3MassFlavorPairs_DATAMC_MC, "h3genudall", 2, 2, 1, 3), "genud,tagall"},
        {GetProjectionZ(h3MassFlavorPairs_DATAMC_MC, "h3genxall", 3, 3, 1, 3), "genx,tagall"},
        {GetProjectionZ(h3MassFlavorPairs_DATAMC_MC, "h3all", 1, 3, 1, 3), "all"}
    };

    std::vector<std::pair<TH1D*, const char*>> histograms_data = {
        {GetProjectionZ(h3MassFlavorPairs_DATAMC_DATA, "h3tagcsall_data", 1, 3, 1, 1), "genall,tagcs"},
        {GetProjectionZ(h3MassFlavorPairs_DATAMC_DATA, "h3tagudall_data", 1, 3, 2, 2), "genall,tagud"},
        {GetProjectionZ(h3MassFlavorPairs_DATAMC_DATA, "h3tagxall_data", 1, 3, 3, 3), "genall,tagx"},
        {GetProjectionZ(h3MassFlavorPairs_DATAMC_DATA, "h3all_data", 1, 3, 1, 3), "all"}
    };

    // Scale MC histograms
    double mc_integral = histograms.back().first->Integral();
    for (auto& [hist, _] : histograms) {
        hist->Scale(1./mc_integral);
    }

    // Scale DATA histograms
    double data_integral = histograms_data.back().first->Integral();
    for (auto& [hist, _] : histograms_data) {
        hist->Scale(1./data_integral);
    }

    TCanvas *c3 = new TCanvas("c3", "Canvas with 3x3 Grid", 2560, 1440);
    c3->Divide(4, 4);

    for (size_t i = 0; i < histograms.size(); ++i) {
        c3->cd(i + 1);
        gPad->SetLeftMargin(0.1);
        gPad->SetRightMargin(0);
        gPad->SetBottomMargin(0.08);
        gPad->SetTopMargin(0);

        auto [hist, label] = histograms[i];
        tdrDraw(hist, "HPz", kNone, kAzure+7, kSolid, -1, 1001, kAzure+7);
        hist->SetFillColorAlpha(kAzure+7, 0.25);
        hist->GetXaxis()->SetTitle("Mass (GeV)");
        hist->GetYaxis()->SetTitle("N frac");
        hist->GetXaxis()->SetRangeUser(55, 115);

        if (i == 3 || i == 7 || i == 11 || i == 15) {
            auto [hist_data, label_data] = histograms_data[i / 4];
            tdrDraw(hist_data, "Pz", kFullCircle, kPink-9);
            hist_data->SetMarkerSize(1);

            TLegend *leg = tdrLeg(0.8, 0.8 - 0.05 * 2, 0.9, 0.82);
            leg->AddEntry(hist, "MC", "FPLE");
            leg->AddEntry(hist_data, "DATA", "PLE");
        }

        TLatex *tex = new TLatex();
        tex->SetNDC();
        tex->SetTextSize(0.045);
        tex->DrawLatex(0.17, 0.85, label);

        gPad->Update();
    }

    // Save the canvas as a .pdf file
    c3->SaveAs("pdf/MCvsDATA_Masses_loop.pdf");
}