#include <TH1.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include <TColor.h>
#include <iostream>
#include <string>
#include <cctype>
#include "tdrstyle_mod22.C"

void fraction_a() {

// Ask the user for an input for which jet stream to compare
std::string input;
std::cout << "Enter 'u', 's' or 'd': ";
std::cin >> input;

// Check if the input is valid
if (input != "u" && input != "s" && input != "d") {
    std::cerr << "Error: Invalid input. Please enter 'u', 's', or 'd'." << std::endl; 
    return; // Exit with an error code
}

std::string num_input;
std::cout << "Enter num of bins '1' or '3': ";
std::cin >> num_input;

// Open the ROOT file containing the histograms
TFile *file = new TFile("output.root", "READ");
// Retrieve the histograms

/*
TH1D *h_new = (TH1D*)file->Get(("h_" + input + "_new").c_str());
TH1D *h_3_new = (TH1D*)file->Get(("h_" + input + "3_new").c_str());
TH1D *h_5_new = (TH1D*)file->Get(("h_" + input + "5_new").c_str());
TH1D *h_all_new = (TH1D*)file->Get(("h_" + input + "all_new").c_str());
*/
TH1D *h_new, *h_3_new, *h_5_new, *h_all_new;

if (num_input == '3') {
    h_new = (TH1D*)file->Get(("h_" + input + "_new").c_str());
    h_3_new = (TH1D*)file->Get(("h_" + input + "3_new").c_str());
    h_5_new = (TH1D*)file->Get(("h_" + input + "5_new").c_str());
    h_all_new = (TH1D*)file->Get(("h_" + input + "all_new").c_str());
} else if (num_input == '1') {
    h_new = (TH1D*)file->Get(("h_" + input + "_one").c_str());
    h_3_new = (TH1D*)file->Get(("h_" + input + "3_one").c_str());
    h_5_new = (TH1D*)file->Get(("h_" + input + "5_one").c_str());
    h_all_new = (TH1D*)file->Get(("h_" + input + "all_one").c_str());
} else {
    std::cerr << "Error: Invalid input. Please enter '1' or '3'." << std::endl; 
    return; // Exit with an error code 
}

// Normalize the histograms to percentages
/*
int nUjet = h_u_new->GetEntries();
int nU3jet = h_u3_new->GetEntries();
int nU5jet = h_u5_new->GetEntries();
int nUall = h_uall_new->GetEntries();

h_s->Scale(1./nSjet);
h_s3->Scale(1./nS3jet);
h_s5->Scale(1./nS5jet);
h_sall->Scale(1./nSall);

h_s->Scale(1,"width");
h_s3->Scale(1,"width");
h_s5->Scale(1,"width");
h_sall->Scale(1,"width");*/

TH1D *hr = (TH1D*)h_new->Clone(("hr" + input).c_str());
TH1D *hr3 = (TH1D*)h_3_new->Clone(("hr" + input + "3").c_str());
TH1D *hr5 = (TH1D*)h_5_new->Clone(("hr" + input + "5").c_str());

hr->Divide(h_new,h_all_new,1,1,"b");
hr3->Divide(h_3_new,h_all_new,1,1,"b");
hr5->Divide(h_5_new,h_all_new,1,1,"b");

std::string uppercase = input;

// Convert the input to uppercase
    for (char &c : uppercase) {
        c = std::toupper(c);
    }

// Create a stack
THStack *h = new THStack(("h" + input).c_str(), ("; p_{T,cand} (GeV); " + uppercase + " Jet p_{T} fraction").c_str());

// Set histogram fill colors and add to stack
hr->SetFillColor(625);
hr5->SetFillColor(593);
hr3->SetFillColor(410);

// Add histograms to the stack
h->Add(hr);
h->Add(hr3);
h->Add(hr5);

// Draw the stack
TCanvas *c1 = new TCanvas("c1", "p_{T} fractions", 800, 600);
c1->SetLogx();
h->Draw("hist");

gPad->SetBottomMargin(0.14);
gPad->SetRightMargin(0.17);
gPad->Update();
TH1 *hh = h->GetHistogram();
hh->GetXaxis()->SetTitleSize(0.06);
hh->GetXaxis()->SetTitleOffset(1.07);
hh->GetYaxis()->SetTitleSize(0.06);
hh->GetYaxis()->SetTitleOffset(0.7);
hh->GetXaxis()->SetLabelSize(0.05); 
hh->GetYaxis()->SetLabelSize(0.05); 

// Create legend
TLegend *leg = tdrLeg(0.83,0.8-0.06*3,1.05,0.9);
leg->AddEntry(hr5, "Photons", "f");
leg->AddEntry(hr3, "#splitline{Neutral}{Hadrons}", "f");
leg->AddEntry(hr, "#splitline{Charged}{Hadrons}", "f");
leg->SetTextSize(0.04);
leg->Draw();

TLatex *tex1 = new TLatex();
tex1->SetNDC(); tex1->SetTextSize(0.035);
tex1->DrawLatex(0.15,0.77,"|#eta| < 1.3");
tex1->DrawLatex(0.15,0.72,"60 < p_{T,jet} < 140 GeV");

TLatex *tex2 = new TLatex();
tex2->SetNDC(); tex2->SetTextSize(0.065);
tex2->DrawLatex(0.1,0.92,"CMS");

TLatex *tex3 = new TLatex();
tex3->SetNDC(); tex3->SetTextSize(0.05);
tex3->SetTextFont(42);
tex3->DrawLatex(0.61,0.92,"Run3 (13.6 TeV)");

TLatex *tex4 = new TLatex();
tex4->SetNDC(); tex4->SetTextSize(0.045);
tex4->SetTextFont(52);
tex4->DrawLatex(0.15,0.83,"Private");
// Assuming the x-axis categories are correctly set when histograms were created
// If you need to set labels for the x-axis categories, do it here

// Update the canvas to reflect changes
c1->Modified();
c1->Update();

// Do not close the file if you want to interact with the histograms further
// file->Close(); // Uncomment this if you're done with the file
}