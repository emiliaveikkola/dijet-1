  #include "tdrstyle_mod22.C"

  void draw(){
  TFile *f = new TFile("output.root","read");

  TH1D *h_d = (TH1D*) f->Get("h_d");
  TH1D *h_u = (TH1D*) f->Get("h_u");
  TH1D *h_s = (TH1D*) f->Get("h_s");
  TH1D *h_dus = (TH1D*) f->Get("h_dus");
  TH1D *h_d2 = (TH1D*) f->Get("h_d2");
  TH1D *h_u2 = (TH1D*) f->Get("h_u2");
  TH1D *h_s2 = (TH1D*) f->Get("h_s2");
  TH1D *h_dus2 = (TH1D*) f->Get("h_dus");

//h->SetLineColor(kRed);
  // h->Draw();
  //h2->Draw("SAMES");
  
  /* h_d->SetLineColor(kRed);
     h_d->SetLineColor(kRed);
     h_ud2->SetLineColor(kBlue);
     h_s->SetLineColor(kGreen);
     h_s2->SetLineColor(kOrange); */

   int nUjet = h_u->GetEntries();
   int nDjet = h_d->GetEntries();
   int nSjet = h_s->GetEntries();
   int nDUSjet = h_dus->GetEntries();

   int nU2jet = h_u2->GetEntries();
   int nD2jet = h_d2->GetEntries();
   int nS2jet = h_s2->GetEntries();
   int nDUS2jet = h_dus2->GetEntries();


   cout << nSjet << " " << nUjet << " " << nDjet << endl;


  // Normalizing with number of jets
	h_u->Scale(1./nUjet);
	h_s->Scale(1./nSjet);
	h_d->Scale(1./nDjet);
    h_dus->Scale(1./nDUSjet);

    h_u2->Scale(1./nU2jet);
	h_s2->Scale(1./nS2jet);
	h_d2->Scale(1./nD2jet);
    h_dus2->Scale(1./nDUS2jet);



  // Normalizing with the width of the x-axis
    h_u->Scale(1,"width");
	h_s->Scale(1,"width");
	h_d->Scale(1,"width");
    h_dus->Scale(1,"width");

    h_u2->Scale(1,"width");
	h_s2->Scale(1,"width");
	h_d2->Scale(1,"width");
    h_dus2->Scale(1,"width");


	// The mean and mean error for each histogram
	double meanD = h_d->GetMean();
	double meanErrorD = h_d->GetMeanError();

	double meanU = h_u->GetMean();
	double meanErrorU = h_u->GetMeanError();

	double meanS = h_s->GetMean();
	double meanErrorS = h_s->GetMeanError();


	// Print or use the means and mean errors as needed
	cout << "Mean D: " << meanD << " +/- " << meanErrorD << endl;
	cout << "Mean U: " << meanU << " +/- " << meanErrorU << endl;
	cout << "Mean S: " << meanS << " +/- " << meanErrorS << endl; 
  
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

  TH1D *hrs = (TH1D*)h_s->Clone("hrs");
  TH1D *hru = (TH1D*)h_u->Clone("hru");
  TH1D *hrd = (TH1D*)h_d->Clone("hrd");

  TH1D *hrs2 = (TH1D*)h_s2->Clone("hrs2");
  TH1D *hru2 = (TH1D*)h_u2->Clone("hru2");
  TH1D *hrd2 = (TH1D*)h_d2->Clone("hrd2");

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
    TCanvas *canvas = new TCanvas("canvas", "Canvas Title", W, H);
    canvas->Divide(1, 2);

  

    // Set up the upper pad (Pad 1)
    canvas->cd(1);
    float Hup = H_ref * (1-B_ref);
    float Tup = T_ref * H_ref / Hup;
    float Bup = 0.01;
    gPad->SetPad(0, H_ref * F_ref / H, 1, 1);
    gPad->SetLeftMargin(L);
    gPad->SetRightMargin(R);
    gPad->SetTopMargin(Tup);
    gPad->SetBottomMargin(Bup);
    gPad->SetLogx();
  
  hrs->Divide(h_dus);
  hru->Divide(h_dus);
  hrd->Divide(h_dus);

  hrd->SetLineColor(kRed);
  hru->SetLineColor(kBlue);
  hrs->SetLineColor(kGreen);

  TLegend *legend1 = new TLegend(0.7, 0.75, 0.9, 0.9);
  legend1->SetTextSize(0.03);

  hrs->Draw();
  legend1->AddEntry(hrs, "S GenJets ratio", "l");
  hru->Draw("SAME");
  legend1->AddEntry(hru, "U GenJets ratio", "l");
  hrd->Draw("SAME");
  legend1->AddEntry(hrd, "D GenJets ratio", "l");

  // Draw the legend
  legend1->Draw();

  TLatex latex;
  latex.SetTextSize(0.05); // Adjust text size as needed
  latex.DrawLatexNDC(0.1, 0.95, "Upper Pad Title"); // NDC coordinates for placement

// Set up the lower pad (Pad 2)
    canvas->cd(2);
    float Hdw = H - Hup;
    float Tdw = M_ref * H_ref / Hdw;
    float Bdw = B_ref * H_ref / Hdw;
    gPad->SetPad(0, 0, 1, H_ref * F_ref / H);
    gPad->SetLeftMargin(L);
    gPad->SetRightMargin(R);
    gPad->SetTopMargin(Tdw);
    gPad->SetBottomMargin(Bdw);
    gPad->SetLogx();

  hrs2->Divide(h_dus2);
  hru2->Divide(h_dus2);
  hrd2->Divide(h_dus2);

  hrd2->SetLineColor(kRed);
  hru2->SetLineColor(kBlue);
  hrs2->SetLineColor(kGreen);

     // Create a legend
  TLegend *legend2 = new TLegend(0.7, 0.75, 0.9, 0.9);
  legend2->SetTextSize(0.03);

  hrs2->Draw();
  legend2->AddEntry(hrs2, "S GenJets ratio, energy", "l");
  hru2->Draw("SAME");
  legend2->AddEntry(hru2, "U GenJets ratio, energy", "l");
  hrd2->Draw("SAME");
  legend2->AddEntry(hrd2, "D GenJets ratio, energy", "l");

  legend2->Draw();
  
  latex.SetTextSize(0.05); // Adjust text size as needed
  latex.DrawLatexNDC(0.1, 0.95, "Lower Pad Title"); // NDC coordinates for placement

// Finalize the canvas
    canvas->cd(0); // Go back to the main canvas before final update
    canvas->Update();
    canvas->RedrawAxis();
    canvas->GetFrame()->Draw();
  
  // Show the canvas
 // canvas->Draw();
}
