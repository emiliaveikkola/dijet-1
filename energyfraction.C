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

void energyfraction() {
// Open the ROOT file containing the histograms
TFile *file = new TFile("output_x.root", "READ");
// Retrieve the histograms

string vq[] = {"d", "u", "s", "c", "b", "g"};
int nq = sizeof(vq) / sizeof(vq[0]);

string vc[] = {"ch", "nh", "ne"};
int nc = sizeof(vc) / sizeof(vc[0]);

string vxvar[] = {"ptcand", "ptjet"};
int nxvar = sizeof(vxvar) / sizeof(vxvar[0]);

string vxvar_name[] = {"gencand", "genjet"};
int nxvar_name = sizeof(vxvar_name) / sizeof(vxvar_name[0]);

string vyvar[] = {"fl", "fh"};
int nyvar = sizeof(vyvar) / sizeof(vyvar[0]);

std::map < string, int > mcolor;

mcolor["ch"] = kRed-7;
mcolor["nh"] = kGreen-6;
mcolor["ne"] = kBlue-6;

std::map < string, string > mleg;

mleg["ch"] = "Charged Hadrons";
mleg["nh"] = "Neutral Hadrons";
mleg["ne"] = "Photons";


std::map < string, TH1D* > mh;
std::map< string, TH1D*> mhclone;
std::map< string, TH1D*> mhsubtract;

setTDRStyle();
lumi_136TeV = "Run3";
extraText = "Private";

for (int iq = 0; iq != nq; ++ iq) {
    const char *cq = vq[iq].c_str();
        for (int ix = 0; ix != nxvar; ++ ix) {
            for (int iy = 0; iy != nyvar; ++ iy) {
            const char *cx = vxvar[ix].c_str();
            const char *cx_name = vxvar_name[ix].c_str();
            const char *cy = vyvar[iy].c_str();
            vector<float> range;
            if (vxvar[ix] == "ptjet"){range = {10, 5300};
            //if (vxvar[ix] == "ptcand"){range = {0.1, 100};}
                TH1D *h = tdrHist(Form("h1_%s%s%s",cq,cx,cy),Form("%s %s energy fraction",cq,cy),0,1,Form("p_{T, %s} (GeV)",cx_name),range[0],range[1]);
                TCanvas *c = tdrCanvas(Form("c1_%s%s%s",cq,cx,cy),h,8,kSquare);
                c->SetLogx();
                TLegend *leg = tdrLeg(0.6,0.9-0.05*3,0.85,0.9);

                //if (debug){cout << "ixloop" << ix << endl << flush;}
                
                for (int ic = 0; ic != nc; ++ ic) {
                    const char *cv = vc[ic].c_str();
                    //const char *pid = vpid[id].c_str();
                    string hname = Form("h_all_%s_%s%s_vs_%s", cq, cy, cv, cx);
                    TH1D *h = (TH1D*)file->Get(hname.c_str()); assert(h);
                    mh[hname] = h;

                    vector<int> draw;
                    vector<float> size;
                    if (vc[ic] == "ch"){draw = {kFullSquare,kRed};size = {1.5};}
                    if (vc[ic] == "nh"){draw = {kFullCircle,kGreen+2};size = {1.5};}
                    if (vc[ic] == "ne"){draw = {kFullDiamond,kBlue};size = {1.75};}

                    tdrDraw(h,"histe", draw[0],draw[1],kSolid,-1,kNone);
                    h->SetMarkerSize(size[0]);
                    leg->AddEntry(mh[hname], mleg[cv].c_str(), "ple");
                    //leg->SetY1NDC(leg->GetY1NDC()-0.07);
                    //leg->SetTextSize(0.035);
                }

                string hname = Form("h_all_%s_%s_vs_%s", cq, cy, cx);


                gPad->SetBottomMargin(0.14);
                //gPad->SetRightMargin(0.175);
                gPad->Update();

                TLatex *tex1 = new TLatex();
                tex1->SetNDC(); tex1->SetTextSize(0.045);
                tex1->DrawLatex(0.17,0.8,"|#eta| < 1.3");
                if (vxvar[ix] == "ptcand"){
                    tex1->DrawLatex(0.17,0.75,"80 < p_{T,genjet} < 100 GeV");
                }
                reverseLegend(leg);
                c->RedrawAxis();
                c->Modified();
                c->Update();
                c->SaveAs(Form("pdf/energyfraction_%s.pdf",hname.c_str()));
        }
            }
        }
        
    
}
} // void fraction