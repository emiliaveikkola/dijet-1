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
TFile *file = new TFile("output.root", "READ");
// Retrieve the histograms

  string vpid[] = {"pionp", "pionm", "kaonp", "kaonm",//"lambdap", "lambdam","kaon0"
                   "sigmapm",//"sigma0", "sigmap", "sigmam", "sigmaantip", "sigmaantim",
                    //"pion0","xi0","xim","antixi0","antixim","omegam","antiomegam",
                   "proton", "antiproton", "neutron", "antineutron","kaon0l", "kaon0s", "lambdapm","xiomega",
                   "photon","electron", "muon"}; //,"positron", "antimuon"
  int npid = sizeof(vpid) / sizeof(vpid[0]);

string vq[] = {"d", "u", "s", "c", "b"};
int nq = sizeof(vq) / sizeof(vq[0]);

string vxvar[] = {"ptcand", "ptjet"};
int nxvar = sizeof(vxvar) / sizeof(vxvar[0]);

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
        if (vxvar[ix] == "ptcand"){
        const char *cq = vq[iq].c_str();
        const char *cx = vxvar[ix].c_str();
        TH1D *h = tdrHist(Form("h1_%s%s",cq,cx),Form("%s jet N fraction",cq),0 + 1e-4,1,"p_{T,cand} (GeV)",0.1,100);
        TCanvas *c = tdrCanvas(Form("c1_%s%s",cq,cx),h,8,kSquare);
        c->SetLogx();
        TLegend *leg = tdrLeg(0.89,0.9,1.1,0.92);
        THStack *hs = new THStack(Form("hs_%s%s",cq,cx), "; p_{T,cand} (GeV); Jet N fraction");

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
            tex1->DrawLatex(0.17,0.75,"80 < p_{T,jet} < 100 GeV");
        } // for id
        reverseLegend(leg);
        c->RedrawAxis();
        c->Modified();
        c->Update();
        c->SaveAs(Form("pdf/fractions2_%s_%s.pdf",cq,cx));
        } //for ptcand
    } // for ix
  } // for iq
} // void fraction2
  
