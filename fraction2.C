#include <TH1.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include "tdrstyle_mod22.C"

void fraction2() {
// Open the ROOT file containing the histograms
TFile *file = new TFile("output.root", "READ");
// Retrieve the histograms

// S jets
TH1D *h_k0ls = (TH1D*)file->Get("h_k0ls");
TH1D *h_k0ss = (TH1D*)file->Get("h_k0ss");
TH1D *h_kps = (TH1D*)file->Get("h_kps");
//TH1D *h_k0s = (TH1D*)file->Get("h_k0s");
TH1D *h_pionps = (TH1D*)file->Get("h_pionps");
TH1D *h_pion0s = (TH1D*)file->Get("h_pion0s");
TH1D *h_lambdas = (TH1D*)file->Get("h_lambdas");
TH1D *h_sigma0s = (TH1D*)file->Get("h_sigma0s");
TH1D *h_protons = (TH1D*)file->Get("h_protons");
TH1D *h_neutrons = (TH1D*)file->Get("h_neutrons");
TH1D *h_sall_mod = (TH1D*)file->Get("h_sall_mod");
TH1D *h_s5_mod = (TH1D*)file->Get("h_s5_mod");

// U jets
TH1D *h_k0lu = (TH1D*)file->Get("h_k0lu");
TH1D *h_k0su = (TH1D*)file->Get("h_k0su");
TH1D *h_kpu = (TH1D*)file->Get("h_kpu");
//TH1D *h_k0u = (TH1D*)file->Get("h_k0u");
TH1D *h_pionpu = (TH1D*)file->Get("h_pionpu");
TH1D *h_pion0u = (TH1D*)file->Get("h_pion0u");
TH1D *h_lambdau = (TH1D*)file->Get("h_lambdau");
TH1D *h_sigma0u = (TH1D*)file->Get("h_sigma0u");
TH1D *h_protonu = (TH1D*)file->Get("h_protonu");
TH1D *h_neutronu = (TH1D*)file->Get("h_neutronu");
TH1D *h_uall_mod = (TH1D*)file->Get("h_uall_mod");
TH1D *h_u5_mod = (TH1D*)file->Get("h_u5_mod");

// D jets
TH1D *h_k0ld = (TH1D*)file->Get("h_k0ld");
TH1D *h_k0sd = (TH1D*)file->Get("h_k0sd");
TH1D *h_kpd = (TH1D*)file->Get("h_kpd");
//TH1D *h_k0d = (TH1D*)file->Get("h_k0d");
TH1D *h_pionpd = (TH1D*)file->Get("h_pionpd");
TH1D *h_pion0d = (TH1D*)file->Get("h_pion0d");
TH1D *h_lambdad = (TH1D*)file->Get("h_lambdad");
TH1D *h_sigma0d = (TH1D*)file->Get("h_sigma0d");
TH1D *h_protond = (TH1D*)file->Get("h_protond");
TH1D *h_neutrond = (TH1D*)file->Get("h_neutrond");
TH1D *h_dall_mod = (TH1D*)file->Get("h_dall_mod");
TH1D *h_d5_mod = (TH1D*)file->Get("h_d5_mod");


// Normalize the histograms to percentages
/*
int nK0L = h_k0l->GetEntries();
int nK0S = h_k0s->GetEntries();
int nKp = h_kp->GetEntries();
int nK0 = h_k0->GetEntries();
int nLambda = h_lambda->GetEntries();
int nSigma0 = h_sigma0->GetEntries();

h_s->Scale(1./nSjet);
h_s3->Scale(1./nS3jet);
h_s5->Scale(1./nS5jet);
h_sall->Scale(1./nSall);*/

/*h_s->Scale(1,"width");
h_s3->Scale(1,"width");
h_s5->Scale(1,"width");
h_sall->Scale(1,"width");
*/

TH1D *hrk0ls = (TH1D*)h_k0ls->Clone("hrk0ls");
TH1D *hrk0ss = (TH1D*)h_k0ss->Clone("hrk0ss");
TH1D *hrkps = (TH1D*)h_kps->Clone("hrkps");
//TH1D *hrk0s = (TH1D*)h_k0->Clone("hrk0s");
TH1D *hrlambdas = (TH1D*)h_lambdas->Clone("hrlambdas");
TH1D *hrsigma0s = (TH1D*)h_sigma0s->Clone("hrsigma0s");
TH1D *hrpionps = (TH1D*)h_pionps->Clone("hrpionps");
TH1D *hrpion0s = (TH1D*)h_pion0s->Clone("hrpion0s");
TH1D *hrprotons = (TH1D*)h_protons->Clone("hrprotons");
TH1D *hrneutrons = (TH1D*)h_neutrons->Clone("hrneutrons");
TH1D *hrs5 = (TH1D*)h_s5_mod->Clone("hrs5");

TH1D *hrk0lu = (TH1D*)h_k0lu->Clone("hrk0lu");
TH1D *hrk0su = (TH1D*)h_k0su->Clone("hrk0su");
TH1D *hrkpu = (TH1D*)h_kpu->Clone("hrkpu");
//TH1D *hrk0u = (TH1D*)h_k0u->Clone("hrk0u");
TH1D *hrlambdau = (TH1D*)h_lambdau->Clone("hrlambdau");
TH1D *hrsigma0u = (TH1D*)h_sigma0u->Clone("hrsigma0u");
TH1D *hrpionpu = (TH1D*)h_pionpu->Clone("hrpionpu");
TH1D *hrpion0u = (TH1D*)h_pion0u->Clone("hrpion0u");
TH1D *hrprotonu = (TH1D*)h_protonu->Clone("hrprotonu");
TH1D *hrneutronu = (TH1D*)h_neutronu->Clone("hrneutronu");
TH1D *hru5 = (TH1D*)h_u5_mod->Clone("hru5");

TH1D *hrk0ld = (TH1D*)h_k0ld->Clone("hrk0ld");
TH1D *hrk0sd = (TH1D*)h_k0sd->Clone("hrk0sd");
TH1D *hrkpd = (TH1D*)h_kpd->Clone("hrkpd");
//TH1D *hrk0d = (TH1D*)h_k0d->Clone("hrk0d");
TH1D *hrlambdad = (TH1D*)h_lambdad->Clone("hrlambdad");
TH1D *hrsigma0d = (TH1D*)h_sigma0d->Clone("hrsigma0d");
TH1D *hrpionpd = (TH1D*)h_pionpd->Clone("hrpionpd");
TH1D *hrpion0d = (TH1D*)h_pion0d->Clone("hrpion0d");
TH1D *hrprotond = (TH1D*)h_protond->Clone("hrprotond");
TH1D *hrneutrond = (TH1D*)h_neutrond->Clone("hrneutrond");
TH1D *hrd5 = (TH1D*)h_d5_mod->Clone("hrd5");

TH1D *hrk0ldu = (TH1D*)h_k0lu->Clone("hrk0ldu");
TH1D *hrk0sdu = (TH1D*)h_k0su->Clone("hrk0sdu");
TH1D *hrkpdu = (TH1D*)h_kpu->Clone("hrkpdu");
//TH1D *hrk0du = (TH1D*)h_k0u->Clone("hrk0du");
TH1D *hrlambdadu = (TH1D*)h_lambdau->Clone("hrlambdadu");
TH1D *hrsigma0du = (TH1D*)h_sigma0u->Clone("hrsigma0du");
TH1D *hrpionpdu = (TH1D*)h_pionpu->Clone("hrpionpdu");
TH1D *hrpion0du = (TH1D*)h_pion0u->Clone("hrpion0du");
TH1D *hrdu5 = (TH1D*)h_u5_mod->Clone("hrdu5");

TH1D *hrprotondu = (TH1D*)h_protonu->Clone("hrprotondu");
TH1D *hrneutrondu = (TH1D*)h_neutronu->Clone("hrneutrondu");
TH1D *h_duall_mod = (TH1D*)h_uall_mod->Clone("h_duall_mod");

hrprotondu->Add(h_protond);
hrneutrondu->Add(h_neutrond);
h_duall_mod->Add(h_dall_mod);

hrk0ldu->Add(hrk0ld);
hrk0sdu->Add(hrk0sd);
hrkpdu->Add(hrkpd);
//hrk0du->Add(hrk0d);
hrlambdadu->Add(hrlambdad);
hrsigma0du->Add(hrsigma0d);
hrpionpdu->Add(hrpionpd);
hrpion0du->Add(hrpion0d);
hrdu5->Add(hrd5);


hrk0ls->Divide(h_sall_mod);
hrk0ss->Divide(h_sall_mod);
hrkps->Divide(h_sall_mod);
//hrk0s->Divide(h_sall);
hrlambdas->Divide(h_sall_mod);
hrsigma0s->Divide(h_sall_mod);
hrpionps->Divide(h_sall_mod);
hrpion0s->Divide(h_sall_mod);
hrprotons->Divide(h_sall_mod);
hrneutrons->Divide(h_sall_mod);
hrs5->Divide(h_sall_mod);

hrk0lu->Divide(h_uall_mod);
hrk0su->Divide(h_uall_mod);
hrkpu->Divide(h_uall_mod);
//hrk0u->Divide(h_uall_mod);
hrlambdau->Divide(h_uall_mod);
hrsigma0u->Divide(h_uall_mod);
hrpionpu->Divide(h_uall_mod);
hrpion0u->Divide(h_uall_mod);
hrprotonu->Divide(h_uall_mod);
hrneutronu->Divide(h_uall_mod);
hru5->Divide(h_uall_mod);

hrk0ld->Divide(h_dall_mod);
hrk0sd->Divide(h_dall_mod);
hrkpd->Divide(h_dall_mod);
//hrk0d->Divide(h_dall_mod);
hrlambdad->Divide(h_dall_mod);
hrsigma0d->Divide(h_dall_mod);
hrpionpd->Divide(h_dall_mod);
hrpion0d->Divide(h_dall_mod);
hrprotond->Divide(h_dall_mod);
hrneutrond->Divide(h_dall_mod);
hrd5->Divide(h_dall_mod);

hrk0ldu->Divide(h_duall_mod);
hrk0sdu->Divide(h_duall_mod);
hrkpdu->Divide(h_duall_mod);
//hrk0du->Divide(h_duall_mod);
hrlambdadu->Divide(h_duall_mod);
hrsigma0du->Divide(h_duall_mod);
hrpionpdu->Divide(h_duall_mod);
hrpion0du->Divide(h_duall_mod);
hrprotondu->Divide(h_duall_mod);
hrneutrondu->Divide(h_duall_mod);
hrdu5->Divide(h_duall_mod);

// Create a stack
//setTDRStyle();
//lumi_136TeV = "Run3";
//extraText = "Private";
//TH1D *h1 = tdrHist("h","Jet p_{T} fraction (S-U)",-0.06 + 1e-4,0.10 -1e-4,"p_{T,cand} (GeV)",0.1,100);
//TCanvas *c1 = tdrCanvas("c1",h1,8,kSquare);
//c1->SetLogx();
THStack *hs = new THStack("hs", "; p_{T,cand} (GeV); S Jet N fraction");
//hs->GetXaxis()->SetTitleSize(0.05);
//hs->GetYaxis()->SetTitleSize(0.05);
//hs->GetXaxis()->SetTitleOffset(1.2);
//hs->GetYaxis()->SetTitleOffset(1.2);

// Set histogram fill colors and add to stack
hrs5->SetFillColor(kBlue-9);
hrk0ls->SetFillColor(kOrange-3);
hrk0ss->SetFillColor(kRed-7);
hrkps->SetFillColor(kOrange-2);
//hrk0s->SetFillColor(kOrange);
hrlambdas->SetFillColor(kAzure+7);
hrpionps->SetFillColor(kGreen-6);
hrprotons->SetFillColor(kViolet-4);
hrneutrons->SetFillColor(kPink+6);
//hrpion0s->SetFillColor(kViolet-4);
//hrsigma0s->SetFillColor(kPink+6);


// Add histograms to the stack
hs->Add(hrk0ss);
hs->Add(hrk0ls);
hs->Add(hrkps);
//hs->Add(hrk0s);
hs->Add(hrpionps);
hs->Add(hrlambdas);
//hs->Add(hrpion0s);
//hs->Add(hrsigma0s);
hs->Add(hrs5);
hs->Add(hrprotons);
hs->Add(hrneutrons);


// Draw the stack
TCanvas *c1 = new TCanvas("c1", "Pt fractions for S", 800, 600);
c1->SetLogx();
hs->Draw("hist");

gPad->SetBottomMargin(0.14);
gPad->Update();
TH1 *h = hs->GetHistogram();
h->GetXaxis()->SetTitleSize(0.06);
h->GetXaxis()->SetTitleOffset(1.07);
h->GetYaxis()->SetTitleSize(0.06);
h->GetYaxis()->SetTitleOffset(0.7);
h->GetXaxis()->SetLabelSize(0.05); 
h->GetYaxis()->SetLabelSize(0.05); 

// Create legend
TLegend *leg = tdrLeg(0.9,0.79-0.025*8,1.1,0.9);
leg->AddEntry(hrneutrons, "p", "f");
leg->AddEntry(hrprotons, "n", "f");
leg->AddEntry(hrs5, "#gamma", "f");
leg->AddEntry(hrlambdas, "#Lambda", "f");
leg->AddEntry(hrpionps, "#pi^{+/-}", "f");
leg->AddEntry(hrkps, "K^{+/-}", "f");
leg->AddEntry(hrk0ls, "K^{0}_{L}", "f");
leg->AddEntry(hrk0ss, "K^{0}_{S}", "f");
//leg->AddEntry(hrk0s, "K^0", "f");
//leg->AddEntry(hrsigma0s, "#Sigma^{0}", "f");
//leg->AddEntry(hrpion0s, "#pi^{0}", "f");
leg->SetTextFont(132);
leg->SetTextSize(0.03);
leg->Draw();

TLatex *tex1 = new TLatex();
tex1->SetNDC(); tex1->SetTextSize(0.035);
tex1->DrawLatex(0.15,0.77,"|#eta| < 1.3");
tex1->DrawLatex(0.15,0.72,"60 < p_{T,jet} < 140 GeV");

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
// Assuming the x-axis categories are correctly set when histograms were created
// If you need to set labels for the x-axis categories, do it here

// Update the canvas to reflect changes
c1->RedrawAxis();
c1->Modified();
c1->Update();
c1->SaveAs("pdf/fractions2S.pdf");



















THStack *hdu = new THStack("hdu", "; p_{T,cand} (GeV); U & D Jet N fraction");
//hs->GetXaxis()->SetTitleSize(0.05);
//hs->GetYaxis()->SetTitleSize(0.05);
//hs->GetXaxis()->SetTitleOffset(1.2);
//hs->GetYaxis()->SetTitleOffset(1.2);

// Set histogram fill colors and add to stack
hrdu5->SetFillColor(kBlue-9);
hrk0ldu->SetFillColor(kOrange-3);
hrk0sdu->SetFillColor(kRed-7);
hrkpdu->SetFillColor(kOrange-2);
//hrk0du->SetFillColor(kOrange);
hrlambdadu->SetFillColor(kAzure+7);
hrpionpdu->SetFillColor(kGreen-6);
hrprotondu->SetFillColor(kViolet-4);
hrneutrondu->SetFillColor(kPink+6);
//hrpion0du->SetFillColor(kViolet-4);
//hrsigma0du->SetFillColor(kPink+6);


// Add histograms to the stack
hdu->Add(hrk0sdu);
hdu->Add(hrk0ldu);
hdu->Add(hrkpdu);
//hdu->Add(hrk0du);
hdu->Add(hrpionpdu);
hdu->Add(hrlambdadu);
//hdu->Add(hrpion0du);
//hdu->Add(hrsigma0du);
hdu->Add(hrdu5);
hdu->Add(hrprotondu);
hdu->Add(hrneutrondu);

// Draw the stack
TCanvas *c2 = new TCanvas("c2", "Pt fractions for S", 800, 600);
c2->SetLogx();
hdu->Draw("hist");

gPad->SetBottomMargin(0.14);
gPad->Update();
TH1 *h2 = hdu->GetHistogram();
h2->GetXaxis()->SetTitleSize(0.06);
h2->GetXaxis()->SetTitleOffset(1.07);
h2->GetYaxis()->SetTitleSize(0.06);
h2->GetYaxis()->SetTitleOffset(0.7);
h2->GetXaxis()->SetLabelSize(0.05); 
h2->GetYaxis()->SetLabelSize(0.05); 

// Create legend
TLegend *leg2 = tdrLeg(0.9,0.79-0.025*8,1.1,0.9);
leg2->AddEntry(hrneutrondu, "p", "f");
leg2->AddEntry(hrprotondu, "n", "f");
leg2->AddEntry(hrdu5, "#gamma", "f");
leg2->AddEntry(hrlambdadu, "#Lambda", "f");
leg2->AddEntry(hrpionpdu, "#pi^{+/-}", "f");
leg2->AddEntry(hrkpdu, "K^{+/-}", "f");
leg2->AddEntry(hrk0ldu, "K^{0}_{L}", "f");
leg2->AddEntry(hrk0sdu, "K^{0}_{S}", "f");
//leg2->AddEntry(hrk0du, "K^0", "f");
leg2->AddEntry(hrsigma0du, "#Sigma^{0}", "f");
leg2->AddEntry(hrpion0du, "#pi^{0}", "f");
leg2->SetTextFont(132);
leg2->SetTextSize(0.03);
leg2->Draw();

TLatex *tex21 = new TLatex();
tex21->SetNDC(); tex21->SetTextSize(0.035);
tex21->DrawLatex(0.15,0.77,"|#eta| < 1.3");
tex21->DrawLatex(0.15,0.72,"60 < p_{T,jet} < 140 GeV");

TLatex *tex22 = new TLatex();
tex22->SetNDC(); tex22->SetTextSize(0.065);
tex22->DrawLatex(0.1,0.92,"CMS");

TLatex *tex23 = new TLatex();
tex23->SetNDC(); tex23->SetTextSize(0.05);
tex23->SetTextFont(42);
tex23->DrawLatex(0.65,0.92,"Run3 (13.6 TeV)");

TLatex *tex24 = new TLatex();
tex24->SetNDC(); tex24->SetTextSize(0.045);
tex24->SetTextFont(52);
tex24->DrawLatex(0.15,0.83,"Private");
// Assuming the x-axis categories are correctly set when histograms were created
// If you need to set labels for the x-axis categories, do it here

// Update the canvas to reflect changes
c2->RedrawAxis();
c2->Modified();
c2->Update();
c2->SaveAs("pdf/fractions2UD.pdf");









THStack *hu = new THStack("hu", "; p_{T,cand} (GeV); U Jet N fraction");
//hs->GetXaxis()->SetTitleSize(0.05);
//hs->GetYaxis()->SetTitleSize(0.05);
//hs->GetXaxis()->SetTitleOffset(1.2);
//hs->GetYaxis()->SetTitleOffset(1.2);

// Set histogram fill colors and add to stack
hru5->SetFillColor(kBlue-9);
hrk0lu->SetFillColor(kOrange-3);
hrk0su->SetFillColor(kRed-7);
hrkpu->SetFillColor(kOrange-2);
//hrk0u->SetFillColor(kOrange);
hrlambdau->SetFillColor(kAzure+7);
hrpionpu->SetFillColor(kGreen-6);
hrprotonu->SetFillColor(kViolet-4);
hrneutronu->SetFillColor(kPink+6);
//hrpion0u->SetFillColor(kViolet-4);
//hrsigma0u->SetFillColor(kPink+6);


// Add histograms to the stack
hu->Add(hrk0su);
hu->Add(hrk0lu);
hu->Add(hrkpu);
//hu->Add(hrk0u);
hu->Add(hrpionpu);
hu->Add(hrlambdau);
//hu->Add(hrpion0u);
//hu->Add(hrsigma0u);
hu->Add(hru5);
hu->Add(hrprotonu);
hu->Add(hrneutronu);

// Draw the stack
TCanvas *c3 = new TCanvas("c3", "Pt fractions for S", 800, 600);
c3->SetLogx();
hu->Draw("hist");

gPad->SetBottomMargin(0.14);
gPad->Update();
TH1 *h3 = hu->GetHistogram();
h3->GetXaxis()->SetTitleSize(0.06);
h3->GetXaxis()->SetTitleOffset(1.07);
h3->GetYaxis()->SetTitleSize(0.06);
h3->GetYaxis()->SetTitleOffset(0.7);
h3->GetXaxis()->SetLabelSize(0.05); 
h3->GetYaxis()->SetLabelSize(0.05); 

// Create legend
TLegend *leg3 = tdrLeg(0.9,0.79-0.025*8,1.1,0.9);
leg3->AddEntry(hrneutronu, "p", "f");
leg3->AddEntry(hrprotonu, "n", "f");
leg3->AddEntry(hru5, "#gamma", "f");
leg3->AddEntry(hrlambdau, "#Lambda", "f");
leg3->AddEntry(hrpionpu, "#pi^{+/-}", "f");
leg3->AddEntry(hrkpu, "K^{+/-}", "f");
leg3->AddEntry(hrk0lu, "K^{0}_{L}", "f");
leg3->AddEntry(hrk0su, "K^{0}_{S}", "f");
//leg3->AddEntry(hrk0u, "K^0", "f");
leg3->AddEntry(hrsigma0u, "#Sigma^{0}", "f");
leg3->AddEntry(hrpion0u, "#pi^{0}", "f");
leg3->SetTextFont(132);
leg3->SetTextSize(0.03);
leg3->Draw();

TLatex *tex31 = new TLatex();
tex31->SetNDC(); tex31->SetTextSize(0.035);
tex31->DrawLatex(0.15,0.77,"|#eta| < 1.3");
tex31->DrawLatex(0.15,0.72,"60 < p_{T,jet} < 140 GeV");

TLatex *tex32 = new TLatex();
tex32->SetNDC(); tex32->SetTextSize(0.065);
tex32->DrawLatex(0.1,0.92,"CMS");

TLatex *tex33 = new TLatex();
tex33->SetNDC(); tex33->SetTextSize(0.05);
tex33->SetTextFont(42);
tex33->DrawLatex(0.65,0.92,"Run3 (13.6 TeV)");

TLatex *tex34 = new TLatex();
tex34->SetNDC(); tex34->SetTextSize(0.045);
tex34->SetTextFont(52);
tex34->DrawLatex(0.15,0.83,"Private");
// Assuming the x-axis categories are correctly set when histograms were created
// If you need to set labels for the x-axis categories, do it here

// Update the canvas to reflect changes
c3->RedrawAxis();
c3->Modified();
c3->Update();
c3->SaveAs("pdf/fractions2U.pdf");










THStack *hd = new THStack("hd", "; p_{T,cand} (GeV); D Jet N fraction");
//hs->GetXaxis()->SetTitleSize(0.05);
//hs->GetYaxis()->SetTitleSize(0.05);
//hs->GetXaxis()->SetTitleOffset(1.2);
//hs->GetYaxis()->SetTitleOffset(1.2);

// Set histogram fill colors and add to stack
hrd5->SetFillColor(kBlue-9);
hrk0ld->SetFillColor(kOrange-3);
hrk0sd->SetFillColor(kRed-7);
hrkpd->SetFillColor(kOrange-2);
//hrk0d->SetFillColor(kOrange);
hrlambdad->SetFillColor(kAzure+7);
hrpionpd->SetFillColor(kGreen-6);
hrprotond->SetFillColor(kViolet-4);
hrneutrond->SetFillColor(kPink+6);
//hrpion0d->SetFillColor(kViolet-4);
//hrsigma0d->SetFillColor(kPink+6);


// Add histograms to the stack
hd->Add(hrk0sd);
hd->Add(hrk0ld);
hd->Add(hrkpd);
//hd->Add(hrk0d);
hd->Add(hrpionpd);
hd->Add(hrlambdad);
//hd->Add(hrpion0d);
//hd->Add(hrsigma0d);
hd->Add(hrd5);
hd->Add(hrprotond);
hd->Add(hrneutrond);

// Draw the stack
TCanvas *c4 = new TCanvas("c4", "Pt fractions for S", 800, 600);
c4->SetLogx();
hd->Draw("hist");

gPad->SetBottomMargin(0.14);
gPad->Update();
TH1 *h4 = hd->GetHistogram();
h4->GetXaxis()->SetTitleSize(0.06);
h4->GetXaxis()->SetTitleOffset(1.07);
h4->GetYaxis()->SetTitleSize(0.06);
h4->GetYaxis()->SetTitleOffset(0.7);
h4->GetXaxis()->SetLabelSize(0.05); 
h4->GetYaxis()->SetLabelSize(0.05); 

// Create legend
TLegend *leg4 = tdrLeg(0.9,0.79-0.025*8,1.1,0.9);
leg4->AddEntry(hrneutrond, "p", "f");
leg4->AddEntry(hrprotond, "n", "f");
leg4->AddEntry(hrd5, "#gamma", "f");
leg4->AddEntry(hrlambdad, "#Lambda", "f");
leg4->AddEntry(hrpionpd, "#pi^{+/-}", "f");
leg4->AddEntry(hrkpd, "K^{+/-}", "f");
leg4->AddEntry(hrk0ld, "K^{0}_{L}", "f");
leg4->AddEntry(hrk0sd, "K^{0}_{S}", "f");
//leg4->AddEntry(hrk0d, "K^0", "f");
leg4->AddEntry(hrsigma0d, "#Sigma^{0}", "f");
leg4->AddEntry(hrpion0d, "#pi^{0}", "f");
leg4->SetTextFont(132);
leg4->SetTextSize(0.03);
leg4->Draw();

TLatex *tex41 = new TLatex();
tex41->SetNDC(); tex41->SetTextSize(0.035);
tex41->DrawLatex(0.15,0.77,"|#eta| < 1.3");
tex41->DrawLatex(0.15,0.72,"60 < p_{T,jet} < 140 GeV");

TLatex *tex42 = new TLatex();
tex42->SetNDC(); tex42->SetTextSize(0.065);
tex42->DrawLatex(0.1,0.92,"CMS");

TLatex *tex43 = new TLatex();
tex43->SetNDC(); tex43->SetTextSize(0.05);
tex43->SetTextFont(42);
tex43->DrawLatex(0.65,0.92,"Run3 (13.6 TeV)");

TLatex *tex44 = new TLatex();
tex44->SetNDC(); tex44->SetTextSize(0.045);
tex44->SetTextFont(52);
tex44->DrawLatex(0.15,0.83,"Private");
// Assuming the x-axis categories are correctly set when histograms were created
// If you need to set labels for the x-axis categories, do it here

// Update the canvas to reflect changes
c4->RedrawAxis();
c4->Modified();
c4->Update();
c4->SaveAs("pdf/fractions2D.pdf");

// Do not close the file if you want to interact with the histograms further
// file->Close(); // Uncomment this if you're done with the file
}