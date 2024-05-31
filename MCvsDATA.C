#include <TMath.h>
#include <TF1.h>
#include <TH1F.h>
#include <TH1D.h>
#include <TProfile2D.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include <TStyle.h>
#include <iostream>
#include <algorithm>
#include "tdrstyle_mod22.C"

void NormalizeByColumns(TH2D* h2D) {
    // Get the number of bins along the axes
    Int_t numBinsX = h2D->GetNbinsX();
    Int_t numBinsY = h2D->GetNbinsY();

    // Loop over each column (y-bin) to calculate the sum of bin contents and normalize
    for (Int_t j = 1; j <= numBinsY; ++j) {
        Double_t sumColumn = 0.0;

        // Calculate the sum of the column
        for (Int_t i = 1; i <= numBinsX; ++i) {
            sumColumn += h2D->GetBinContent(i, j);
        }

        // Normalize the column
        if (sumColumn != 0) {
            for (Int_t i = 1; i <= numBinsX; ++i) {
                Double_t content = h2D->GetBinContent(i, j);
                h2D->SetBinContent(i, j, content / sumColumn);
            }
        }
    }
}

void NormalizeByRows(TH2D* h2D) {
    // Get the number of bins along the axes
    Int_t numBinsX = h2D->GetNbinsX();
    Int_t numBinsY = h2D->GetNbinsY();

    // Loop over each row (x-bin) to calculate the sum of bin contents and normalize
    for (Int_t i = 1; i <= numBinsX; ++i) {
        Double_t sumRow = 0.0;

        // Calculate the sum of the row
        for (Int_t j = 1; j <= numBinsY; ++j) {
            sumRow += h2D->GetBinContent(i, j);
        }

        // Normalize the row
        if (sumRow != 0) {
            for (Int_t j = 1; j <= numBinsY; ++j) {
                Double_t content = h2D->GetBinContent(i, j);
                h2D->SetBinContent(i, j, content / sumRow);
            }
        }
    }
}

void PrintBinContents(TH2D* h2D) {
    Int_t numBinsX = h2D->GetNbinsX();
    Int_t numBinsY = h2D->GetNbinsY();
    for (Int_t i = 1; i <= numBinsX; ++i) {
        for (Int_t j = 1; j <= numBinsY; ++j) {
            Double_t content = h2D->GetBinContent(i, j);
            std::cout << "Bin (" << i << ", " << j << "): " << content << std::endl;
        }
    }
}

