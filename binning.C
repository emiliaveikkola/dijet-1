#include <TH1.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>

void binning() {
// Open the ROOT file containing the histograms
TFile *file = new TFile("output.root", "READ");
// Retrieve the histograms
TH1D *h_d = (TH1D*)file->Get("h_d");
TH1D *h_d3 = (TH1D*)file->Get("h_d3");
TH1D *h_d5 = (TH1D*)file->Get("h_d5");
TH1D *h_dall = (TH1D*)file->Get("h_dall");

// Normalize the histograms to percentages
int nDjet = h_d->GetEntries();
int nD3jet = h_d3->GetEntries();
int nD5jet = h_d5->GetEntries();
int nDall = h_dall->GetEntries();

TH1D *hrd = (TH1D*)h_d->Clone("hrd");
TH1D *hrd3 = (TH1D*)h_d3->Clone("hrd3");
TH1D *hrd5 = (TH1D*)h_d5->Clone("hrd5");

hrd->Divide(h_dall);
hrd3->Divide(h_dall);
hrd5->Divide(h_dall);

double x1 = 0; // Set the lower edge of your interval
double x2 = 2;

double x3 = x2; // Set the lower edge of your interval
double x4 = 50;

double x5 = x4;
double x6 = 100;

double totalArea = 0;
double eachArea = 0;

// Calculate the area between bin1 and bin2
double area1 = hrd->Integral(x1, x2);
double area2 = hrd->Integral(x3, x4);
double area3 = hrd->Integral(x5, x6);

totalArea = area1 + area2 + area3;
eachArea = totalArea* 1/3;

// Print the area
std::cout << "Area1 of the histogram between " << x1 << " and " << x2 << " is: " << area1 << std::endl;
std::cout << "Area2 of the histogram between " << x3 << " and " << x4 << " is: " << area2 << std::endl;
std::cout << "Area3 of the histogram between " << x5 << " and " << x6 << " is: " << area3 << std::endl;
std::cout << "Total are of the histograms between " << x1 << " and " << x6 << " is: " << totalArea << std::endl;
std::cout << "Equal areas for histograms are " << eachArea << std::endl;



}