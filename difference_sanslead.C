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

void difference_sanslead() {
// Open the ROOT file containing the histograms
TFile *file = new TFile("output_y.root", "READ");
// Retrieve the histograms

string vq[] = {"d", "u", "s", "c", "b", "g"};
int nq = sizeof(vq) / sizeof(vq[0]);

string vc[] = {"ch", "nh", "ne"};
int nc = sizeof(vc) / sizeof(vc[0]);

string vxvar[] = {"ptcand", "ptlead"};
int nxvar = sizeof(vxvar) / sizeof(vxvar[0]);

string vxvar_name[] = {"gencand", "genleadcand"};
int nxvar_name = sizeof(vxvar_name) / sizeof(vxvar_name[0]);

string vyvar[] = {"flc", "fln", "fle", "fhc", "fhn", "fhe"};
int nyvar = sizeof(vyvar) / sizeof(vyvar[0]);

std::map < string, int > mcolor;

mcolor["ch"] = kRed-7;
mcolor["nh"] = kGreen-6;
mcolor["ne"] = kBlue-6;

std::map < string, string > mleg;

mleg["ch"] = "#splitline{Charged}{Hadrons}";
mleg["nh"] = "#splitline{Neutral}{Hadrons}";
mleg["ne"] = "Photons";


std::map < string, TH1D* > mh;
std::map< string, TH1D*> mhclone;
std::map< string, TH1D*> mhsubtract;

setTDRStyle();
lumi_136TeV = "Run3";
extraText = "Private";

for (int iq = 0; iq != nq; ++ iq) {
    const char *cq = vq[iq].c_str();
        for (int ix1 = 0; ix1 != nxvar; ++ ix1) {
            const char *cx1 = vxvar[ix1].c_str();
            for (int ix2 = 0; ix2 != nxvar; ++ix2) {
            if (vxvar[ix1] == "ptcand" && vxvar[ix2] == "ptlead") {
                const char *cx2 = vxvar[ix2].c_str();
                const char *cx_name = vxvar_name[ix1].c_str();
                //if (vxvar[ix] == "ptcand"){
                vector<float> range;
                    TH1D *h = tdrHist(Form("h1_%s,%s-%s",cq,cx1,cx2),Form("%s N fraction %s-%s",cq,cx1,cx2),-0.5 + 1e-4,1.15 -1e-4,Form("p_{T, %s} (GeV)",cx_name),4,100);
                    TCanvas *c = tdrCanvas(Form("c1_%s,%s-%s",cq,cx1,cx2),h,8,kSquare);
                    c->SetLogx();
                    TLegend *leg = tdrLeg(0.83,0.9-0.1*3,1.1,0.9);

                    //if (debug){cout << "ixloop" << ix << endl << flush;}
                    
                    for (int ic = 0; ic != nc; ++ ic) {
                        const char *cv = vc[ic].c_str();

                        string hname = Form("h_%s_%s_vs_%s", cq, cv, cx1);
                        TH1D *h = (TH1D*)file->Get(hname.c_str()); assert(h);
                        mh[hname] = h;
                        string hname_all = Form("h_all_%s_vs_%s", cq, cx1);
                        TH1D *h_all = (TH1D*)file->Get(hname_all.c_str()); assert(h_all);
                        mh[hname_all] = h_all;
                        string hrname = Form("hr_%s_%s_vs_%s", cq, cv, cx1);
                        TH1D *hc = (TH1D*)h->Clone(Form("%s",hrname.c_str()));
                        hc->Divide(hc,h_all,1,1,"b");
                        mhclone[hrname] = hc;

                        string hname2 = Form("h_%s_%s_vs_%s", cq, cv, cx2);
                        TH1D *h2 = (TH1D*)file->Get(hname2.c_str()); assert(h2);
                        mh[hname2] = h2;
                        string hname_all2 = Form("h_all_%s_vs_%s", cq, cx2);
                        TH1D *h_all2 = (TH1D*)file->Get(hname_all2.c_str()); assert(h_all2);
                        mh[hname_all2] = h_all2;
                        string hrname2 = Form("hr_%s_%s_vs_%s", cq, cv, cx2);
                        TH1D *hc2 = (TH1D*)h2->Clone(Form("%s",hrname2.c_str()));
                        hc2->Divide(hc2,h_all2,1,1,"b");
                        mhclone[hrname2] = hc2;

                        hc->Add(hc2, -1);
                        vector<int> draw;
                        vector<float> size;
                        if (vc[ic] == "ch"){draw = {kFullSquare,kRed};size = {1.5};}
                        if (vc[ic] == "nh"){draw = {kFullCircle,kGreen+2};size = {1.5};}
                        if (vc[ic] == "ne"){draw = {kFullDiamond,kBlue};size = {1.75};}

                        tdrDraw(hc,"histe", draw[0],draw[1],kSolid,-1,kNone);
                        hc->SetMarkerSize(size[0]);
                        leg->AddEntry(mhclone[hrname], mleg[cv].c_str(), "ple");
                        //leg->SetY1NDC(leg->GetY1NDC()-0.07);
                        leg->SetTextSize(0.035);
                    }

                    string hname = Form("h_%s_vs_%s", cq, cx1);
                    string hname2 = Form("h_%s_vs_%s", cq, cx2);

                    gPad->SetBottomMargin(0.14);
                    gPad->SetRightMargin(0.175);
                    gPad->Update();

                    TLatex *tex1 = new TLatex();
                    tex1->SetNDC(); tex1->SetTextSize(0.045);
                    tex1->DrawLatex(0.17,0.8,"|#eta| < 1.3");
                    tex1->DrawLatex(0.17,0.75,"80 < p_{T,genjet} < 100 GeV");
                    reverseLegend(leg);
                    c->RedrawAxis();
                    c->Modified();
                    c->Update();
                    c->SaveAs(Form("pdf/difference_%s,%s-%s.pdf",cq,cx1,cx2));
            
            }
            }
        }
}
} // void fraction