/*
// S jets
TH1D *h_kaon0l_s_vs_ptcand = (TH1D*)file->Get("h_kaon0l_s_vs_cand");
TH1D *h_kaon0s_s_vs_cand = (TH1D*)file->Get("h_kaon0s_s_vs_cand");
TH1D *h_kaonp_s_vs_cand = (TH1D*)file->Get("h_kaonp_s_vs_cand");
TH1D *h_kaonm_s_vs_cand = (TH1D*)file->Get("h_kaonm_s_vs_cand");
//TH1D *h_kaon0_s_vs_cand = (TH1D*)file->Get("h_kaon0_s_vs_cand");
TH1D *h_pionp_s_vs_cand = (TH1D*)file->Get("h_pionp_s_vs_cand");
TH1D *h_pionm_s_vs_cand = (TH1D*)file->Get("h_pionm_s_vs_cand");
TH1D *h_pion0_s_vs_cand = (TH1D*)file->Get("h_pion0_s_vs_cand");
TH1D *h_lambda_s_vs_cand = (TH1D*)file->Get("h_lambda_s_vs_cand");
TH1D *h_sigma0_s_vs_cand = (TH1D*)file->Get("h_sigma0_s_vs_cand");
TH1D *h_sigmap_s_vs_cand = (TH1D*)file->Get("h_sigmap_s_vs_cand");
TH1D *h_sigmam_s_vs_cand = (TH1D*)file->Get("h_sigmam_s_vs_cand");
TH1D *h_proton_s_vs_cand = (TH1D*)file->Get("h_proton_s_vs_cand");
TH1D *h_antiproton_s_vs_cand = (TH1D*)file->Get("h_antiproton_s_vs_cand");
TH1D *h_neutron_s_vs_cand = (TH1D*)file->Get("h_neutron_s_vs_cand");
TH1D *h_antineutron_s_vs_cand = (TH1D*)file->Get("h_antineutron_s_vs_cand");
TH1D *h_muon_s_vs_cand = (TH1D*)file->Get("h_muon_s_vs_cand");
TH1D *h_electron_s_vs_cand = (TH1D*)file->Get("h_electron_s_vs_cand");
TH1D *h_sall_cand = (TH1D*)file->Get("h_sall_cand");
TH1D *h_s5_cand = (TH1D*)file->Get("h_s5_cand");

// U jets
TH1D *h_kaon0lu = (TH1D*)file->Get("h_kaon0lu");
TH1D *h_kaon0su = (TH1D*)file->Get("h_kaon0su");
TH1D *h_kaonpu = (TH1D*)file->Get("h_kaonpu");
TH1D *h_kaonmu = (TH1D*)file->Get("h_kaonmu");
//TH1D *h_kaon0u = (TH1D*)file->Get("h_kaon0u");
TH1D *h_pionpu = (TH1D*)file->Get("h_pionpu");
TH1D *h_pionmu = (TH1D*)file->Get("h_pionmu");
TH1D *h_pion0u = (TH1D*)file->Get("h_pion0u");
TH1D *h_lambdau = (TH1D*)file->Get("h_lambdau");
TH1D *h_sigma0u = (TH1D*)file->Get("h_sigma0u");
TH1D *h_sigmapu = (TH1D*)file->Get("h_sigmapu");
TH1D *h_sigmamu = (TH1D*)file->Get("h_sigmamu");
TH1D *h_protonu = (TH1D*)file->Get("h_protonu");
TH1D *h_antiprotonu = (TH1D*)file->Get("h_antiprotonu");
TH1D *h_neutronu = (TH1D*)file->Get("h_neutronu");
TH1D *h_antineutronu = (TH1D*)file->Get("h_antineutronu");
TH1D *h_muonu = (TH1D*)file->Get("h_muonu");
TH1D *h_electronu = (TH1D*)file->Get("h_electronu");
TH1D *h_uall_cand = (TH1D*)file->Get("h_uall_cand");
TH1D *h_u5_cand = (TH1D*)file->Get("h_u5_cand");

// D jets
TH1D *h_kaon0ld = (TH1D*)file->Get("h_kaon0ld");
TH1D *h_kaon0sd = (TH1D*)file->Get("h_kaon0sd");
TH1D *h_kaonpd = (TH1D*)file->Get("h_kaonpd");
TH1D *h_kaonmd = (TH1D*)file->Get("h_kaonmd");
//TH1D *h_kaon0d = (TH1D*)file->Get("h_kaon0d");
TH1D *h_pionpd = (TH1D*)file->Get("h_pionpd");
TH1D *h_pionmd = (TH1D*)file->Get("h_pionmd");
TH1D *h_pion0d = (TH1D*)file->Get("h_pion0d");
TH1D *h_lambdad = (TH1D*)file->Get("h_lambdad");
TH1D *h_sigma0d = (TH1D*)file->Get("h_sigma0d");
TH1D *h_sigmapd = (TH1D*)file->Get("h_sigmapd");
TH1D *h_sigmamd = (TH1D*)file->Get("h_sigmamd");
TH1D *h_protond = (TH1D*)file->Get("h_protond");
TH1D *h_antiprotond = (TH1D*)file->Get("h_antiprotond");
TH1D *h_neutrond = (TH1D*)file->Get("h_neutrond");
TH1D *h_antineutrond = (TH1D*)file->Get("h_antineutrond");
TH1D *h_muond = (TH1D*)file->Get("h_muond");
TH1D *h_electrond = (TH1D*)file->Get("h_electrond");
TH1D *h_dall_cand = (TH1D*)file->Get("h_dall_cand");
TH1D *h_d5_cand = (TH1D*)file->Get("h_d5_cand");

TH1D *hr_kaon0l_s_vs_ptcand = (TH1D*)h_kaon0l_s_vs_ptcand->Clone("hr_kaon0l_s_vs_ptcand");
TH1D *hr_kaon0s_s_vs_ptcand = (TH1D*)h_kaon0s_s_vs_ptcand->Clone("hr_kaon0s_s_vs_ptcand");
TH1D *hr_kaonp_s_vs_ptcand = (TH1D*)h_kaonp_s_vs_ptcand->Clone("hr_kaonp_s_vs_ptcand");
TH1D *hr_kaonm_s_vs_ptcand = (TH1D*)h_kaonm_s_vs_ptcand->Clone("hr_kaonm_s_vs_ptcand");
//TH1D *hr_kaon0_s_vs_ptcand = (TH1D*)h_kaon0->Clone("hr_kaon0_s_vs_ptcand");
TH1D *hrlambda_s_vs_ptcand = (TH1D*)h_lambda_s_vs_ptcand->Clone("hrlambda_s_vs_ptcand");
TH1D *hrsigma0_s_vs_ptcand = (TH1D*)h_sigma0_s_vs_ptcand->Clone("hrsigma0_s_vs_ptcand");
TH1D *hrsigmap_s_vs_ptcand = (TH1D*)h_sigmap_s_vs_ptcand->Clone("hrsigmap_s_vs_ptcand");
TH1D *hrsigmam_s_vs_ptcand = (TH1D*)h_sigmam_s_vs_ptcand->Clone("hrsigmam_s_vs_ptcand");
TH1D *hrpionp_s_vs_ptcand = (TH1D*)h_pionp_s_vs_ptcand->Clone("hrpionp_s_vs_ptcand");
TH1D *hrpionm_s_vs_ptcand = (TH1D*)h_pionm_s_vs_ptcand->Clone("hrpionm_s_vs_ptcand");
TH1D *hrpion0_s_vs_ptcand = (TH1D*)h_pion0_s_vs_ptcand->Clone("hrpion0_s_vs_ptcand");
TH1D *hrproton_s_vs_ptcand = (TH1D*)h_proton_s_vs_ptcand->Clone("hrproton_s_vs_ptcand");
TH1D *hrantiproton_s_vs_ptcand = (TH1D*)h_antiproton_s_vs_ptcand->Clone("hrantiproton_s_vs_ptcand");
TH1D *hrneutron_s_vs_ptcand = (TH1D*)h_neutron_s_vs_ptcand->Clone("hrneutron_s_vs_ptcand");
TH1D *hrantineutron_s_vs_ptcand = (TH1D*)h_antineutron_s_vs_ptcand->Clone("hrantineutron_s_vs_ptcand");
TH1D *hrelectron_s_vs_ptcand = (TH1D*)h_electron_s_vs_ptcand->Clone("hrelectron_s_vs_ptcand");
TH1D *hrmuon_s_vs_ptcand = (TH1D*)h_muon_s_vs_ptcand->Clone("hrmuon_s_vs_ptcand");
TH1D *hrs5 = (TH1D*)h_s5_cand->Clone("hrs5");

TH1D *hrk0lu = (TH1D*)h_kaon0lu->Clone("hrk0lu");
TH1D *hrk0su = (TH1D*)h_kaon0su->Clone("hrk0su");
TH1D *hrkpu = (TH1D*)h_kaonpu->Clone("hrkpu");
TH1D *hrkmu = (TH1D*)h_kaonmu->Clone("hrkmu");
//TH1D *hrk0u = (TH1D*)h_kaon0u->Clone("hrk0u");
TH1D *hrlambdau = (TH1D*)h_lambdau->Clone("hrlambdau");
TH1D *hrsigma0u = (TH1D*)h_sigma0u->Clone("hrsigma0u");
TH1D *hrsigmapu = (TH1D*)h_sigmapu->Clone("hrsigmapu");
TH1D *hrsigmamu = (TH1D*)h_sigmamu->Clone("hrsigmamu");
TH1D *hrpionpu = (TH1D*)h_pionpu->Clone("hrpionpu");
TH1D *hrpionmu = (TH1D*)h_pionmu->Clone("hrpionmu");
TH1D *hrpion0u = (TH1D*)h_pion0u->Clone("hrpion0u");
TH1D *hrprotonu = (TH1D*)h_protonu->Clone("hrprotonu");
TH1D *hrantiprotonu = (TH1D*)h_antiprotonu->Clone("hrantiprotonu");
TH1D *hrneutronu = (TH1D*)h_neutronu->Clone("hrneutronu");
TH1D *hrantineutronu = (TH1D*)h_antineutronu->Clone("hrantineutronu");
TH1D *hrelectronu = (TH1D*)h_electronu->Clone("hrelectronu");
TH1D *hrmuonu = (TH1D*)h_muonu->Clone("hrmuonu");
TH1D *hru5 = (TH1D*)h_u5_cand->Clone("hru5");

TH1D *hrk0ld = (TH1D*)h_kaon0ld->Clone("hrk0ld");
TH1D *hrk0sd = (TH1D*)h_kaon0sd->Clone("hrk0sd");
TH1D *hrkpd = (TH1D*)h_kaonpd->Clone("hrkpd");
TH1D *hrkmd = (TH1D*)h_kaonmd->Clone("hrkmd");
//TH1D *hrk0d = (TH1D*)h_kaon0d->Clone("hrk0d");
TH1D *hrlambdad = (TH1D*)h_lambdad->Clone("hrlambdad");
TH1D *hrsigma0d = (TH1D*)h_sigma0d->Clone("hrsigma0d");
TH1D *hrsigmapd = (TH1D*)h_sigmapd->Clone("hrsigmapd");
TH1D *hrsigmamd = (TH1D*)h_sigmamd->Clone("hrsigmamd");
TH1D *hrpionpd = (TH1D*)h_pionpd->Clone("hrpionpd");
TH1D *hrpionmd = (TH1D*)h_pionmd->Clone("hrpionmd");
TH1D *hrpion0d = (TH1D*)h_pion0d->Clone("hrpion0d");
TH1D *hrprotond = (TH1D*)h_protond->Clone("hrprotond");
TH1D *hrantiprotond = (TH1D*)h_antiprotond->Clone("hrantiprotond");
TH1D *hrneutrond = (TH1D*)h_neutrond->Clone("hrneutrond");
TH1D *hrantineutrond = (TH1D*)h_antineutrond->Clone("hrantineutrond");
TH1D *hrelectrond = (TH1D*)h_electrond->Clone("hrelectrond");
TH1D *hrmuond = (TH1D*)h_muond->Clone("hrmuond");
TH1D *hrd5 = (TH1D*)h_d5_cand->Clone("hrd5");

TH1D *hrk0ldu = (TH1D*)h_kaon0lu->Clone("hrk0ldu");
TH1D *hrk0sdu = (TH1D*)h_kaon0su->Clone("hrk0sdu");
TH1D *hrkpdu = (TH1D*)h_kaonpu->Clone("hrkpdu");
TH1D *hrkmdu = (TH1D*)h_kaonmu->Clone("hrkmdu");
//TH1D *hrk0du = (TH1D*)h_kaon0u->Clone("hrk0du");
TH1D *hrlambdadu = (TH1D*)h_lambdau->Clone("hrlambdadu");
TH1D *hrsigma0du = (TH1D*)h_sigma0u->Clone("hrsigma0du");
TH1D *hrsigmapdu = (TH1D*)h_sigmapu->Clone("hrsigmapdu");
TH1D *hrsigmamdu = (TH1D*)h_sigmamu->Clone("hrsigmamdu");
TH1D *hrpionpdu = (TH1D*)h_pionpu->Clone("hrpionpdu");
TH1D *hrpionmdu = (TH1D*)h_pionmu->Clone("hrpionmdu");
TH1D *hrpion0du = (TH1D*)h_pion0u->Clone("hrpion0du");
TH1D *hrdu5 = (TH1D*)h_u5_cand->Clone("hrdu5");

TH1D *hrprotondu = (TH1D*)h_protonu->Clone("hrprotondu");
TH1D *hrantiprotondu = (TH1D*)h_antiprotonu->Clone("hrantiprotondu");
TH1D *hrneutrondu = (TH1D*)h_neutronu->Clone("hrneutrondu");
TH1D *hrantineutrondu = (TH1D*)h_antineutronu->Clone("hrantineutrondu");
TH1D *hrelectrondu = (TH1D*)h_electronu->Clone("hrelectrondu");
TH1D *hrmuondu = (TH1D*)h_muonu->Clone("hrmuondu");
TH1D *h_duall_cand = (TH1D*)h_uall_cand->Clone("h_duall_cand");

hrprotondu->Add(h_protond);
hrneutrondu->Add(h_neutrond);
hrantiprotondu->Add(h_antiprotond);
hrantineutrondu->Add(h_antineutrond);
hrelectrondu->Add(h_electrond);
hrmuondu->Add(h_muond);
h_duall_cand->Add(h_dall_cand);

hrk0ldu->Add(hrk0ld);
hrk0sdu->Add(hrk0sd);
hrkpdu->Add(hrkpd);
hrkmdu->Add(hrkmd);
//hrk0du->Add(hrk0d);
hrlambdadu->Add(hrlambdad);
hrsigma0du->Add(hrsigma0d);
hrsigmapdu->Add(hrsigmapd);
hrsigmamdu->Add(hrsigmamd);
hrpionpdu->Add(hrpionpd);
hrpionmdu->Add(hrpionmd);
hrpion0du->Add(hrpion0d);
hrdu5->Add(hrd5);


hr_kaon0l_s_vs_ptcand->Divide(h_sall_cand);
hr_kaon0s_s_vs_ptcand->Divide(h_sall_cand);
hr_kaonp_s_vs_ptcand->Divide(h_sall_cand);
hr_kaonm_s_vs_ptcand->Divide(h_sall_cand);
//hr_kaon0_s_vs_ptcand->Divide(h_sall);
hrlambda_s_vs_ptcand->Divide(h_sall_cand);
hrsigma0s->Divide(h_sall_cand);

hrsigmaps->Add(hrsigmams);

hrsigmaps->Divide(h_sall_cand);
//hrsigmams->Divide(h_sall_cand);
hrpionps->Divide(h_sall_cand);
hrpionms->Divide(h_sall_cand);
hrpion0s->Divide(h_sall_cand);
hrprotons->Divide(h_sall_cand);
hrneutrons->Divide(h_sall_cand);
hrantiprotons->Divide(h_sall_cand);
hrantineutrons->Divide(h_sall_cand);

hrelectrons->Add(hrmuons);

hrelectrons->Divide(h_sall_cand);
//hrmuons->Divide(h_sall_cand);
hrs5->Divide(h_sall_cand);

hrk0lu->Divide(h_uall_cand);
hrk0su->Divide(h_uall_cand);
hrkpu->Divide(h_uall_cand);
hrkmu->Divide(h_uall_cand);
//hrk0u->Divide(h_uall_cand);
hrlambdau->Divide(h_uall_cand);
hrsigma0u->Divide(h_uall_cand);

hrsigmapu->Add(hrsigmamu);

hrsigmapu->Divide(h_uall_cand);
//hrsigmamu->Divide(h_uall_cand);
hrpionpu->Divide(h_uall_cand);
hrpionmu->Divide(h_uall_cand);
hrpion0u->Divide(h_uall_cand);
hrprotonu->Divide(h_uall_cand);
hrneutronu->Divide(h_uall_cand);
hrantiprotonu->Divide(h_uall_cand);
hrantineutronu->Divide(h_uall_cand);

hrelectronu->Add(hrmuonu);

hrelectronu->Divide(h_uall_cand);
//hrmuonu->Divide(h_uall_cand);
hru5->Divide(h_uall_cand);

hrk0ld->Divide(h_dall_cand);
hrk0sd->Divide(h_dall_cand);
hrkpd->Divide(h_dall_cand);
hrkmd->Divide(h_dall_cand);
//hrk0d->Divide(h_dall_cand);
hrlambdad->Divide(h_dall_cand);
hrsigma0d->Divide(h_dall_cand);

hrsigmapd->Add(hrsigmamd);

hrsigmapd->Divide(h_dall_cand);
//hrsigmamd->Divide(h_dall_cand);
hrpionpd->Divide(h_dall_cand);
hrpionmd->Divide(h_dall_cand);
hrpion0d->Divide(h_dall_cand);
hrprotond->Divide(h_dall_cand);
hrneutrond->Divide(h_dall_cand);
hrantiprotond->Divide(h_dall_cand);
hrantineutrond->Divide(h_dall_cand);

hrelectrond->Add(hrmuond);

hrelectrond->Divide(h_dall_cand);
//hrmuond->Divide(h_dall_cand);
hrd5->Divide(h_dall_cand);

hrk0ldu->Divide(h_duall_cand);
hrk0sdu->Divide(h_duall_cand);
hrkpdu->Divide(h_duall_cand);
hrkmdu->Divide(h_duall_cand);
//hrk0du->Divide(h_duall_cand);
hrlambdadu->Divide(h_duall_cand);
hrsigma0du->Divide(h_duall_cand);

hrsigmapdu->Add(hrsigmamdu);

hrsigmapdu->Divide(h_duall_cand);
//hrsigmamdu->Divide(h_duall_cand);
hrpionpdu->Divide(h_duall_cand);
hrpionmdu->Divide(h_duall_cand);
hrpion0du->Divide(h_duall_cand);
hrprotondu->Divide(h_duall_cand);
hrneutrondu->Divide(h_duall_cand);
hrantiprotondu->Divide(h_duall_cand);
hrantineutrondu->Divide(h_duall_cand);

hrelectrondu->Add(hrmuondu);

hrelectrondu->Divide(h_duall_cand);
//hrmuondu->Divide(h_duall_cand);
hrdu5->Divide(h_duall_cand);*/
/*
// Create a stack
setTDRStyle();
lumi_136TeV = "Run3";
extraText = "Private";
TH1D *h1 = tdrHist("h1","S jet N fraction",0 + 1e-4,1,"p_{T,cand} (GeV)",0.1,100);
TCanvas *c1 = tdrCanvas("c1",h1,8,kSquare);
c1->SetLogx();

THStack *hs = new THStack("hs", "; p_{T,cand} (GeV); S Jet N fraction");

// Set histogram fill colors and add to stack
hr_electron_s_vs_ptcand->SetFillColor(kCyan-9);
hrs5->SetFillColor(kBlue-9);
hrlambdas->SetFillColor(kTeal-9);
hrk0ls->SetFillColor(kGreen-6);
hrk0ss->SetFillColor(kGreen-7);
//hrk0s->SetFillColor(kOrange);
hrantineutrons->SetFillColor(kGreen-9);
hrneutrons->SetFillColor(kGreen-10);
hrantiprotons->SetFillColor(kMagenta-7);
hrprotons->SetFillColor(kMagenta-9);
//hrpion0s->SetFillColor(kViolet-4);
//hrsigma0s->SetFillColor(kPink+6);
hrsigmaps->SetFillColor(kMagenta-10);
//hrsigmams->SetFillColor(kViolet+1);
hrkms->SetFillColor(kRed-6);
hrkps->SetFillColor(kRed-7);
hrpionms->SetFillColor(kRed-9);
hrpionps->SetFillColor(kRed-10);
//hrmuons->SetFillColor(kPink+1);


// Add histograms to the stack
hs->Add(hrpionps);
hs->Add(hrpionms);
hs->Add(hrkps);
hs->Add(hrkms);
//hs->Add(hrk0s);

hs->Add(hrsigmaps);
//hs->Add(hrsigmams);
//hs->Add(hrpion0s);
//hs->Add(hrsigma0s);
hs->Add(hrprotons);
hs->Add(hrantiprotons);
hs->Add(hrneutrons);
hs->Add(hrantineutrons);
hs->Add(hrk0ss);
hs->Add(hrk0ls);
hs->Add(hrlambdas);
hs->Add(hrs5);
hs->Add(hrelectrons);
//hs->Add(hrmuons);


hs->Draw("hist same");

gPad->SetBottomMargin(0.14);
gPad->SetRightMargin(0.1);
gPad->Update();

// Create legend
TLegend *leg = tdrLeg(0.9,0.79-0.04*14,1.1,0.9);
//leg->AddEntry(hrmuons, "#mu", "f");
leg->AddEntry(hrelectrons, "e, #mu", "f");
leg->AddEntry(hrs5, "#gamma", "f");
leg->AddEntry(hrlambdas, "#Lambda", "f");
leg->AddEntry(hrk0ls, "K_{L}", "f");
leg->AddEntry(hrk0ss, "K_{S}", "f");
leg->AddEntry(hrantineutrons, "#bar{n}", "f");
leg->AddEntry(hrneutrons, "n", "f");
leg->AddEntry(hrantiprotons, "#bar{p}", "f");
leg->AddEntry(hrprotons, "p", "f");
leg->AddEntry(hrsigmaps, "#Sigma^{+/-}", "f");
//leg->AddEntry(hrsigmams, "#Sigma^{-}", "f");
leg->AddEntry(hrkms, "K^{-}", "f");
leg->AddEntry(hrkps, "K^{+}", "f");
leg->AddEntry(hrpionms, "#pi^{-}", "f");
leg->AddEntry(hrpionps, "#pi^{+}", "f");
leg->SetTextFont(42);
leg->SetTextSize(0.04);
leg->Draw();

TLatex *tex1 = new TLatex();
tex1->SetNDC(); tex1->SetTextSize(0.045);
tex1->DrawLatex(0.17,0.8,"|#eta| < 1.3");
tex1->DrawLatex(0.17,0.75,"80 < p_{T,jet} < 100 GeV");

TLatex *tex2 = new TLatex();
tex2->SetNDC(); tex2->SetTextSize(0.065);
tex2->DrawLatex(0.1,0.92,"CMS");

TLatex *tex3 = new TLatex();
tex3->SetNDC(); tex3->SetTextSize(0.05);
tex3->SetTextFont(42);
tex3->DrawLatex(0.65,0.92,"Run3 (13.6 TeV)");

TLatex *tex4 = new TLatex();
tex4->SetNDC(); tex4->SetTextSize(0.045);
tex4->SetTextFont(52);
tex4->DrawLatex(0.15,0.83,"Private");

// Update the canvas to reflect changes
c1->RedrawAxis();
c1->Modified();
c1->Update();
c1->SaveAs("pdf/fractions2S.pdf");
















setTDRStyle();
lumi_136TeV = "Run3";
extraText = "Private";
TH1D *h2 = tdrHist("h2","UD jet N fraction",0 + 1e-4,1,"p_{T,cand} (GeV)",0.1,100);
TCanvas *c2 = tdrCanvas("c2",h2,8,kSquare);
c2->SetLogx();

THStack *hdu = new THStack("hdu", "; p_{T,cand} (GeV); U & D Jet N fraction");

// Set histogram fill colors and add to stack
hrelectrondu->SetFillColor(kCyan-9);
hrdu5->SetFillColor(kBlue-9);
hrlambdadu->SetFillColor(kTeal-9);
hrk0ldu->SetFillColor(kGreen-6);
hrk0sdu->SetFillColor(kGreen-7);
//hrk0du->SetFillColor(kOrange);
hrantineutrondu->SetFillColor(kGreen-9);
hrneutrondu->SetFillColor(kGreen-10);
hrantiprotondu->SetFillColor(kMagenta-7);
hrprotondu->SetFillColor(kMagenta-9);
//hrpion0du->SetFillColor(kViolet-4);
//hrsigma0du->SetFillColor(kPink+6);
hrsigmapdu->SetFillColor(kMagenta-10);
//hrsigmamdu->SetFillColor(kViolet+1);
hrkmdu->SetFillColor(kRed-6);
hrkpdu->SetFillColor(kRed-7);
hrpionmdu->SetFillColor(kRed-9);
hrpionpdu->SetFillColor(kRed-10);
//hrmuondu->SetFillColor(kPink+1);


// Add histograms to the stack
hdu->Add(hrpionpdu);
hdu->Add(hrpionmdu);
hdu->Add(hrkpdu);
hdu->Add(hrkmdu);
//hdu->Add(hrk0du);
hdu->Add(hrsigmapdu);
//hdu->Add(hrsigmamdu);
//hdu->Add(hrpion0du);
//hdu->Add(hrsigma0du);
hdu->Add(hrprotondu);
hdu->Add(hrantiprotondu);
hdu->Add(hrneutrondu);
hdu->Add(hrantineutrondu);
hdu->Add(hrk0sdu);
hdu->Add(hrk0ldu);
hdu->Add(hrlambdadu);
hdu->Add(hrdu5);
hdu->Add(hrelectrondu);
//hdu->Add(hrmuondu);

hdu->Draw("hist same");

gPad->SetBottomMargin(0.14);
gPad->SetRightMargin(0.1);
gPad->Update();

// Create legend
TLegend *leg2 = tdrLeg(0.9,0.79-0.04*14,1.1,0.9);
//leg2->AddEntry(hrmuonu, "#mu", "f");
leg2->AddEntry(hrelectrondu, "e, #mu", "f");
leg2->AddEntry(hrdu5, "#gamma", "f");
leg2->AddEntry(hrlambdadu, "#Lambda", "f");
leg2->AddEntry(hrk0ldu, "K_{L}", "f");
leg2->AddEntry(hrk0sdu, "K_{S}", "f");
leg2->AddEntry(hrantineutrondu, "#bar{n}", "f");
leg2->AddEntry(hrneutrondu, "n", "f");
leg2->AddEntry(hrantiprotondu, "#bar{p}", "f");
leg2->AddEntry(hrprotondu, "p", "f");
leg2->AddEntry(hrsigmapdu, "#Sigma^{+/-}", "f");
//leg2->AddEntry(hrsigmamdu, "#Sigma^{-}", "f");
leg2->AddEntry(hrkmdu, "K^{-}", "f");
leg2->AddEntry(hrkpdu, "K^{+}", "f");
leg2->AddEntry(hrpionmdu, "#pi^{-}", "f");
leg2->AddEntry(hrpionpdu, "#pi^{+}", "f");
leg2->SetTextFont(42);
leg2->SetTextSize(0.04);
leg2->Draw();

TLatex *tex21 = new TLatex();
tex21->SetNDC(); tex21->SetTextSize(0.045);
tex21->DrawLatex(0.17,0.8,"|#eta| < 1.3");
tex21->DrawLatex(0.17,0.75,"60 < p_{T,jet} < 140 GeV");

// Assuming the x-axis categories are correctly set when histograms were created
// If you need to set labels for the x-axis categories, do it here

// Update the canvas to reflect changes
c2->RedrawAxis();
c2->Modified();
c2->Update();
c2->SaveAs("pdf/fractions2UD.pdf");







setTDRStyle();
lumi_136TeV = "Run3";
extraText = "Private";
TH1D *h3 = tdrHist("h3","U jet N fraction",0 + 1e-4,1,"p_{T,cand} (GeV)",0.1,100);
TCanvas *c3 = tdrCanvas("c3",h3,8,kSquare);
c3->SetLogx();

THStack *hu = new THStack("hu", "; p_{T,cand} (GeV); U Jet N fraction");

// Set histogram fill colors and add to stack
hrelectronu->SetFillColor(kCyan-9);
hru5->SetFillColor(kBlue-9);
hrlambdau->SetFillColor(kTeal-9);
hrk0lu->SetFillColor(kGreen-6);
hrk0su->SetFillColor(kGreen-7);
//hrk0u->SetFillColor(kOrange);
hrantineutronu->SetFillColor(kGreen-9);
hrneutronu->SetFillColor(kGreen-10);
hrantiprotonu->SetFillColor(kMagenta-7);
hrprotonu->SetFillColor(kMagenta-9);
//hrpion0u->SetFillColor(kViolet-4);
//hrsigma0u->SetFillColor(kPink+6);
hrsigmapu->SetFillColor(kMagenta-10);
//hrsigmamu->SetFillColor(kViolet+1);
hrkmu->SetFillColor(kRed-6);
hrkpu->SetFillColor(kRed-7);
hrpionmu->SetFillColor(kRed-9);
hrpionpu->SetFillColor(kRed-10);
//hrmuonu->SetFillColor(kPink+1);


// Add histograms to the stack
hu->Add(hrpionpu);
hu->Add(hrpionmu);
hu->Add(hrkpu);
hu->Add(hrkmu);
//hu->Add(hrk0u);

hu->Add(hrsigmapu);
//hu->Add(hrsigmamu);
//hu->Add(hrpion0u);
//hu->Add(hrsigma0u);
hu->Add(hrprotonu);
hu->Add(hrantiprotonu);
hu->Add(hrneutronu);
hu->Add(hrantineutronu);
hu->Add(hrk0su);
hu->Add(hrk0lu);
hu->Add(hrlambdau);
hu->Add(hru5);
hu->Add(hrelectronu);
//hu->Add(hrmuonu);

hu->Draw("hist same");

gPad->SetBottomMargin(0.14);
gPad->SetRightMargin(0.1);
gPad->Update(); 

// Create legend
TLegend *leg3 = tdrLeg(0.9,0.79-0.04*14,1.1,0.9);
//leg3->AddEntry(hrmuonu, "#mu", "f");
leg3->AddEntry(hrelectronu, "e, #mu", "f");
leg3->AddEntry(hru5, "#gamma", "f");
leg3->AddEntry(hrlambdau, "#Lambda", "f");
leg3->AddEntry(hrk0lu, "K_{L}", "f");
leg3->AddEntry(hrk0su, "K_{S}", "f");
leg3->AddEntry(hrantineutronu, "#bar{n}", "f");
leg3->AddEntry(hrneutronu, "n", "f");
leg3->AddEntry(hrantiprotonu, "#bar{p}", "f");
leg3->AddEntry(hrprotonu, "p", "f");
leg3->AddEntry(hrsigmapu, "#Sigma^{+/-}", "f");
//leg3->AddEntry(hrsigmamu, "#Sigma^{-}", "f");
leg3->AddEntry(hrkmu, "K^{-}", "f");
leg3->AddEntry(hrkpu, "K^{+}", "f");
leg3->AddEntry(hrpionmu, "#pi^{-}", "f");
leg3->AddEntry(hrpionpu, "#pi^{+}", "f");


//leg3->AddEntry(hrk0u, "K^0", "f");
//leg3->AddEntry(hrsigma0u, "#Sigma^{0}", "f");
//leg3->AddEntry(hrpion0u, "#pi^{0}", "f");
leg3->SetTextFont(42);
leg3->SetTextSize(0.04);
leg3->Draw();

TLatex *tex31 = new TLatex();
tex31->SetNDC(); tex31->SetTextSize(0.045);
tex31->DrawLatex(0.17,0.8,"|#eta| < 1.3");
tex31->DrawLatex(0.17,0.75,"80 < p_{T,jet} < 100 GeV");

// Update the canvas to reflect changes
c3->RedrawAxis();
c3->Modified();
c3->Update();
c3->SaveAs("pdf/fractions2U.pdf");






setTDRStyle();
lumi_136TeV = "Run3";
extraText = "Private";
TH1D *h4 = tdrHist("h4","D jet N fraction",0 + 1e-4,1,"p_{T,cand} (GeV)",0.1,100);
TCanvas *c4 = tdrCanvas("c4",h4,8,kSquare);
c4->SetLogx();

THStack *hd = new THStack("hd", "; p_{T,cand} (GeV); D Jet N fraction");

// Set histogram fill colors and add to stack
hrelectrond->SetFillColor(kCyan-9);
hrd5->SetFillColor(kBlue-9);
hrlambdad->SetFillColor(kTeal-9);
hrk0ld->SetFillColor(kGreen-6);
hrk0sd->SetFillColor(kGreen-7);
//hrk0d->SetFillColor(kOrange);
hrantineutrond->SetFillColor(kGreen-9);
hrneutrond->SetFillColor(kGreen-10);
hrantiprotond->SetFillColor(kMagenta-7);
hrprotond->SetFillColor(kMagenta-9);
//hrpion0d->SetFillColor(kViolet-4);
//hrsigma0d->SetFillColor(kPink+6);
hrsigmapd->SetFillColor(kMagenta-10);
//hrsigmamd->SetFillColor(kViolet+1);
hrkmd->SetFillColor(kRed-6);
hrkpd->SetFillColor(kRed-7);
hrpionmd->SetFillColor(kRed-9);
hrpionpd->SetFillColor(kRed-10);
//hrmuond->SetFillColor(kPink+1);


// Add histograms to the stack
hd->Add(hrpionpd);
hd->Add(hrpionmd);
hd->Add(hrkpd);
hd->Add(hrkmd);
//hd->Add(hrk0d);
hd->Add(hrsigmapd);
//hd->Add(hrsigmamd);
//hd->Add(hrpion0d);
//hd->Add(hrsigma0d);
hd->Add(hrprotond);
hd->Add(hrantiprotond);
hd->Add(hrneutrond);
hd->Add(hrantineutrond);
hd->Add(hrk0sd);
hd->Add(hrk0ld);
hd->Add(hrlambdad);
hd->Add(hrd5);
hd->Add(hrelectrond);
//hd->Add(hrmuond);

hd->Draw("hist same");

gPad->SetBottomMargin(0.14);
gPad->SetRightMargin(0.1);
gPad->Update();  

// Create legend
TLegend *leg4 = tdrLeg(0.9,0.79-0.04*14,1.1,0.9);
//leg4->AddEntry(hrmuond, "#mu", "f");
leg4->AddEntry(hrelectrond, "e, #mu", "f");
leg4->AddEntry(hrd5, "#gamma", "f");
leg4->AddEntry(hrlambdad, "#Lambda", "f");
leg4->AddEntry(hrk0ld, "K_{L}", "f");
leg4->AddEntry(hrk0sd, "K_{S}", "f");
leg4->AddEntry(hrantineutrond, "#bar{n}", "f");
leg4->AddEntry(hrneutrond, "n", "f");
leg4->AddEntry(hrantiprotond, "#bar{p}", "f");
leg4->AddEntry(hrprotond, "p", "f");
leg4->AddEntry(hrsigmapd, "#Sigma^{+/-}", "f");
//leg4->AddEntry(hrsigmamd, "#Sigma^{-}", "f");
leg4->AddEntry(hrkmd, "K^{-}", "f");
leg4->AddEntry(hrkpd, "K^{+}", "f");
leg4->AddEntry(hrpionmd, "#pi^{-}", "f");
leg4->AddEntry(hrpionpd, "#pi^{+}", "f");


//leg4->AddEntry(hrk0d, "K^0", "f");
//leg4->AddEntry(hrsigma0d, "#Sigma^{0}", "f");
//leg4->AddEntry(hrpion0d, "#pi^{0}", "f");
leg4->SetTextFont(42);
leg4->SetTextSize(0.04);
leg4->Draw();

TLatex *tex41 = new TLatex();
tex41->SetNDC(); tex41->SetTextSize(0.045);
tex41->DrawLatex(0.17,0.8,"|#eta| < 1.3");
tex41->DrawLatex(0.17,0.75,"80 < p_{T,jet} < 100 GeV");
// Update the canvas to reflect changes
c4->RedrawAxis();
c4->Modified();
c4->Update();
c4->SaveAs("pdf/fractions2D.pdf");

// Do not close the file if you want to interact with the histograms further
// file->Close(); // Uncomment this if you're done with the file
}
*/