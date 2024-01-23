#include <TH1.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include "tdrstyle_mod22.C"

void energyfraction() {

// Ask the user for an input for which jet stream to compare
/*std::string input;
std::cout << "Enter 'u', 's' or 'd': ";
std::cin >> input;

// Check if the input is valid
if (input != "u" && input != "s" && input != "d") {
    std::cerr << "Error: Invalid input. Please enter 'u', 's', or 'd'." << std::endl; 
    return; // Exit with an error code
}
   
// Open the ROOT file containing the histograms
TFile *file = new TFile("output.root", "READ");

TProfile *pch, *pnh, *pne;

pch = (TProfile*)file->Get(("p" + input +"ch").c_str());
pnh = (TProfile*)file->Get(("p" + input +"nh").c_str());
pne = (TProfile*)file->Get(("p" + input +"ne").c_str());*/

// Open the ROOT file containing the histograms
TFile *file = new TFile("output.root", "READ");

// Retrieve the histograms
TProfile *puch = (TProfile*)file->Get("puch");
TProfile *punh = (TProfile*)file->Get("punh");
TProfile *pune = (TProfile*)file->Get("pune");
TProfile *pdch = (TProfile*)file->Get("pdch");
TProfile *pdnh = (TProfile*)file->Get("pdnh");
TProfile *pdne = (TProfile*)file->Get("pdne");
TProfile *psch = (TProfile*)file->Get("psch");
TProfile *psnh = (TProfile*)file->Get("psnh");
TProfile *psne = (TProfile*)file->Get("psne");

/*std::string uppercase = input;

// Convert the input to uppercase
    for (char &c : uppercase) {
        c = std::toupper(c);
    }*/

// Draw the canvas
setTDRStyle();
lumi_136TeV = "Run3";
extraText = "Private";
TH1D *h1 = tdrHist("h1","U Jet energy fraction",0,1,"p_{T,genjet} (GeV)",10,5300);
TCanvas *c1 = tdrCanvas("c1",h1,8,kSquare);
c1->SetLogx();

tdrDraw(pune,"histe",kFullDiamond,kBlue,kSolid,-1,kNone);
pune->SetMarkerSize(1.75);
tdrDraw(punh,"histe",kFullCircle,kGreen+2,kSolid,-1,kNone);
punh->SetMarkerSize(1.5);
tdrDraw(puch,"histe",kFullSquare,kRed,kSolid,-1,kNone);
puch->SetMarkerSize(1.5);

// Create legend
//TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
TLegend *leg1 = tdrLeg(0.6,0.9-0.05*3,0.85,0.9);
leg1->AddEntry(pune, "Photons", "ple");
leg1->AddEntry(punh, "Neutral Hadrons", "ple");
leg1->AddEntry(puch, "Charged Hadrons", "ple");
leg1->Draw();

TLatex *tex1 = new TLatex();
tex1->SetNDC(); tex1->SetTextSize(0.045);
tex1->DrawLatex(0.17,0.8,"|#eta| < 1.3");
tex1->DrawLatex(0.17,0.75,"60 < p_{T,jet} < 140 GeV");

// Update the canvas to reflect changes
c1->RedrawAxis();
c1->Modified();
c1->Update();
c1->SaveAs("pdf/energyfractionU.pdf");

TH1D *h2 = tdrHist("h2","D Jet energy fraction",0,1,"p_{T,genjet} (GeV)",10,5300);
TCanvas *c2 = tdrCanvas("c2",h2,8,kSquare);
c2->SetLogx();

tdrDraw(pdne,"histe",kFullDiamond,kBlue,kSolid,-1,kNone);
pdne->SetMarkerSize(1.75);
tdrDraw(pdnh,"histe",kFullCircle,kGreen+2,kSolid,-1,kNone);
pdnh->SetMarkerSize(1.5);
tdrDraw(pdch,"histe",kFullSquare,kRed,kSolid,-1,kNone);
pdch->SetMarkerSize(1.5);

// Create legend
//TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
TLegend *leg2 = tdrLeg(0.6,0.9-0.05*3,0.85,0.9);
leg2->AddEntry(pdne, "Photons", "ple");
leg2->AddEntry(pdnh, "Neutral Hadrons", "ple");
leg2->AddEntry(pdch, "Charged Hadrons", "ple");
leg2->Draw();

TLatex *tex2 = new TLatex();
tex2->SetNDC(); tex2->SetTextSize(0.045);
tex2->DrawLatex(0.17,0.8,"|#eta| < 1.3");
tex2->DrawLatex(0.17,0.75,"60 < p_{T,jet} < 140 GeV");

// Update the canvas to reflect changes
c2->RedrawAxis();
c2->Modified();
c2->Update();
c2->SaveAs("pdf/energyfractionD.pdf");

TH1D *h3 = tdrHist("h3","S Jet energy fraction",0,1,"p_{T,genjet} (GeV)",10,5300);
TCanvas *c3 = tdrCanvas("c3",h3,8,kSquare);
c3->SetLogx();

tdrDraw(psne,"histe",kFullDiamond,kBlue,kSolid,-1,kNone);
psne->SetMarkerSize(1.75);
tdrDraw(psnh,"histe",kFullCircle,kGreen+2,kSolid,-1,kNone);
psnh->SetMarkerSize(1.5);
tdrDraw(psch,"histe",kFullSquare,kRed,kSolid,-1,kNone);
psch->SetMarkerSize(1.5);

// Create legend
//TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
TLegend *leg3 = tdrLeg(0.6,0.9-0.05*3,0.85,0.9);
leg3->AddEntry(psne, "Photons", "ple");
leg3->AddEntry(psnh, "Neutral Hadrons", "ple");
leg3->AddEntry(psch, "Charged Hadrons", "ple");
leg3->Draw();

TLatex *tex3 = new TLatex();
tex3->SetNDC(); tex3->SetTextSize(0.045);
tex3->DrawLatex(0.17,0.8,"|#eta| < 1.3");
tex3->DrawLatex(0.17,0.75,"60 < p_{T,jet} < 140 GeV");

// Update the canvas to reflect changes
c3->RedrawAxis();
c3->Modified();
c3->Update();
c3->SaveAs("pdf/energyfractionS.pdf");

// Do not close the file if you want to interact with the histograms further
// file->Close(); // Uncomment this if you're done with the file
}