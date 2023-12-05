  void draw(){
  TFile *f = new TFile("output.root","read");

  TH1D *h_d = (TH1D*) f->Get("h_d");
  TH1D *h_u = (TH1D*) f->Get("h_u");
  TH1D *h_s = (TH1D*) f->Get("h_s");
  TH1D *h_dus = (TH1D*) f->Get("h_dus");
  TH1D *h_d2 = (TH1D*) f->Get("h_d2");
  TH1D *h_u2 = (TH1D*) f->Get("h_u2");
  TH1D *h_s2 = (TH1D*) f->Get("h_s2");

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


   cout << nSjet << " " << nUjet << " " << nDjet << endl;


  // Normalizing with number of jets
	h_u->Scale(1./nUjet);
	h_s->Scale(1./nSjet);
	h_d->Scale(1./nDjet);
    h_dus->Scale(1./nDUSjet);



  // Normalizing with the width of the x-axis
    h_u->Scale(1,"width");
	h_s->Scale(1,"width");
	h_d->Scale(1,"width");
    h_dus->Scale(1,"width");


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
  TCanvas *canvas1 = new TCanvas("canvas1", "Particle Candidates in Jets", 800, 600);
  //canvas1->SetLogy();
  canvas1->SetLogx();

  // Set line colors for each histogram
  /*h_d->SetLineColor(kRed);
  h_u->SetLineColor(kBlue);
  h_s->SetLineColor(kGreen);
  h_d2->SetLineColor(kPink);
  h_u2->SetLineColor(kViolet);
  h_s2->SetLineColor(kTeal);*/
  
  // Create a legend
  TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
  legend->SetTextSize(0.03);
  
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


  hrs->Divide(h_dus);
  hru->Divide(h_dus);
  hrd->Divide(h_dus);
  
  hrd->SetLineColor(kRed);
  hru->SetLineColor(kBlue);
  hrs->SetLineColor(kGreen);
  
  hrs->Draw();
  hru->Draw("SAME");
  hrd->Draw("SAME");

  // Draw the legend
  legend->Draw();
  
  // Show the canvas
  canvas1->Draw();
}