void MCvsDATA() {
    TFile *file = new TFile("output_stag_DATA.root", "READ");

    TH2D *hJetFlavourPairMCDATA = (TH2D*)file->Get("hJetFlavourPairMCDATA");
    TProfile2D *hMassFlavorPairs_DATAMC = (TProfile2D*)file->Get("hMassFlavorPairs_DATAMC");
    setTDRStyle();

    // Clone the original histogram to preserve the original data for the second normalization
    TH2D *hJetFlavourPairMCDATA_ByRows = (TH2D*)hJetFlavourPairMCDATA->Clone("hJetFlavourPairMCDATA_ByRows");
    TH2D *hJetFlavourPairMCDATA_ByColumns = (TH2D*)hJetFlavourPairMCDATA->Clone("hJetFlavourPairMCDATA_ByColumns");

    // Normalize by rows
    NormalizeByRows(hJetFlavourPairMCDATA_ByRows);

    std::cout << "\nBin contents after row normalization:" << std::endl;
    PrintBinContents(hJetFlavourPairMCDATA_ByRows);

    // Normalize by columns
    NormalizeByColumns(hJetFlavourPairMCDATA_ByColumns);

    std::cout << "\nBin contents after column normalization:" << std::endl;
    PrintBinContents(hJetFlavourPairMCDATA_ByColumns);


    // Set bin labels for X axis
    hJetFlavourPairMCDATA_ByRows->GetXaxis()->SetBinLabel(1, "cs");
    hJetFlavourPairMCDATA_ByRows->GetXaxis()->SetBinLabel(2, "ud");
    hJetFlavourPairMCDATA_ByRows->GetXaxis()->SetBinLabel(3, "x");

    hJetFlavourPairMCDATA_ByColumns->GetXaxis()->SetBinLabel(1, "cs");
    hJetFlavourPairMCDATA_ByColumns->GetXaxis()->SetBinLabel(2, "ud");
    hJetFlavourPairMCDATA_ByColumns->GetXaxis()->SetBinLabel(3, "x");

    hMassFlavorPairs_DATAMC->GetXaxis()->SetBinLabel(1, "cs");
    hMassFlavorPairs_DATAMC->GetXaxis()->SetBinLabel(2, "ud");
    hMassFlavorPairs_DATAMC->GetXaxis()->SetBinLabel(3, "x");

    // Set bin labels for Y axis
    hJetFlavourPairMCDATA_ByRows->GetYaxis()->SetBinLabel(1, "cs");
    hJetFlavourPairMCDATA_ByRows->GetYaxis()->SetBinLabel(2, "ud");
    hJetFlavourPairMCDATA_ByRows->GetYaxis()->SetBinLabel(3, "x");

    hJetFlavourPairMCDATA_ByColumns->GetYaxis()->SetBinLabel(1, "cs");
    hJetFlavourPairMCDATA_ByColumns->GetYaxis()->SetBinLabel(2, "ud");
    hJetFlavourPairMCDATA_ByColumns->GetYaxis()->SetBinLabel(3, "x");

    hMassFlavorPairs_DATAMC->GetYaxis()->SetBinLabel(1, "cs");
    hMassFlavorPairs_DATAMC->GetYaxis()->SetBinLabel(2, "ud");
    hMassFlavorPairs_DATAMC->GetYaxis()->SetBinLabel(3, "x");

    // Set axis titles
    hJetFlavourPairMCDATA_ByRows->GetXaxis()->SetTitle("MC");
    hJetFlavourPairMCDATA_ByRows->GetYaxis()->SetTitle("DATA");

    hJetFlavourPairMCDATA_ByColumns->GetXaxis()->SetTitle("MC");
    hJetFlavourPairMCDATA_ByColumns->GetYaxis()->SetTitle("DATA");


    lumi_136TeV = "Run3 simulation";
    extraText = "Private";

    // Create canvas and save the row-normalized histogram
    TH1D *h1 = tdrHist("h1", "Data", 1, 4, "MC", 1, 4);
    TCanvas *c1 = tdrCanvas("c1", h1, 8, 11, kRectangular);

    // Set the right margin of the canvas
    c1->SetRightMargin(0.15);

    // Draw the row-normalized 2D histogram
    hJetFlavourPairMCDATA_ByRows->Draw("colz");

    // Update the canvas to reflect the changes
    c1->Update();

    // Save the canvas as a .pdf file
    c1->SaveAs("pdf/MCvsDATA_ByRows.pdf");

    // Create a new canvas and save the column-normalized histogram
    TCanvas *c2 = tdrCanvas("c2", h1, 8, 11, kRectangular);

    // Set the right margin of the canvas
    c2->SetRightMargin(0.15);

    // Draw the column-normalized 2D histogram
    hJetFlavourPairMCDATA_ByColumns->Draw("colz");

    // Update the canvas to reflect the changes
    c2->Update();

    // Save the canvas as a .pdf file
    c2->SaveAs("pdf/MCvsDATA_ByColumns.pdf");



    TCanvas *c3 = tdrCanvas("c3", h1, 8, 11, kRectangular);
    c3->SetRightMargin(0.17);
    hMassFlavorPairs_DATAMC->Draw("COLZ");
    c3->Update();
    c3->SaveAs("pdf/MCvsDATA_Massgrid.pdf");

}
