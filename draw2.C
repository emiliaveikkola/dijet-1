#include "tdrstyle_mod22.C"

  void draw(){
  TFile *f = new TFile("output.root","read");

  TH1D *h_k0l = (TH1D*) f->Get("h_k0l");
  TH1D *h_k0s = (TH1D*) f->Get("h_k0s");
  TH1D *h_kp = (TH1D*) f->Get("h_kp");
  TH1D *h_k0 = (TH1D*) f->Get("h_k0");
  TH1D *h_lambda = (TH1D*) f->Get("h_lambda");
  TH1D *h_sigma0 = (TH1D*) f->Get("h_sigma0");

  TH1D *h_k0l2 = (TH1D*) f->Get("h_k0l2");
  TH1D *h_k0s2 = (TH1D*) f->Get("h_k0s2");
  TH1D *h_kp2 = (TH1D*) f->Get("h_kp2");
  TH1D *h_k02 = (TH1D*) f->Get("h_k02");
  TH1D *h_lambda2 = (TH1D*) f->Get("h_lambda2");
  TH1D *h_sigma02 = (TH1D*) f->Get("h_sigma02");

  TH1D *h_dusall = (TH1D*) f->Get("h_dusall");

   int nKaonp = h_kp->GetEntries();
   int nKaon0 = h_k0->GetEntries();
   int nKaonL = h_k0l->GetEntries();
   int nKaonS = h_k0s->GetEntries();
   int nLambda = h_lambda->GetEntries();
   int nSigma = h_sigma0->GetEntries();

    int nKaonp2 = h_kp2->GetEntries();
   int nKaon02 = h_k02->GetEntries();
   int nKaonL2 = h_k0l2->GetEntries();
   int nKaonS2 = h_k0s2->GetEntries();
   int nLambda2 = h_lambda2->GetEntries();
   int nSigma2 = h_sigma02->GetEntries();

  // Normalizing with number of jets
	h_kp->Scale(1./nKaonp);
	h_k0->Scale(1./nKaon0);
	h_k0l->Scale(1./nKaonL);
  h_k0s->Scale(1./nKaonS);
  h_lambda->Scale(1./nLambda);
  h_sigma0->Scale(1./nSigma);

  h_kp2->Scale(1./nKaonp2);
	h_k02->Scale(1./nKaon02);
	h_k0l2->Scale(1./nKaonL2);
  h_k0s2->Scale(1./nKaonS2);
  h_lambda2->Scale(1./nLambda2);
  h_sigma02->Scale(1./nSigma2);

  // Normalizing with the width of the x-axis
    h_kp->Scale(1,"width");
	h_k0->Scale(1,"width");
	h_k0l->Scale(1,"width");
    h_k0s->Scale(1,"width");
    h_lambda->Scale(1,"width");
	h_sigma0->Scale(1,"width");

    h_kp2->Scale(1,"width");
	h_k02->Scale(1,"width");
	h_k0l2->Scale(1,"width");
    h_k0s2->Scale(1,"width");
    h_lambda2->Scale(1,"width");
	h_sigma02->Scale(1,"width");

/*	// The mean and mean error for each histogram
	double meanD = h_d->GetMean();
	double meanErrorD = h_d->GetMeanError();

	double meanU = h_u->GetMean();
	double meanErrorU = h_u->GetMeanError();

	double meanS = h_s->GetMean();
	double meanErrorS = h_s->GetMeanError();


	// Print or use the means and mean errors as needed
	cout << "Mean D: " << meanD << " +/- " << meanErrorD << endl;
	cout << "Mean U: " << meanU << " +/- " << meanErrorU << endl;
	cout << "Mean S: " << meanS << " +/- " << meanErrorS << endl; */
  
  // Create a TCanvas
  //TCanvas *canvas1 = new TCanvas("canvas1", "Particle Candidates in Jets", 800, 600);
  //canvas1->SetLogy();
  //canvas1->SetLogx();

  //TCanvas *canvas2 = new TCanvas("canvas2", "Particle Candidates in Jets", 800, 600);
  //canvas2->SetLogy();
  //canvas2->SetLogx();

  setTDRStyle(); // Apply the CMS TDR style settings if you have this function defined

  // Create a canvas and divide it into two pads
    //TCanvas *canvas = new TCanvas("canvas", "Canvas Title", 800, 600);
    //canvas->Divide(1, 2);


  // Set line colors for each histogram
  /*h_d->SetLineColor(kRed);
  h_u->SetLineColor(kBlue);
  h_s->SetLineColor(kGreen);
  h_d2->SetLineColor(kPink);
  h_u2->SetLineColor(kViolet);
  h_s2->SetLineColor(kTeal);*/
  
 
  
  // Draw histograms with lines and add entries to the legend
  /*h_d->Draw("HE");
  legend->AddEntry(h_d, "D GenJets", "l");
  
  h_u->Draw("HESAME");
  legend->AddEntry(h_u, "U GenJets", "l");
  
  h_s->Draw("HESAME");
  legend->AddEntry(h_s, "S GenJets", "l");*/
  
  /*h_d2->Draw("LSAME");
     legend->AddEntry(h_d2, "D RecoJets", "l");
     
     h_u2->Draw("LSAME");
     legend->AddEntry(h_u2, "U RecoJets", "l");
     
     h_s2->Draw("LSAME");
     legend->AddEntry(h_s2, "S RecoJets", "l");*/
  
  

  // Normalizing with number of jets
	/*h_u->Scale(1./nUjet);
	h_s->Scale(1./nSjet);
	h_d->Scale(1./nDjet);

  // Normalizing with the width of the x-axis
  h_u->Scale(1,"width");
	h_s->Scale(1,"width");
	h_d->Scale(1,"width");

 TCanvas *canvas2 = new TCanvas("canvas2", "Particle Candidates in Jets2", 800, 600);
  canvas2->SetLogy();
  canvas2->SetLogx();

  // Set line colors for each histogram
  h_d2->SetLineColor(kRed);
  h_u2->SetLineColor(kBlue);
  h_s2->SetLineColor(kGreen);
  
  // Create a legend
  TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
  legend->SetTextSize(0.03);
  
  // Draw histograms with lines and add entries to the legend
  h_d->Draw("HE");
  legend->AddEntry(h_d, "D GenJets", "l");
  
  h_u->Draw("HESAME");
  legend->AddEntry(h_u, "U GenJets", "l");
  
  h_s->Draw("HESAME");
  legend->AddEntry(h_s, "S GenJets", "l");
  
   h_d2->Draw("LSAME");
     legend->AddEntry(h_d2, "D RecoJets", "l");
     
     h_u2->Draw("LSAME");
     legend->AddEntry(h_u2, "U RecoJets", "l");
     
     h_s2->Draw("LSAME");
     legend->AddEntry(h_s2, "S RecoJets", "l");
  
  // Draw the legend
  legend->Draw();
  
  // Show the canvas
  canvas->Draw();*/

  //TCanvas *canvas = new tdrDiCanvas("canvas", "Name", canvas1, canvas2);

  TH1D *hrkp = (TH1D*)h_kp->Clone("hrkp");
  TH1D *hrk0 = (TH1D*)h_k0->Clone("hrk0");
  TH1D *hrk0l = (TH1D*)h_k0l->Clone("hrk0l");
  TH1D *hrk0s = (TH1D*)h_k0s->Clone("hrk0s");
  TH1D *hrlambda = (TH1D*)h_lambda->Clone("hrlambda");
  TH1D *hrsigma0 = (TH1D*)h_sigma0->Clone("hrsigma0");

  TH1D *hrkp2 = (TH1D*)h_kp2->Clone("hrkp2");
  TH1D *hrk02 = (TH1D*)h_k02->Clone("hrk02");
  TH1D *hrk0l2 = (TH1D*)h_k0l2->Clone("hrk0l2");
  TH1D *hrk0s2 = (TH1D*)h_k0s2->Clone("hrk0s2");
  TH1D *hrlambda2 = (TH1D*)h_lambda2->Clone("hrlambda2");
  TH1D *hrsigma02 = (TH1D*)h_sigma02->Clone("hrsigma02");

  // Canvas size parameters from tdrDiCanvas
    int W_ref = 600;
    int H_ref = 600;
    float F_ref = 1./3.;
    float M_ref = 0.03;
    float T_ref = 0.07;
    float B_ref = 0.13;
    float L = 0.15;
    float R = 0.05;
    int W = W_ref;
    int H = H_ref * (1 + (1-T_ref-B_ref)*F_ref+M_ref);

    // Create a canvas with the specified dimensions
    TCanvas *canvas = new TCanvas("canvas", "Canvas Title", 2400, 1000);
    canvas->Divide(2, 1); // Divide the main canvas into three vertical sections

    // Set up the upper pad (Pad 1)
    canvas->cd(1);
    //float Hup = H_ref * (1-B_ref);
    //float Tup = T_ref * H_ref / Hup;
    //float Bup = 0.01;
    //gPad->SetPad(0, H_ref * F_ref / H, 1, 1);
    //gPad->SetLeftMargin(L);
    //gPad->SetRightMargin(R);
    //gPad->SetTopMargin(Tup);
    //gPad->SetBottomMargin(Bup);
    gPad->SetLogx();
  
  hrkp->Divide(h_dusall);
  hrk0->Divide(h_dusall);
  hrk0l->Divide(h_dusall);
  hrk0s->Divide(h_dusall);
  hrlambda->Divide(h_dusall);
  hrsigma0->Divide(h_dusall);

  hrkp->SetLineColor(kRed);
  hrk0->SetLineColor(kBlue);
  hrk0l->SetLineColor(kGreen);
  hrk0s->SetLineColor(kBlack);
  hrlambda->SetLineColor(kOrange);
  hrsigma0->SetLineColor(kCyan);

  TLegend *legend1 = new TLegend(0.35, 0.7, 0.7, 0.9);
  legend1->SetTextSize(0.03);

  hrkp->Draw();
  legend1->AddEntry(hrkp, "S GenJets K^+", "l");
  hrk0->Draw("SAME");
  legend1->AddEntry(hrk0, "S GenJets K^0", "l");
  hrk0l->Draw("SAME");
  legend1->AddEntry(hrk0l, "S GenJets K^0_L", "l");
   hrk0s->Draw();
  legend1->AddEntry(hrk0s, "S GenJets K^0_S", "l");
  hrlambda->Draw("SAME");
  legend1->AddEntry(hrlambda, "S GenJets Lambda", "l");
  hrsigma0->Draw("SAME");
  legend1->AddEntry(hrsigma0, "S GenJets Sigma^0", "l");

  // Draw the legend
  legend1->Draw();

  TLatex latex;
  latex.SetTextSize(0.05); // Adjust text size as needed
  latex.DrawLatexNDC(0.1, 0.95, "S jets"); // NDC coordinates for placement

  gPad->Update();

// Set up the lower pad (Pad 2)
    canvas->cd(2);
    //float Hdw = H - Hup;
    //float Tdw = M_ref * H_ref / Hdw;
    //float Bdw = B_ref * H_ref / Hdw;
    //gPad->SetPad(0, 0, 1, H_ref * F_ref / H);
    //gPad->SetLeftMargin(L);
    //gPad->SetRightMargin(R);
    //gPad->SetTopMargin(Tdw);
    //gPad->SetBottomMargin(Bdw);
    gPad->SetLogx();

  hrkp2->Divide(h_dusall);
  hrk02->Divide(h_dusall);
  hrk0l2->Divide(h_dusall);
  hrk0s2->Divide(h_dusall);
  hrlambda2->Divide(h_dusall);
  hrsigma02->Divide(h_dusall);

  hrkp2->SetLineColor(kRed);
  hrk02->SetLineColor(kBlue);
  hrk0l2->SetLineColor(kGreen);
  hrk0s2->SetLineColor(kBlack);
  hrlambda2->SetLineColor(kOrange);
  hrsigma02->SetLineColor(kCyan);

     // Create a legend
  TLegend *legend2 = new TLegend(0.35, 0.7, 0.7, 0.9);
  legend2->SetTextSize(0.03);

 hrkp2->Draw();
  legend2->AddEntry(hrkp2, "UD GenJets K^+", "l");
  hrk02->Draw("SAME");
  legend2->AddEntry(hrk02, "UD GenJets K^0", "l");
  hrk0l2->Draw("SAME");
  legend2->AddEntry(hrk0l2, "UD GenJets K^0_L", "l");
   hrk0s2->Draw();
  legend2->AddEntry(hrk0s2, "UD GenJets K^0_S", "l");
  hrlambda2->Draw("SAME");
  legend2->AddEntry(hrlambda2, "UD GenJets Lambda", "l");
  hrsigma02->Draw("SAME");
  legend2->AddEntry(hrsigma02, "UD GenJets Sigma^0", "l");

  legend2->Draw();
  
  latex.SetTextSize(0.05); // Adjust text size as needed
  latex.DrawLatexNDC(0.1, 0.95, "UD jets"); // NDC coordinates for placement


  gPad->Update();

// Finalize the canvas
    canvas->cd(); // Go back to the main canvas before final update
    canvas->Update();
    canvas->Draw();
  
  // Show the canvas
 // canvas->Draw();
}