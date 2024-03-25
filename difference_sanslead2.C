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

void difference_sanslead2() {
// Open the ROOT file containing the histograms
TFile *file = new TFile("output_y.root", "READ");
// Retrieve the histograms

string vpid[] = {"pionp", "pionm", "kaonp", "kaonm",//"lambdap", "lambdam","kaon0"
                   "sigmapm",//"sigma0", "sigmap", "sigmam", "sigmaantip", "sigmaantim",
                    //"pion0","xi0","xim","antixi0","antixim","omegam","antiomegam",
                   "proton", "antiproton", "neutron", "antineutron","kaon0l", "kaon0s", "lambdapm","xiomega",
                   "photon","electron", "muon"}; //,"positron", "antimuon"
  int npid = sizeof(vpid) / sizeof(vpid[0]);

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

mcolor["kaon0l"] = kGreen-6;
mcolor["kaon0s"] = kGreen-7;
mcolor["kaonp"] = kRed-7;
mcolor["kaonm"] = kRed-6;
mcolor["lambdapm"] = kTeal-9;
//mcolor["lambdam"] = kTeal-9;
mcolor["sigmapm"] = kMagenta-10;
//mcolor["sigmam"] = kMagenta-10;
//mcolor["sigmaantip"] = kMagenta-10;
//mcolor["sigmaantim"] = kMagenta-10;
mcolor["pionp"] = kRed-10;
mcolor["pionm"] = kRed-9;
mcolor["xiomega"] = kAzure+8;
//mcolor["xim"] = kRed-9;
//mcolor["antixi0"] = kRed-10;
//mcolor["antixim"] = kRed-9;
//mcolor["omegam"] = kRed-10;
//mcolor["antiomegam"] = kRed-9;
mcolor["proton"] = kMagenta-9;
mcolor["antiproton"] = kMagenta-7;
mcolor["neutron"] = kGreen-10;
mcolor["antineutron"] = kGreen-9;
mcolor["electron"] = kCyan-9;
mcolor["muon"] = kOrange-9;
//mcolor["positron"] = kCyan-9;
//mcolor["antimuon"] = kCyan-9;
mcolor["photon"] = kBlue-9;

std::map < string, int > mmarker;

mmarker["kaon0l"] = kFullTriangleUp;
mmarker["kaon0s"] = kOpenTriangleUp;
mmarker["kaonp"] = kFullSquare;
mmarker["kaonm"] = kOpenSquare;
mmarker["lambdapm"] = kOpenStar;
//mmarker["lambdam"] = kTeal-9;
mmarker["sigmapm"] = kFullStar;
//mmarker["sigmam"] = kMagenta-10;
//mmarker["sigmaantip"] = kMagenta-10;
//mmarker["sigmaantim"] = kMagenta-10;
mmarker["pionp"] = kFullCircle;
mmarker["pionm"] = kOpenCircle;
mmarker["xiomega"] = kStar;
//mmarker["xim"] = kRed-9;
//mmarker["antixi0"] = kRed-10;
//mmarker["antixim"] = kRed-9;
//mmarker["omegam"] = kRed-10;
//mmarker["antiomegam"] = kRed-9;
mmarker["proton"] = kFullCross;
mmarker["antiproton"] = kOpenCross;
mmarker["neutron"] =  kFullCrossX;
mmarker["antineutron"] =  kOpenCrossX;
mmarker["electron"] = kFullDoubleDiamond;
mmarker["muon"] = kOpenDoubleDiamond;
//mmarker["positron"] = kCyan-9;
//mmarker["antimuon"] = kCyan-9;
mmarker["photon"] = kFullDiamond;

std::map < string, string > mleg;

mleg["kaon0l"] = "K^{0}_{L}";
mleg["kaon0s"] = "K^{0}_{S}";
mleg["kaonp"] = "K^{+}";
mleg["kaonm"] = "K^{-}";
mleg["lambdapm"] = "#Lambda^{#pm}";
//mleg["lambdam"] = "#Lambda^{-}";
mleg["sigmapm"] = "#Sigma^{#pm}";
//mleg["sigmam"] = "#Sigma^{-}";
//mleg["sigmaantip"] = "#bar{#Sigma}^{+}";
//mleg["sigmaantim"] = "#bar{#Sigma}^{-}";
mleg["pionp"] = "#pi^{+}";
mleg["pionm"] = "#pi^{-}";
mleg["xiomega"] = "#Xi, #Omega";
//mleg["xim"] = "#Xi^{-}";
//mleg["antixi0"] = "#bar{#Xi}^{0}";
//mleg["antixim"] = "#bar{#Xi}^{-}";
//mleg["omegam"] = "#Omega^{-}";
//mleg["antiomegam"] = "#bar{#Omega}^{-}";
mleg["proton"] = "p";
mleg["antiproton"] = "#bar{p}";
mleg["neutron"] = "n";
mleg["antineutron"] = "#bar{n}";
mleg["electron"] = "e, e^{+}";
mleg["muon"] = "#mu, #mu^{-}";
//mleg["positron"] = "e^{+}";
//mleg["antimuon"] = "#mu^{+}";
mleg["photon"] = "#gamma";


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
            const char *cx2 = vxvar[ix2].c_str();
            const char *cx_name = vxvar_name[ix1].c_str();
                if (vxvar[ix1] == "ptcand" && vxvar[ix2] == "ptlead") {
                    vector<float> range;
                    TH1D *h1 = tdrHist(Form("h1_%s,%s-%s",cq,cx1,cx2),Form("%s N fraction %s-%s",cq,cx1,cx2),-0.5 + 1e-4,0.4 -1e-4,Form("p_{T, %s} (GeV)",cx_name),4,100);
                    TCanvas *c = tdrCanvas(Form("c1_%s,%s-%s",cq,cx1,cx2),h1,8,kSquare);
                    c->SetLogx();
                    TLegend *leg = tdrLeg(0.83,0.95-0.05*16,1.1,0.9);
                    for (int id = 0; id != npid; ++ id) {
                        const char *pid = vpid[id].c_str();
                        string hname = Form("h_%s_%s_vs_%s", pid, cq, cx1);
                        TH1D *h = (TH1D*)file->Get(hname.c_str()); assert(h);
                        mh[hname] = h;
                        string hname_all = Form("h_all_%s_vs_%s", cq, cx1);
                        TH1D *h_all = (TH1D*)file->Get(hname_all.c_str()); assert(h_all);
                        mh[hname_all] = h_all;
                        string hrname = Form("hr_%s_%s_vs_%s", pid, cq, cx1);
                        TH1D *hc = (TH1D*)h->Clone(Form("%s",hrname.c_str()));
                        hc->Divide(hc,h_all,1,1,"b");
                        mhclone[hrname] = hc;

                        string hname2 = Form("h_%s_%s_vs_%s", pid, cq, cx2);
                        TH1D *h2 = (TH1D*)file->Get(hname2.c_str()); assert(h2);
                        mh[hname2] = h2;
                        string hname_all2 = Form("h_all_%s_vs_%s", cq, cx2);
                        TH1D *h_all2 = (TH1D*)file->Get(hname_all2.c_str()); assert(h_all2);
                        mh[hname_all2] = h_all2;
                        string hrname2 = Form("hr_%s_%s_vs_%s", pid, cq, cx2);
                        TH1D *hc2 = (TH1D*)h2->Clone(Form("%s",hrname2.c_str()));
                        hc2->Divide(hc2,h_all2,1,1,"b");
                        mhclone[hrname2] = hc2;

                        hc->Add(hc2, -1);

                        tdrDraw(hc,"histe", mmarker[pid], mcolor[pid],kSolid,-1,kNone);
                        hc->SetMarkerSize(1.75);
                        leg->AddEntry(mhclone[hrname], mleg[pid].c_str(), "ple");
                        //leg->SetY1NDC(leg->GetY1NDC()-0.07);
                        leg->SetTextSize(0.035);
                    }
                
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
                    c->SaveAs(Form("pdf/difference2_%s,%s-%s.pdf",cq,cx1,cx2));
                }
            }
        }        
    }   
} // void fraction