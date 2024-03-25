void fraction2() {
// Open the ROOT file containing the histograms
TFile *file = new TFile("output.root", "READ");
// Retrieve the histograms


// U jets
TH1D *h_pionp_u_vs_ptcand = (TH1D*)file->Get("h_pionp_u_vs_ptcand");
TH1D *h_pionm_u_vs_ptcand = (TH1D*)file->Get("h_pionm_u_vs_ptcand");
TH1D *h_kaonp_u_vs_ptcand = (TH1D*)file->Get("h_kaonp_u_vs_ptcand");
TH1D *h_kaonm_u_vs_ptcand = (TH1D*)file->Get("h_kaonm_u_vs_ptcand");
TH1D *h_sigmapm_u_vs_ptcand = (TH1D*)file->Get("h_sigmapm_u_vs_ptcand");
TH1D *h_proton_u_vs_ptcand = (TH1D*)file->Get("h_proton_u_vs_ptcand");
TH1D *h_antiproton_u_vs_ptcand = (TH1D*)file->Get("h_antiproton_u_vs_ptcand");
TH1D *h_neutron_u_vs_ptcand = (TH1D*)file->Get("h_neutron_u_vs_ptcand");
TH1D *h_antineutron_u_vs_ptcand = (TH1D*)file->Get("h_antineutron_u_vs_ptcand");
TH1D *h_kaon0l_u_vs_ptcand = (TH1D*)file->Get("h_kaon0l_u_vs_ptcand");
TH1D *h_kaon0s_u_vs_ptcand = (TH1D*)file->Get("h_kaon0s_u_vs_ptcand");
TH1D *h_lambdapm_u_vs_ptcand = (TH1D*)file->Get("h_lambdapm_u_vs_ptcand");
TH1D *h_xiomega_u_vs_ptcand = (TH1D*)file->Get("h_xiomega_u_vs_ptcand");
TH1D *h_photon_u_vs_ptcand = (TH1D*)file->Get("h_photon_u_vs_ptcand");
TH1D *h_electron_u_vs_ptcand = (TH1D*)file->Get("h_electron_u_vs_ptcand");
TH1D *h_muon_u_vs_ptcand = (TH1D*)file->Get("h_muon_u_vs_ptcand");

TH1D *h_all_u_vs_ptcand = (TH1D*)file->Get("h_all_u_vs_ptcand");

// D jets
TH1D *h_pionp_d_vs_ptcand = (TH1D*)file->Get("h_pionp_d_vs_ptcand");
TH1D *h_pionm_d_vs_ptcand = (TH1D*)file->Get("h_pionm_d_vs_ptcand");
TH1D *h_kaonp_d_vs_ptcand = (TH1D*)file->Get("h_kaonp_d_vs_ptcand");
TH1D *h_kaonm_d_vs_ptcand = (TH1D*)file->Get("h_kaonm_d_vs_ptcand");
TH1D *h_sigmapm_d_vs_ptcand = (TH1D*)file->Get("h_sigmapm_d_vs_ptcand");
TH1D *h_proton_d_vs_ptcand = (TH1D*)file->Get("h_proton_d_vs_ptcand");
TH1D *h_antiproton_d_vs_ptcand = (TH1D*)file->Get("h_antiproton_d_vs_ptcand");
TH1D *h_neutron_d_vs_ptcand = (TH1D*)file->Get("h_neutron_d_vs_ptcand");
TH1D *h_antineutron_d_vs_ptcand = (TH1D*)file->Get("h_antineutron_d_vs_ptcand");
TH1D *h_kaon0l_d_vs_ptcand = (TH1D*)file->Get("h_kaon0l_d_vs_ptcand");
TH1D *h_kaon0s_u_vs_ptcand = (TH1D*)file->Get("h_kaon0s_d_vs_ptcand");
TH1D *h_lambdapm_u_vs_ptcand = (TH1D*)file->Get("h_lambdapm_d_vs_ptcand");
TH1D *h_xiomega_d_vs_ptcand = (TH1D*)file->Get("h_xiomega_d_vs_ptcand");
TH1D *h_photon_d_vs_ptcand = (TH1D*)file->Get("h_photon_d_vs_ptcand");
TH1D *h_electron_d_vs_ptcand = (TH1D*)file->Get("h_electron_d_vs_ptcand");
TH1D *h_muon_d_vs_ptcand = (TH1D*)file->Get("h_muon_d_vs_ptcand");


TH1D *hrk0ldu = (TH1D*)h_kaon0lu->Clone("hrk0ldu");
TH1D *hr_pionp_ud_vs_ptcand = (TH1D*)h_pionp_u_vs_ptcand->Clone("h_pionp_u_vs_ptcand");
TH1D *hr_pionm_ud_vs_ptcand = (TH1D*)h_pionm_u_vs_ptcand->Clone("h_pionm_u_vs_ptcand");
TH1D *hr_kaonp_ud_vs_ptcand = (TH1D*)h_kaonp_u_vs_ptcand->Clone("h_kaonp_u_vs_ptcand");
TH1D *hr_kaonm_ud_vs_ptcand = (TH1D*)h_kaonm_u_vs_ptcand->Clone("h_kaonm_u_vs_ptcand");
TH1D *hr_sigmapm_ud_vs_ptcand = (TH1D*)h_sigmapm_u_vs_ptcand->Clone("h_sigmapm_u_vs_ptcand");
TH1D *hr_proton_ud_vs_ptcand = (TH1D*)h_proton_u_vs_ptcand->Clone("h_proton_u_vs_ptcand");
TH1D *hr_antiproton_ud_vs_ptcand = (TH1D*)h_antiproton_u_vs_ptcand->Clone("h_antiproton_u_vs_ptcand");
TH1D *hr_neutron_ud_vs_ptcand = (TH1D*)h_neutron_u_vs_ptcand->Clone("h_neutron_u_vs_ptcand");
TH1D *hr_antineutron_ud_vs_ptcand = (TH1D*)h_antineutron_u_vs_ptcand->Clone("h_antineutron_u_vs_ptcand");
TH1D *hr_kaon0l_ud_vs_ptcand = (TH1D*)h_kaon0l_u_vs_ptcand->Clone("h_kaon0l_u_vs_ptcand");
TH1D *hr_kaon0s_ud_vs_ptcand = (TH1D*)h_kaon0s_u_vs_ptcand->Clone("h_kaon0s_u_vs_ptcand");
TH1D *hr_lambdapm_ud_vs_ptcand = (TH1D*)h_lambdapm_u_vs_ptcand->Clone("h_lambdapm_u_vs_ptcand");
TH1D *hr_xiomega_ud_vs_ptcand = (TH1D*)h_xiomega_u_vs_ptcand->Clone("h_xiomega_u_vs_ptcand");
TH1D *hr_photon_ud_vs_ptcand = (TH1D*)h_photon_u_vs_ptcand->Clone("h_photon_u_vs_ptcand");
TH1D *hr_electron_ud_vs_ptcand = (TH1D*)h_electron_u_vs_ptcand->Clone("h_electron_u_vs_ptcand");
TH1D *hr_muon_ud_vs_ptcand = (TH1D*)h_muon_u_vs_ptcand->Clone("h_muon_u_vs_ptcand");

TH1D *hr_all_ud_vs_ptcand = (TH1D*)h_all_u_vs_ptcand->Clone("h_all_u_vs_ptcand");

hrprotondu->Add(h_protond);
hr_pionp_ud_vs_ptcand ->Add(h_pionp_d_vs_ptcand);
hr_pionm_ud_vs_ptcand ->Add(h_pionm_d_vs_ptcand);
hr_kaonp_ud_vs_ptcand ->Add(h_kaonp_d_vs_ptcand);
hr_kaonm_ud_vs_ptcand ->Add(h_kaonm_d_vs_ptcand);
hr_sigmapm_ud_vs_ptcand ->Add(h_sigmapm_d_vs_ptcand);
hr_proton_ud_vs_ptcand ->Add(h_proton_d_vs_ptcand);
hr_antiproton_ud_vs_ptcand ->Add(h_antiproton_d_vs_ptcand);
hr_neutron_ud_vs_ptcand ->Add(h_neutron_d_vs_ptcand);
hr_antineutron_ud_vs_ptcand ->Add(h_antineutron_d_vs_ptcand);
hr_kaon0l_ud_vs_ptcand ->Add(h_kaon0l_d_vs_ptcand);
hr_kaon0s_ud_vs_ptcand ->Add(h_kaon0s_d_vs_ptcand);
hr_lambdapm_ud_vs_ptcand ->Add(h_lambdapm_d_vs_ptcand);
hr_xiomega_ud_vs_ptcand ->Add(h_xiomega_d_vs_ptcand);
hr_photon_ud_vs_ptcand ->Add(h_photon_d_vs_ptcand);
hr_electron_ud_vs_ptcand ->Add(h_electron_d_vs_ptcand);
hr_muon_ud_vs_ptcand ->Add(h_muon_d_vs_ptcand);

hr_all_ud_vs_ptcand ->Add(h_all_d_vs_ptcand);

hr_pionp_ud_vs_ptcand ->Divide(hr_all_ud_vs_ptcand);
hr_pionm_ud_vs_ptcand ->Divide(hr_all_ud_vs_ptcand);
hr_kaonp_ud_vs_ptcand ->Divide(hr_all_ud_vs_ptcand);
hr_kaonm_ud_vs_ptcand ->Divide(hr_all_ud_vs_ptcand);
hr_sigmapm_ud_vs_ptcand ->Divide(hr_all_ud_vs_ptcand);
hr_proton_ud_vs_ptcand ->Divide(hr_all_ud_vs_ptcand);
hr_antiproton_ud_vs_ptcand ->Divide(hr_all_ud_vs_ptcand);
hr_neutron_ud_vs_ptcand ->Divide(hr_all_ud_vs_ptcand);
hr_antineutron_ud_vs_ptcand ->Divide(hr_all_ud_vs_ptcand);
hr_kaon0l_ud_vs_ptcand ->Divide(hr_all_ud_vs_ptcand);
hr_kaon0s_ud_vs_ptcand ->Divide(hr_all_ud_vs_ptcand);
hr_lambdapm_ud_vs_ptcand ->Divide(hr_all_ud_vs_ptcand);
hr_xiomega_ud_vs_ptcand ->Divide(hr_all_ud_vs_ptcand);
hr_photon_ud_vs_ptcand ->Divide(hr_all_ud_vs_ptcand);
hr_electron_ud_vs_ptcand ->Divide(hr_all_ud_vs_ptcand);
hr_muon_ud_vs_ptcand ->Divide(hr_all_ud_vs_ptcand);

setTDRStyle();
lumi_136TeV = "Run3";
extraText = "Private";
TH1D *h2 = tdrHist("h2","UD jet N fraction",0 + 1e-4,1,"p_{T,cand} (GeV)",0.1,100);
TCanvas *c2 = tdrCanvas("c2",h2,8,kSquare);
c2->SetLogx();

THStack *hdu = new THStack("hdu", "; p_{T,cand} (GeV); U & D Jet N fraction");

// Set histogram fill colors and add to stack

hr_pionp_ud_vs_ptcand ->SetFillColor(kRed-10);
hr_pionm_ud_vs_ptcand ->SetFillColor(kRed-9);
hr_kaonp_ud_vs_ptcand ->SetFillColor(kRed-7);
hr_kaonm_ud_vs_ptcand ->SetFillColor(kRed-6);
hr_sigmapm_ud_vs_ptcand ->SetFillColor(kMagenta-10);
hr_proton_ud_vs_ptcand ->SetFillColor(kMagenta-9);
hr_antiproton_ud_vs_ptcand ->SetFillColor(kMagenta-7);
hr_neutron_ud_vs_ptcand ->SetFillColor(kGreen-10);
hr_antineutron_ud_vs_ptcand ->SetFillColor(kGreen-9);
hr_kaon0l_ud_vs_ptcand ->SetFillColor(kGreen-6);
hr_kaon0s_ud_vs_ptcand ->SetFillColor(kGreen-7);
hr_lambdapm_ud_vs_ptcand ->SetFillColor(kTeal-9);
hr_xiomega_ud_vs_ptcand ->SetFillColor(kAzure+8);
hr_photon_ud_vs_ptcand ->SetFillColor(kBlue-9);
hr_electron_ud_vs_ptcand ->SetFillColor(kCyan-9);
hr_muon_ud_vs_ptcand ->SetFillColor(kOrange-9);


// Add histograms to the stack

hdu->Add(hr_pionp_ud_vs_ptcand);
hdu->Add(hr_pionm_ud_vs_ptcand);
hdu->Add(hr_kaonp_ud_vs_ptcand);
hdu->Add(hr_kaonm_ud_vs_ptcand);
hdu->Add(hr_sigmapm_ud_vs_ptcand);
hdu->Add(hr_proton_ud_vs_ptcand);
hdu->Add(hr_antiproton_ud_vs_ptcand);
hdu->Add(hr_neutron_ud_vs_ptcand);
hdu->Add(hr_antineutron_ud_vs_ptcand);
hdu->Add(hr_kaon0l_ud_vs_ptcand);
hdu->Add(hr_kaon0s_ud_vs_ptcand);
hdu->Add(hr_lambdapm_ud_vs_ptcand);
hdu->Add(hr_xiomega_ud_vs_ptcand);
hdu->Add(hr_photon_ud_vs_ptcand);
hdu->Add(hr_electron_ud_vs_ptcand);
hdu->Add(hr_muon_ud_vs_ptcand);


hdu->Draw("hist same");

gPad->SetBottomMargin(0.14);
gPad->SetRightMargin(0.1);
gPad->Update();

// Create legend
TLegend *leg2 = tdrLeg(0.9,0.79-0.04*14,1.1,0.9);
//leg2->AddEntry(hrmuonu, "#mu", "f");
leg2->AddEntry(hr_muon_ud_vs_ptcand, "e, #mu", "f");
leg2->AddEntry(hr_electron_ud_vs_ptcand, "#gamma", "f");
leg2->AddEntry(hr_photon_ud_vs_ptcand, "#Lambda", "f");
leg2->AddEntry(hr_xiomega_ud_vs_ptcand, "K_{L}", "f");
leg2->AddEntry(hr_lambdapm_ud_vs_ptcand, "K_{S}", "f");
leg2->AddEntry(hr_kaon0s_ud_vs_ptcand, "#bar{n}", "f");
leg2->AddEntry(hr_kaon0l_ud_vs_ptcand, "n", "f");
leg2->AddEntry(hr_antineutron_ud_vs_ptcand, "#bar{p}", "f");
leg2->AddEntry(hr_neutron_ud_vs_ptcand, "p", "f");
leg2->AddEntry(hr_antiproton_ud_vs_ptcand, "#Sigma^{+/-}", "f");
leg2->AddEntry(hr_proton_ud_vs_ptcand, "#Sigma^{-}", "f");
leg2->AddEntry(hr_sigmapm_ud_vs_ptcand, "K^{-}", "f");
leg2->AddEntry(hr_kaonm_ud_vs_ptcand, "K^{+}", "f");
leg2->AddEntry(hr_kaonp_ud_vs_ptcand, "#pi^{-}", "f");
leg2->AddEntry(hr_pionm_ud_vs_ptcand, "#pi^{+}", "f");
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
c2->SaveAs("pdf/fractions2_du.pdf");
