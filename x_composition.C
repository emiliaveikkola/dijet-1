#include <TH1.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include <TList.h>
#include "tdrstyle_mod22.C"

void reverseLegend(TLegend *leg) {
    if (!leg) return; // Check for null pointer

    TList *list = leg->GetListOfPrimitives();
    if (!list) return; // Check if the list is valid

    // Create a new TList to hold the reversed order temporarily
    TList *reversedList = new TList();

    for (auto obj : *list) {
    reversedList->AddFirst(obj);
    }

    // Clear the original list without deleting the objects (now owned by reversedList)
    list->Clear();

    // Move items back from the reversed list to the original list, now in reversed order
    for (auto obj : *reversedList) {
        list->Add(obj);
    }

    // Cleanup: delete the temporary reversed list, but do not delete the objects it contains
    delete reversedList;
}


void x_composition() {
// Open the ROOT file containing the histograms
TFile *file = new TFile("output_stag.root", "READ");
// Retrieve the histograms

string vq[] = {//"x_antics" "x_anticd", "x_antisb","x_antisg"
    "cs", "x_anticantib", "x_sg",  "x_anticb", "x_cb",
    "x_anticu", "x_antisu", "x_su", "x_antisantiu",
    "x_anticantiu", "x_cu","x_cg","x_antisantib",
    "x_sb", "x_cd", "x_sd", "x_cs", 
    "x_anticantis","x_anticantid"
      
};
int nq = sizeof(vq) / sizeof(vq[0]);

string vq2[] = { //"x_antiud","x_antidc","x_dg",, "x_antiug", "x_antidg"
    "ud", "x_antidb", "x_db", "x_antidantib", "x_ug",
    "x_antiuc", "x_antius","x_us","x_antiub","x_antiuantis",
    "x_antidantis", "x_antiuantic", "x_uc", "x_antids",
    "x_ud", "x_dc", "x_antiuantid", "x_ds","x_ub",
    "x_antiuantib","x_antidantic"
     
};
int nq2 = sizeof(vq2) / sizeof(vq2[0]);


std::map < string, int > mcolor;

mcolor["cs"] = kOrange+1;
mcolor["x_cg"] = kOrange+7;
mcolor["x_sg"] = kRed+1;
mcolor["x_cu"] = kPink-9;
mcolor["x_sd"] = kPink+4;
mcolor["x_sb"] = kMagenta-4;
mcolor["x_cs"] = kViolet-3;
//mcolor["x_antics"] = kViolet+2;
mcolor["x_anticantis"] = kBlue-4; //1314
mcolor["x_cd"] = kAzure+7;
mcolor["x_anticd"] = kAzure-9;
mcolor["x_anticantid"] = kCyan-7;
mcolor["x_su"] = kTeal-8;
mcolor["x_antisu"] = kTeal+1;
mcolor["x_antisantiu"] = kGreen+1;
mcolor["x_anticu"] = kSpring+6;
mcolor["x_anticantiu"] = kYellow-7;
mcolor["x_antisb"] = kOrange-9;
mcolor["x_antisantib"] = kBlack;
mcolor["x_cb"] = kGray;
mcolor["x_anticb"] = kRed;
mcolor["x_anticantib"] = kBlue;
mcolor["x_antisg"] = kGreen;




std::map < string, int > mcolor2;
mcolor2["ud"] = kYellow-7;
mcolor2["x_ug"] = kTeal+7;
mcolor2["x_dg"] = kAzure+6;
mcolor2["x_uc"] = kViolet+6;
mcolor2["x_ds"] = kPink-9;
mcolor2["x_db"] = kSpring+6;
mcolor2["x_ud"] = kRed;
mcolor2["x_us"] = kBlue+1;
mcolor2["x_dc"] = kGreen+3;
mcolor2["x_ub"] = kOrange+3;
mcolor2["x_antiud"] = kCyan+3;
mcolor2["x_antiuantid"] = kMagenta+2;
mcolor2["x_antius"] = kBlue-7;
mcolor2["x_antiuantis"] = kGreen-5;
mcolor2["x_antids"] = kRed-4;
mcolor2["x_antidantis"] = kYellow-2;
mcolor2["x_antiuc"] = kYellow+3;
mcolor2["x_antiuantic"] = kViolet-5;
mcolor2["x_antidc"] = kTeal+4;
mcolor2["x_antidantic"] = kPink+4;
mcolor2["x_antiub"] = kAzure-4;
mcolor2["x_antiuantib"] = kOrange+7;
mcolor2["x_antidb"] = kTeal-6;
mcolor2["x_antidantib"] = kViolet+3;
mcolor2["x_antiug"] = kGreen+7;
mcolor2["x_antidg"] = kRed+1;





std::map < string, string > mleg;
mleg["cs"] = "#bar{c}s, c#bar{s}";
mleg["x_cs"] = "cs";
mleg["x_sd"] = "sd";
mleg["x_cd"] = "cd";
mleg["x_su"] = "su";
mleg["x_cu"] = "cu";
mleg["x_sb"] = "sb";
mleg["x_cb"] = "cb";
mleg["x_sg"] = "sg";
mleg["x_cg"] = "cg";
mleg["x_antics"] = "antics";
mleg["x_anticantis"] = "anticantis";
mleg["x_antisd"] = "antisd";
mleg["x_antisantid"] = "antisantid";
mleg["x_anticd"] = "anticd";
mleg["x_anticantid"] = "anticantid";
mleg["x_antisu"] = "antisu";
mleg["x_antisantiu"] = "antisantiu";
mleg["x_anticu"] = "anticu";
mleg["x_anticantiu"] = "anticantiu";
mleg["x_antisb"] = "antisb";
mleg["x_antisantib"] = "antisantib";
mleg["x_anticb"] = "anticb";
mleg["x_anticantib"] = "anticantib";
mleg["x_antisg"] = "antisg";
mleg["x_antiuc"] = "antiuc";
mleg["x_antiub"] = "antiub";
mleg["x_antiug"] = "antiug";
mleg["x_antidg"] = "antidg";

std::map < string, string > mleg2;
mleg2["ud"] = "ud";
mleg2["x_ud"] = "x_ud";
mleg2["x_ds"] = "ds"; // corrected to match prefix convention
mleg2["x_dc"] = "dc"; // corrected to match prefix convention
mleg2["x_us"] = "us"; // corrected to match prefix convention
mleg2["x_uc"] = "uc"; // corrected to match prefix convention
mleg2["x_ub"] = "ub";
mleg2["x_db"] = "db";
mleg2["x_ug"] = "ug";
mleg2["x_dg"] = "dg";
mleg2["x_antiud"] = "anti-ud";
mleg2["x_antiuantid"] = "anti-uantid";
mleg2["x_antius"] = "anti-us";
mleg2["x_antiuantis"] = "anti-uantis";
mleg2["x_antids"] = "anti-ds";
mleg2["x_antidantis"] = "anti-dantis";
mleg2["x_antiuc"] = "anti-uc";
mleg2["x_antiuantic"] = "anti-uantic";
mleg2["x_antidc"] = "anti-dc";
mleg2["x_antidantic"] = "anti-dantic";
mleg2["x_antiub"] = "anti-ub";
mleg2["x_antiuantib"] = "anti-uantib";
mleg2["x_antidb"] = "anti-db";
mleg2["x_antidantib"] = "anti-dantib";
mleg2["x_antiug"] = "anti-ug";
mleg2["x_antidg"] = "anti-dg";


std::map < string, TH1D* > mh;
std::map < string, TH1D* > mh2;

setTDRStyle();
lumi_136TeV = "Run3 simulation";
extraText = "Private";

        TH1D *h1 = tdrHist("h1","N", 450e3,900e3,"",0,7);
        //h1->GetXaxis()->SetBinLabel(1, "X composition");
        TCanvas *c = tdrCanvas("c",h1,8,11,kSquare);
        h1->GetXaxis()->SetBinLabel(1, "cs");
        h1->GetXaxis()->SetBinLabel(2, "ud");
        h1->GetXaxis()->SetBinLabel(3, "cd");
        h1->GetXaxis()->SetBinLabel(4, "us");
        h1->GetXaxis()->SetBinLabel(5, "cb");
        h1->GetXaxis()->SetBinLabel(6, "ub");
        h1->GetXaxis()->SetBinLabel(7, "x");

        //c->SetLogy();
        TLegend *leg = tdrLeg(0.85,0.9-0.05*17,1.1,0.92);
        TLegend *leg2 = tdrLeg(0.49,0.9-0.05*10,0.7,0.92);
        TLegend *leg3 = tdrLeg(0.49,0.9-0.05*5,0.7,0.92);
        THStack *hs = new THStack("hs", "; ; ");
        THStack *hu = new THStack("hu", "; ; ");
        THStack *hx = new THStack("hx", "; ; ");

        TH1D *h_cd = (TH1D*)file->Get("h_cd");
        TH1D *h_us = (TH1D*)file->Get("h_us");
        TH1D *h_cb = (TH1D*)file->Get("h_cb");
        TH1D *h_ub = (TH1D*)file->Get("h_ub");
        TH1D *h_x_x = (TH1D*)file->Get("h_x_x");
        TH1D *h_x_gg = (TH1D*)file->Get("h_x_gg");

        for (int iq = 0; iq != nq; ++ iq) {
        const char *cq = vq[iq].c_str();
        string hname = Form("h_%s", cq);
        TH1D *h_cs = (TH1D*)file->Get(hname.c_str()); assert(h_cs);
        mh[hname] = h_cs;
        h_cs->SetFillColor(mcolor[cq]);
        leg->AddEntry(mh[hname], mleg[cq].c_str(), "f");
        hs->Add(h_cs);
        } // for iq
        hs->Draw("hist same");

        for (int iq = 0; iq != nq2; ++ iq) {
        const char *cq2 = vq2[iq].c_str();
        string hname2 = Form("h_%s", cq2);
        TH1D *h_ud = (TH1D*)file->Get(hname2.c_str()); assert(h_ud);
        mh2[hname2] = h_ud;
        h_ud->SetFillColor(mcolor2[cq2]);
        if (vq2[iq] != "x_uc" && vq2[iq] != "x_dc" && 
            vq2[iq] != "x_us" && vq2[iq] != "x_ds" &&
            vq2[iq] != "x_antiuc" && vq2[iq] != "x_antidc" &&
            vq2[iq] != "x_antius" && vq2[iq] != "x_antids"){
            leg->AddEntry(mh2[hname2], mleg2[cq2].c_str(), "f");
        }
        hu->Add(h_ud);
        } // for iq2
        hu->Draw("hist same");          
        
        h_cd->SetFillColor(kRed-7);
        h_cd->Draw("hist same");


        h_us->SetFillColor(kRed-7);
        h_us->Draw("hist same");

  
        h_cb->SetFillColor(kRed-7);
        h_cb->Draw("hist same");


        h_ub->SetFillColor(kRed-7);
        h_ub->Draw("hist same");

        h_x_gg->SetFillColor(kRed-7);
        h_x_x->SetFillColor(kGreen-7);
        hx->Add(h_x_x);
        hx->Add(h_x_gg);

        hx->Draw("hist same");
        cout << "here" << endl << flush;

        leg->SetY1NDC(leg->GetY1NDC()-0.05);
        leg->SetTextSize(0.015);
        leg->Draw();

        leg2->SetY1NDC(leg2->GetY1NDC()-0.05);
        leg2->SetTextSize(0.015);
        leg2->Draw();


        
        gPad->Update();

        TLatex *tex1 = new TLatex();
        tex1->SetNDC(); tex1->SetTextSize(0.015);
        //tex1->DrawLatex(0.19,0.75,"|#eta| < 1.3");

        reverseLegend(leg);
        reverseLegend(leg2);
        CMS_lumi(c, 8, 11);
        gPad->SetRightMargin(0.15);
        c->RedrawAxis();
        c->Modified();
        c->Update();
        c->SaveAs("pdf/x_composition.pdf");

} // void fraction2