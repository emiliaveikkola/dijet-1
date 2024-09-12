#include <TH1.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include <TList.h>
#include "tdrstyle_mod22.C"

void difference_test() {
    // Open the ROOT file containing the histograms
    TFile *file = new TFile("output_z2.root", "READ");

    setTDRStyle();
    lumi_136TeV = "Run3";
    extraText = "Private";

    // Set up the canvas
   TH1D *h = tdrHist("h","S-X N fraction",-0.05 + 1e-4,0.05 -1e-4,"p^{genjet}_{T} (GeV)",180,220);
   TCanvas *c = tdrCanvas("c",h,8,11,kSquare);
    h->GetXaxis()->SetLabelSize(0.04);
    h->GetYaxis()->SetLabelSize(0.04);
    h->GetXaxis()->SetTitleSize(0.045);
    h->GetXaxis()->SetTitleOffset(1.2);
    h->GetYaxis()->SetTitleOffset(1.35);
    h->GetYaxis()->SetTitleSize(0.045);

    // Retrieve histograms from the file
    TH1D *h_hadron_nh_s = (TH1D*)file->Get("h_s_nh_vs_ptjet");
    TH1D *h_hadron_ne_s = (TH1D*)file->Get("h_s_ne_vs_ptjet");
    TH1D *h_hadron_ch_s= (TH1D*)file->Get("h_s_ch_vs_ptjet");
    TH1D *h_s_all= (TH1D*)file->Get("h_all_s_vs_ptjet");

    TH1D *h_hadron_nh_d = (TH1D*)file->Get("h_d_nh_vs_ptjet");
    TH1D *h_hadron_ne_d = (TH1D*)file->Get("h_d_ne_vs_ptjet");
    TH1D *h_hadron_ch_d = (TH1D*)file->Get("h_d_ch_vs_ptjet");
    TH1D *h_d_all= (TH1D*)file->Get("h_all_d_vs_ptjet");

    TH1D *h_hadron_nh_u = (TH1D*)file->Get("h_u_nh_vs_ptjet");
    TH1D *h_hadron_ne_u = (TH1D*)file->Get("h_u_ne_vs_ptjet");
    TH1D *h_hadron_ch_u = (TH1D*)file->Get("h_u_ch_vs_ptjet");
    TH1D *h_u_all= (TH1D*)file->Get("h_all_u_vs_ptjet");

    TH1D *h_hadron_nh_c = (TH1D*)file->Get("h_c_nh_vs_ptjet");
    TH1D *h_hadron_ne_c = (TH1D*)file->Get("h_c_ne_vs_ptjet");
    TH1D *h_hadron_ch_c = (TH1D*)file->Get("h_c_ch_vs_ptjet");
    TH1D *h_c_all= (TH1D*)file->Get("h_all_c_vs_ptjet");

    TH1D *h_hadron_nh_b = (TH1D*)file->Get("h_b_nh_vs_ptjet");
    TH1D *h_hadron_ne_b = (TH1D*)file->Get("h_b_ne_vs_ptjet");
    TH1D *h_hadron_ch_b = (TH1D*)file->Get("h_b_ch_vs_ptjet");
    TH1D *h_b_all= (TH1D*)file->Get("h_all_b_vs_ptjet");

    TH1D *h_hadron_nh_g = (TH1D*)file->Get("h_g_nh_vs_ptjet");
    TH1D *h_hadron_ne_g = (TH1D*)file->Get("h_g_ne_vs_ptjet");
    TH1D *h_hadron_ch_g = (TH1D*)file->Get("h_g_ch_vs_ptjet");
    TH1D *h_g_all= (TH1D*)file->Get("h_all_g_vs_ptjet");


//////////////////////////////////////////////////////////////////////////////////////////////////
    TH1D *hr_hadron_nh_s = (TH1D*)h_hadron_nh_s->Clone("hr_hadron_nh_s");
    TH1D *hr_hadron_ne_s = (TH1D*)h_hadron_ne_s->Clone("hr_hadron_ne_s");
    TH1D *hr_hadron_ch_s= (TH1D*)h_hadron_ch_s->Clone("hr_hadron_ch_s");

    TH1D *hr_hadron_nh_d = (TH1D*)h_hadron_nh_d->Clone("hr_hadron_nh_d");
    TH1D *hr_hadron_ne_d = (TH1D*)h_hadron_ne_d->Clone("hr_hadron_ne_d");
    TH1D *hr_hadron_ch_d= (TH1D*)h_hadron_ch_d->Clone("hr_hadron_ch_d");


    TH1D *hr_hadron_nh_u = (TH1D*)h_hadron_nh_u->Clone("hr_hadron_nh_u");
    TH1D *hr_hadron_ne_u = (TH1D*)h_hadron_ne_u->Clone("hr_hadron_ne_u");
    TH1D *hr_hadron_ch_u= (TH1D*)h_hadron_ch_u->Clone("hr_hadron_ch_u");


    TH1D *hr_hadron_nh_c = (TH1D*)h_hadron_nh_c->Clone("hr_hadron_nh_c");
    TH1D *hr_hadron_ne_c = (TH1D*)h_hadron_ne_c->Clone("hr_hadron_ne_c");
    TH1D *hr_hadron_ch_c= (TH1D*)h_hadron_ch_c->Clone("hr_hadron_ch_c");

    TH1D *hr_hadron_nh_b = (TH1D*)h_hadron_nh_b->Clone("hr_hadron_nh_b");
    TH1D *hr_hadron_ne_b = (TH1D*)h_hadron_ne_b->Clone("hr_hadron_ne_b");
    TH1D *hr_hadron_ch_b= (TH1D*)h_hadron_ch_b->Clone("hr_hadron_ch_b");

    TH1D *hr_hadron_nh_g = (TH1D*)h_hadron_nh_g->Clone("hr_hadron_nh_g");
    TH1D *hr_hadron_ne_g = (TH1D*)h_hadron_ne_g->Clone("hr_hadron_ne_g");
    TH1D *hr_hadron_ch_g= (TH1D*)h_hadron_ch_g->Clone("hr_hadron_ch_g");



    hr_hadron_nh_s->Divide(h_hadron_nh_s,h_s_all,1,1,"b");
    hr_hadron_ne_s->Divide(h_hadron_ne_s,h_s_all,1,1,"b");
    hr_hadron_ch_s->Divide(h_hadron_ch_s,h_s_all,1,1,"b");

    hr_hadron_nh_d->Divide(h_hadron_nh_d,h_d_all,1,1,"b");
    hr_hadron_ne_d->Divide(h_hadron_ne_d,h_d_all,1,1,"b");
    hr_hadron_ch_d->Divide(h_hadron_ch_d,h_d_all,1,1,"b");

    hr_hadron_nh_u->Divide(h_hadron_nh_u,h_u_all,1,1,"b");
    hr_hadron_ne_u->Divide(h_hadron_ne_u,h_u_all,1,1,"b");
    hr_hadron_ch_u->Divide(h_hadron_ch_u,h_u_all,1,1,"b");

    hr_hadron_nh_c->Divide(h_hadron_nh_c,h_c_all,1,1,"b");
    hr_hadron_ne_c->Divide(h_hadron_ne_c,h_c_all,1,1,"b");
    hr_hadron_ch_c->Divide(h_hadron_ch_c,h_c_all,1,1,"b");

    hr_hadron_nh_b->Divide(h_hadron_nh_b,h_b_all,1,1,"b");
    hr_hadron_ne_b->Divide(h_hadron_ne_b,h_b_all,1,1,"b");
    hr_hadron_ch_b->Divide(h_hadron_ch_b,h_b_all,1,1,"b");

    hr_hadron_nh_g->Divide(h_hadron_nh_g,h_g_all,1,1,"b");
    hr_hadron_ne_g->Divide(h_hadron_ne_g,h_g_all,1,1,"b");
    hr_hadron_ch_g->Divide(h_hadron_ch_g,h_g_all,1,1,"b");


    TH1D *hr_hadron_nh_sd = (TH1D*)hr_hadron_nh_s->Clone("hr_hadron_nh_sd");
    TH1D *hr_hadron_ne_sd = (TH1D*)hr_hadron_ne_s->Clone("hr_hadron_ne_sd");
    TH1D *hr_hadron_ch_sd= (TH1D*)hr_hadron_ch_s->Clone("hr_hadron_ch_sd");

    TH1D *hr_hadron_nh_su = (TH1D*)hr_hadron_nh_s->Clone("hr_hadron_nh_su");
    TH1D *hr_hadron_ne_su = (TH1D*)hr_hadron_ne_s->Clone("hr_hadron_ne_su");
    TH1D *hr_hadron_ch_su= (TH1D*)hr_hadron_ch_s->Clone("hr_hadron_ch_su");

    TH1D *hr_hadron_nh_sc = (TH1D*)hr_hadron_nh_s->Clone("hr_hadron_nh_sc");
    TH1D *hr_hadron_ne_sc = (TH1D*)hr_hadron_ne_s->Clone("hr_hadron_ne_sc");
    TH1D *hr_hadron_ch_sc= (TH1D*)hr_hadron_ch_s->Clone("hr_hadron_ch_sc");

    TH1D *hr_hadron_nh_sb = (TH1D*)hr_hadron_nh_s->Clone("hr_hadron_nh_sb");
    TH1D *hr_hadron_ne_sb = (TH1D*)hr_hadron_ne_s->Clone("hr_hadron_ne_sb");
    TH1D *hr_hadron_ch_sb= (TH1D*)hr_hadron_ch_s->Clone("hr_hadron_ch_sb");

    TH1D *hr_hadron_nh_sg = (TH1D*)hr_hadron_nh_s->Clone("hr_hadron_nh_sg");
    TH1D *hr_hadron_ne_sg = (TH1D*)hr_hadron_ne_s->Clone("hr_hadron_ne_sg");
    TH1D *hr_hadron_ch_sg= (TH1D*)hr_hadron_ch_s->Clone("hr_hadron_ch_sg");


    hr_hadron_nh_sd->Add(hr_hadron_nh_d, -1);
    hr_hadron_nh_su->Add(hr_hadron_nh_u, -1);
    hr_hadron_nh_sc->Add(hr_hadron_nh_c, -1);
    hr_hadron_nh_sb->Add(hr_hadron_nh_b, -1);
    hr_hadron_nh_sg->Add(hr_hadron_nh_g, -1);

    hr_hadron_ch_sd->Add(hr_hadron_ch_d, -1);
    hr_hadron_ch_su->Add(hr_hadron_ch_u, -1);
    hr_hadron_ch_sc->Add(hr_hadron_ch_c, -1);
    hr_hadron_ch_sb->Add(hr_hadron_ch_b, -1);
    hr_hadron_ch_sg->Add(hr_hadron_ch_g, -1);

    hr_hadron_ne_sd->Add(hr_hadron_ne_d, -1);
    hr_hadron_ne_su->Add(hr_hadron_ne_u, -1);
    hr_hadron_ne_sc->Add(hr_hadron_ne_c, -1);
    hr_hadron_ne_sb->Add(hr_hadron_ne_b, -1);
    hr_hadron_ne_sg->Add(hr_hadron_ne_g, -1);


    hr_hadron_nh_sd->SetLineWidth(3);
    hr_hadron_nh_su->SetLineWidth(4);
    hr_hadron_nh_sc->SetLineWidth(4);
    hr_hadron_nh_sb->SetLineWidth(4);
    hr_hadron_nh_sg->SetLineWidth(4);

    hr_hadron_ne_sd->SetLineWidth(4);
    hr_hadron_ne_su->SetLineWidth(3);
    hr_hadron_ne_sc->SetLineWidth(4);
    hr_hadron_ne_sb->SetLineWidth(4);
    hr_hadron_ne_sg->SetLineWidth(4);

    hr_hadron_ch_sd->SetLineWidth(4);
    hr_hadron_ch_su->SetLineWidth(3);
    hr_hadron_ch_sc->SetLineWidth(4);
    hr_hadron_ch_sb->SetLineWidth(4);
    hr_hadron_ch_sg->SetLineWidth(4);

    tdrDraw(hr_hadron_nh_su,"histe", 0, kOrange-3, kSolid,-1,kNone);
    tdrDraw(hr_hadron_nh_sb,"histe", 0, kRed-4, kSolid,-1,kNone);
    tdrDraw(hr_hadron_nh_sd,"histe", 0, kViolet+1, kSolid,-1,kNone);
    tdrDraw(hr_hadron_nh_sg,"histe", 0, kGreen+2, kSolid,-1,kNone);
    tdrDraw(hr_hadron_nh_sc,"histe", 0, kAzure+7, kSolid,-1,kNone);

    tdrDraw(hr_hadron_ne_sg,"histe", 0, kGreen+2, kDotted,-1,kNone);
    tdrDraw(hr_hadron_ne_sc,"histe", 0, kAzure+7, kDotted,-1,kNone);
    tdrDraw(hr_hadron_ne_sd,"histe", 0, kViolet+1, kDotted,-1,kNone);
    tdrDraw(hr_hadron_ne_su,"histe", 0, kOrange-3, kDotted,-1,kNone);
    tdrDraw(hr_hadron_ne_sb,"histe", 0, kRed-4, kDotted,-1,kNone);

    tdrDraw(hr_hadron_ch_sb,"histe", 0, kRed-4, kDashed,-1,kNone);
    tdrDraw(hr_hadron_ch_sd,"histe", 0, kViolet+1, kDashed,-1,kNone);
    tdrDraw(hr_hadron_ch_sc,"histe", 0, kAzure+7, kDashed,-1,kNone);
    tdrDraw(hr_hadron_ch_sg,"histe", 0, kGreen+2, kDashed,-1,kNone);
    tdrDraw(hr_hadron_ch_su,"histe", 0, kOrange-3, kDashed,-1,kNone);




    hr_hadron_ne_sd->SetMarkerSize(1.25);
    hr_hadron_ne_su->SetMarkerSize(1.25);
    hr_hadron_ne_sc->SetMarkerSize(1.25);
    hr_hadron_ne_sb->SetMarkerSize(1.25);
    hr_hadron_ne_sg->SetMarkerSize(1.25);
    

    // Add a legend
    TLegend *leg = tdrLeg(0.89,0.9-0.035*15,1.05,0.91);
    leg->AddEntry(hr_hadron_ne_sd, "d #gamma", "l");
    leg->AddEntry(hr_hadron_ne_su, "u #gamma", "l");
    leg->AddEntry(hr_hadron_ne_sc, "c #gamma", "l");
    leg->AddEntry(hr_hadron_ne_sb, "b #gamma", "l");
    leg->AddEntry(hr_hadron_ne_sg, "g #gamma", "l");

    leg->AddEntry(hr_hadron_nh_sd, "d NH", "l");
    leg->AddEntry(hr_hadron_nh_su, "u NH", "l");
    leg->AddEntry(hr_hadron_nh_sc, "c NH", "l");
    leg->AddEntry(hr_hadron_nh_sb, "b NH", "l");
    leg->AddEntry(hr_hadron_nh_sg, "g NH", "l");

    leg->AddEntry(hr_hadron_ch_sd, "d CH", "l");
    leg->AddEntry(hr_hadron_ch_su, "u CH", "l");
    leg->AddEntry(hr_hadron_ch_sc, "c CH", "l");
    leg->AddEntry(hr_hadron_ch_sb, "b CH", "l");
    leg->AddEntry(hr_hadron_ch_sg, "g CH", "l");
    leg->SetTextSize(0.03);
    leg->Draw();

    // Add labels
    TLatex *tex1 = new TLatex();
    tex1->SetNDC();
    tex1->SetTextSize(0.04);
    tex1->DrawLatex(0.19, 0.75, "|#eta| < 1.3");

    // Update and save the canvas
    c->SetRightMargin(0.11);
    c->RedrawAxis();
    c->Modified();
    c->Update();
    c->SaveAs("energydifference_fraction3.pdf");

    // Clean up
    delete c;
    file->Close();
    delete file;
}