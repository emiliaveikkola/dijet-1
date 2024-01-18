#include <TH1.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include <TColor.h>
#include <iostream>
#include <string>
#include <cctype>

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
THStack *h = new THStack(("h" + input).c_str(), ("Pt fraction for " + uppercase + "; PtCand; Jet pt fraction").c_str());

// Set histogram fill colors and add to stack
hr->SetFillColor(625);
hr5->SetFillColor(410);
hr3->SetFillColor(593);

// Add histograms to the stack
h->Add(hr);
h->Add(hr3);
h->Add(hr5);

// Draw the stack
TCanvas *c1 = new TCanvas("c1", "Pt fractions", 800, 600);
c1->SetLogx();
h->Draw("histe");

// Create legend
TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
legend->AddEntry(hr5, "Photons", "f");
legend->AddEntry(hr3, "Neutral Hadrons", "f");
legend->AddEntry(hr, "Charged Hadrons", "f");
legend->Draw();
// Assuming the x-axis categories are correctly set when histograms were created
// If you need to set labels for the x-axis categories, do it here

// Update the canvas to reflect changes
c1->Modified();
c1->Update();

// Do not close the file if you want to interact with the histograms further
// file->Close(); // Uncomment this if you're done with the file
}