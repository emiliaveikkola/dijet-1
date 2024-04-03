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

void fraction2() {
// Open the ROOT file containing the histograms
TFile *file = new TFile("output_z.root", "READ");
// Retrieve the histograms

  string vpid[] = {"pionp", "pionm", "kaonp", "kaonm",//"lambdap", "lambdam","kaon0"
                   "sigmapm",//"sigma0", "sigmap", "sigmam", "sigmaantip", "sigmaantim",
                    //"pion0","xi0","xim","antixi0","antixim","omegam","antiomegam",
                   "proton", "antiproton", "neutron", "antineutron","kaon0l", "kaon0s", "lambdapm","xiomega",
                   "photon","electron", "muon"}; //,"positron", "antimuon"
  int npid = sizeof(vpid) / sizeof(vpid[0]);

string vq[] = {"d", "u", "s", "c", "b", "g"};
int nq = sizeof(vq) / sizeof(vq[0]);

string vxvar[] = {"ptcand", "ptjet", "ptlead"};
int nxvar = sizeof(vxvar) / sizeof(vxvar[0]);

string vxvar_name[] = {"gencand", "genjet", "genleadcand"};
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

/*for (int iq = 0; iq !=nq; ++iq){
    const char *cq = vq[iq].c_str();
    string s = Form("h_%sall_cand",cq);
    TH1D *h = (TH1D*)file->Get(s.c_str()); assert(h);
    mhclone[s] = (TH1D*)h->Clone(Form("%s",s.c_str()));
}
*/
setTDRStyle();
lumi_136TeV = "Run3";
extraText = "Private";

for (int iq = 0; iq != nq; ++ iq) {
    for (int ix = 0; ix != nxvar; ++ ix) {
        //if (vxvar[ix] == "ptcand"){
        const char *cq = vq[iq].c_str();
        const char *cx = vxvar[ix].c_str();
        const char *cx_name = vxvar_name[ix].c_str();
        vector<float> range;
        if (vxvar[ix] == "ptjet"){range = {10, 5300};}
        if (vxvar[ix] == "ptcand"){range = {6, 100};}
        if (vxvar[ix] == "ptlead"){range = {6, 100};}
        TH1D *h = tdrHist(Form("h1_%s%s",cq,cx),Form("%s N fraction",cq),0 + 1e-4,1,Form("p_{T, %s} (GeV)",cx_name),range[0],range[1]);
        TCanvas *c = tdrCanvas(Form("c1_%s%s",cq,cx),h,8,kSquare);
        c->SetLogx();
        TLegend *leg = tdrLeg(0.89,0.9,1.1,0.92);
        THStack *hs = new THStack(Form("hs_%s%s",cq,cx), "; p_{T} (GeV); Jet N fraction");

        for (int id = 0; id != npid; ++ id) {
            const char *pid = vpid[id].c_str();
            string hname = Form("h_%s_%s_vs_%s", pid, cq, cx);
            TH1D *h = (TH1D*)file->Get(hname.c_str()); assert(h);
            mh[hname] = h;
            string hname_all = Form("h_all_%s_vs_%s", cq, cx);
            TH1D *h_all = (TH1D*)file->Get(hname_all.c_str()); assert(h);
            mh[hname_all] = h_all;
            string hrname = Form("hr_%s_%s_vs_%s", pid, cq, cx);
            TH1D *hc = (TH1D*)h->Clone(Form("%s",hrname.c_str()));
            mhclone[hrname] = hc;
            /*
            if (id == npid-1) {
                TH1D *hemu = (TH1D*)h->Clone(Form("%s_%s","emu",cq));
                hemu->Reset();
                TH1D *hsigma = (TH1D*)h->Clone(Form("%s_%s","sigma",cq));
                hsigma->Reset();
                TH1D *hlambda = (TH1D*)h->Clone(Form("%s_%s","lambda",cq));
                hlambda->Reset();
                string hrelectron = Form("hr_electron_%s_vs_ptcand", cq);
                string hrmuon = Form("hr_muon_%s_vs_ptcand", cq);
                string hrsigmap = Form("hr_sigmap_%s_vs_ptcand", cq);
                string hrsigmam = Form("hr_sigmam_%s_vs_ptcand", cq);
                string hrlambdap = Form("hr_lambdap_%s_vs_ptcand", cq);
                string hrlambdam = Form("hr_lambdam_%s_vs_ptcand", cq);
                string hrall = Form("hr%sall_cand", cq);
                TH1D *hmu = mhclone[hrmuon]; assert(hmu);
                TH1D *he = mhclone[hrelectron]; assert(he);
                TH1D *hsigmap = mhclone[hrsigmap]; assert(hsigmap);
                TH1D *hsigmam = mhclone[hrsigmam]; assert(hsigmam);
                TH1D *hlambdap = mhclone[hrlambdap]; assert(hlambdap);
                TH1D *hlambdam = mhclone[hrlambdam]; assert(hlambdam);
                hemu->Add(hmu);
                hemu->Add(he);
                mhclone["hrelectron"] = hemu;
                hsigma->Add(hsigmam);
                hsigma->Add(hsigmap);
                mhclone["hrsigmap"] = hsigma;
                hlambda->Add(hlambdam);
                hlambda->Add(hlambdap);
                mhclone["hrlambdap"] = hlambda;
            } //id == npid-1
            */
            //string hrefname = Form("h_all_%s_%s",cq,cx);
            //TH1D *h_all =  mhclone[hrefname]; assert(h_all);
            hc->Divide(h_all);
            
            hc->SetFillColor(mcolor[pid]);
            hs->Add(hc);
            hs->Draw("hist same");


            leg->AddEntry(mhclone[hrname], mleg[pid].c_str(), "f");
            leg->SetY1NDC(leg->GetY1NDC()-0.05);
            leg->SetTextSize(0.035);

            gPad->SetBottomMargin(0.14);
            gPad->SetRightMargin(0.12);
            gPad->Update();

            TLatex *tex1 = new TLatex();
            tex1->SetNDC(); tex1->SetTextSize(0.045);
            tex1->DrawLatex(0.17,0.8,"|#eta| < 1.3");
            if (vxvar[ix] == "ptcand"){
                tex1->DrawLatex(0.17,0.75,"80 < p_{T,genjet} < 100 GeV");
            }
            if (vxvar[ix] == "ptlead"){
                tex1->DrawLatex(0.17,0.75,"84 < p_{T,leadjet} < 114 GeV");
            }
            
                TLatex *tex2 = new TLatex();
                tex2->SetNDC(); tex2->SetTextSize(0.045); tex2->SetTextFont(52);
                tex2->DrawLatex(0.155,0.86,"Private");
            
        } // for id
        reverseLegend(leg);
        c->RedrawAxis();
        c->Modified();
        c->Update();
        c->SaveAs(Form("pdf/fractions2_%s_%s.pdf",cq,cx));
        //} //for ptcand
    } // for ix
  } // for iq
} // void fraction2