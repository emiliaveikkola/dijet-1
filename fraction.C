#include <TH1.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include <TList.h>
#include "tdrstyle_mod22.C"

bool    debug = true;

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

void fraction() {
// Open the ROOT file containing the histograms
TFile *file = new TFile("output_z.root", "READ");
// Retrieve the histograms

string vq[] = {"d", "u", "s", "c", "b", "g"};
int nq = sizeof(vq) / sizeof(vq[0]);

string vc[] = {"ch", "nh", "ne"};
int nc = sizeof(vc) / sizeof(vc[0]);

string vxvar[] = {"ptcand", "ptjet", "ptlead"};
int nxvar = sizeof(vxvar) / sizeof(vxvar[0]);

string vxvar_name[] = {"gencand", "genjet", "genleadcand"};
int nxvar_name = sizeof(vxvar_name) / sizeof(vxvar_name[0]);

string vyvar[] = {"flc", "fln", "fle", "fhc", "fhn", "fhe"};
int nyvar = sizeof(vyvar) / sizeof(vyvar[0]);

std::map < string, int > mcolor;

mcolor["ch"] = kRed-7;
mcolor["nh"] = kGreen-6;
mcolor["ne"] = kBlue-6;

std::map < string, string > mleg;

mleg["ch"] = "CH";
mleg["nh"] = "NH";
mleg["ne"] = "#gamma";


std::map < string, TH1D* > mh;
std::map< string, TH1D*> mhclone;

setTDRStyle();
lumi_136TeV = "Run3 simulation";
extraText = "Private";

for (int iq = 0; iq != nq; ++ iq) {
    for (int ix = 0; ix != nxvar; ++ ix) {
        //if (vxvar[ix] == "ptcand"){
        const char *cq = vq[iq].c_str();
        const char *cx = vxvar[ix].c_str();
        const char *cx_name = vxvar_name[ix].c_str();
        vector<float> range;
        if (vxvar[ix] == "ptjet"){range = {10, 5300};}
        if (vxvar[ix] == "ptcand"){range = {0.1, 100};}
        if (vxvar[ix] == "ptlead"){range = {6, 100};}
        TH1D *h = tdrHist(Form("h1_%s%s",cq,cx),Form("%s N fraction",cq),0 + 1e-4,1,Form("p_{T, %s} (GeV)",cx_name),range[0],range[1]);
        TCanvas *c = tdrCanvas(Form("c1_%s%s",cq,cx),h,8,11,kSquare);
        c->SetLogx();
        TLegend *leg = tdrLeg(0.89,0.9,1.1,0.92);
        THStack *hs = new THStack(Form("hs_%s%s",cq, cx), "; p_{T} (GeV); Jet N fraction");

        for (int ic = 0; ic != nc; ++ ic) {
            const char *cv = vc[ic].c_str();
            //const char *pid = vpid[id].c_str();
            string hname = Form("h_%s_%s_vs_%s", cq, cv, cx);
            TH1D *h = (TH1D*)file->Get(hname.c_str()); assert(h);
            mh[hname] = h;
            string hname_all = Form("h_all_%s_vs_%s", cq, cx);
            TH1D *h_all = (TH1D*)file->Get(hname_all.c_str()); assert(h);
            mh[hname_all] = h_all;
            string hrname = Form("hr_%s_%s_vs_%s", cq, cv, cx);
            TH1D *hc = (TH1D*)h->Clone(Form("%s",hrname.c_str()));
            mhclone[hrname] = hc;

            hc->Divide(h_all);
            
            hc->SetFillColor(mcolor[cv]);
            hs->Add(hc);
            hs->Draw("hist same");

            leg->AddEntry(mhclone[hrname], mleg[cv].c_str(), "f");
            leg->SetY1NDC(leg->GetY1NDC()-0.07);
            leg->SetTextSize(0.035);
            leg->Draw();

            //gPad->SetBottomMargin(0.14);
            //gPad->SetRightMargin(0.175);
            gPad->Update();

            TLatex *tex1 = new TLatex();
            tex1->SetNDC(); tex1->SetTextSize(0.035);
            tex1->DrawLatex(0.19,0.75,"|#eta| < 1.3");
            if (vxvar[ix] == "ptcand"){
                tex1->DrawLatex(0.19,0.7,"80 < p_{T,genjet} < 100 GeV");
            }
            if (vxvar[ix] == "ptlead"){
                tex1->DrawLatex(0.19,0.7,"80 < p_{T,genjet} < 100 GeV");
            }
            //TLatex *tex2 = new TLatex();
            //tex2->SetNDC(); tex2->SetTextSize(0.035); tex2->SetTextFont(52);
            //tex2->DrawLatex(0.155,0.86,"Private");
        } // for ic
        reverseLegend(leg);
        CMS_lumi(c, 8, 11);
        gPad->SetRightMargin(0.11);
        c->RedrawAxis();
        c->Modified();
        c->Update();
        c->SaveAs(Form("pdf/fractions_%s_%s.pdf",cq,cx));
        } //for ptcand
    //} // for ix
  } // for iq
} // void fraction