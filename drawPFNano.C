#include "TFile.h"
#include "TProfile.h"
#include "TF1.h"

#include "tdrstyle_mod22.C"

void drawPFNano() {

  setTDRStyle();
  TDirectory *curdir = gDirectory;
  
  TFile *f = new TFile("output_z2.root","READ");
  //TFile *f = new TFile("pfnano_v3.root","READ");
  assert(f && !f->IsZombie());
  
  TProfile *prq, *pru, *prd, *prs, *prc, *prb, *prg;
  /*
  prq = (TProfile*)f->Get("pcq"); assert(prq);
  pru = (TProfile*)f->Get("pcu"); assert(pru);
  prd = (TProfile*)f->Get("pcd"); assert(prd);
  prs = (TProfile*)f->Get("pcs"); assert(prs);
  prc = (TProfile*)f->Get("pcc"); assert(prc);
  prb = (TProfile*)f->Get("pcb"); assert(prb);
  prg = (TProfile*)f->Get("pcg"); assert(prg);
  */
  prq = (TProfile*)f->Get("prq"); assert(prq);
  pru = (TProfile*)f->Get("pru"); assert(pru);
  prd = (TProfile*)f->Get("prd"); assert(prd);
  prs = (TProfile*)f->Get("prs"); assert(prs);
  prc = (TProfile*)f->Get("prc"); assert(prc);
  prb = (TProfile*)f->Get("prb"); assert(prb);
  prg = (TProfile*)f->Get("prg"); assert(prg);
  
  TH1D *hdrq, *hdru, *hdrd, *hdrs, *hdrc, *hdrb, *hdrg;
  /*
  hdrq = (TH1D*)f->Get("hdrq"); assert(hdrq);
  hdru = (TH1D*)f->Get("hdru"); assert(hdru);
  hdrd = (TH1D*)f->Get("hdrd"); assert(hdrd);
  hdrs = (TH1D*)f->Get("hdrs"); assert(hdrs);
  hdrc = (TH1D*)f->Get("hdrc"); assert(hdrc);
  hdrb = (TH1D*)f->Get("hdrb"); assert(hdrb);
  hdrg = (TH1D*)f->Get("hdrg"); assert(hdrg);
  */
  hdrq = (TH1D*)f->Get("hrwq"); assert(hdrq);
  hdru = (TH1D*)f->Get("hrwu"); assert(hdru);
  hdrd = (TH1D*)f->Get("hrwd"); assert(hdrd);
  hdrs = (TH1D*)f->Get("hrws"); assert(hdrs);
  hdrc = (TH1D*)f->Get("hrwc"); assert(hdrc);
  hdrb = (TH1D*)f->Get("hrwb"); assert(hdrb);
  hdrg = (TH1D*)f->Get("hrwg"); assert(hdrg);
  
  TH1D *hfq, *hfu, *hfd, *hfs, *hfc, *hfb, *hfg;
  hfq = (TH1D*)f->Get("hfq"); assert(hfq);
  hfu = (TH1D*)f->Get("hfu"); assert(hfu);
  hfd = (TH1D*)f->Get("hfd"); assert(hfd);
  hfs = (TH1D*)f->Get("hfs"); assert(hfs);
  hfc = (TH1D*)f->Get("hfc"); assert(hfc);
  hfb = (TH1D*)f->Get("hfb"); assert(hfb);
  hfg = (TH1D*)f->Get("hfg"); assert(hfg);

  TH1D *hffq, *hffu, *hffd, *hffs, *hffc, *hffb, *hffg;
  /*
  hffq = (TH1D*)f->Get("hffq"); assert(hffq);
  hffu = (TH1D*)f->Get("hffu"); assert(hffu);
  hffd = (TH1D*)f->Get("hffd"); assert(hffd);
  hffs = (TH1D*)f->Get("hffs"); assert(hffs);
  hffc = (TH1D*)f->Get("hffc"); assert(hffc);
  hffb = (TH1D*)f->Get("hffb"); assert(hffb);
  hffg = (TH1D*)f->Get("hffg"); assert(hffg);
  */
  hffq = (TH1D*)f->Get("hf2q"); assert(hffq);
  hffu = (TH1D*)f->Get("hf2u"); assert(hffu);
  hffd = (TH1D*)f->Get("hf2d"); assert(hffd);
  hffs = (TH1D*)f->Get("hf2s"); assert(hffs);
  hffc = (TH1D*)f->Get("hf2c"); assert(hffc);
  hffb = (TH1D*)f->Get("hf2b"); assert(hffb);
  hffg = (TH1D*)f->Get("hf2g"); assert(hffg);

  
  TLatex *tex = new TLatex();
  tex->SetNDC(); tex->SetTextSize(0.045);
  
  extraText = "Private";
  lumi_136TeV = "PFNano";
  //TH1D *h = tdrHist("h","Response over ud",0.87,1.05,//0.92,1.02,//0.95,1.05,
		    TH1D *h = tdrHist("h","Raw response",0.80,1.10,
 // TH1D *h = tdrHist("h","Raw response over ud",0.90,1.04,
		    "p^{genjet}_{T} (GeV)",15,3500);
  TCanvas *c1 = tdrCanvas("c1",h,8,11,kSquare);
  gPad->SetLogx();

  h->GetXaxis()->SetLabelSize(0.04);
  h->GetYaxis()->SetLabelSize(0.04);
  h->GetXaxis()->SetTitleSize(0.045);
  h->GetXaxis()->SetTitleOffset(1.2);
  h->GetYaxis()->SetTitleOffset(1.4);
  h->GetYaxis()->SetTitleSize(0.045);

  TLegend *leg1 = tdrLeg(0.75,0.85-0.045*7,0.90,0.85);
  //TLegend *leg1 = tdrLeg(0.65,0.20,0.90,0.20+0.045*7);
  leg1->SetY1NDC(leg1->GetY1NDC()-0.07);
  leg1->SetTextSize(0.035);
  tex->SetNDC(); tex->SetTextSize(0.04);
  tex->DrawLatex(0.33,0.86,"|#eta| < 1.3"); //AK4PFPUPPI
  tex->DrawLatex(0.33,0.80,"80 < p^{genjet}_{T} < 100 GeV"); //Pythia8 CP5, QCDFlat MC");
  
  TH1D *href = prq->ProjectionX("href");
  TH1D *hrq = prq->ProjectionX("hrq"); 
  TH1D *hru = pru->ProjectionX("hru");
  TH1D *hrd = prd->ProjectionX("hrd");
  TH1D *hrs = prs->ProjectionX("hrs");
  TH1D *hrc = prc->ProjectionX("hrc");
  TH1D *hrb = prb->ProjectionX("hrb");
  TH1D *hrg = prg->ProjectionX("hrg");
/*
  hrq->Divide(href);
  hru->Divide(href);
  hrd->Divide(href);
  hrs->Divide(href);
  hrc->Divide(href);
  hrb->Divide(href);
  hrg->Divide(href);
*/
  tdrDraw(hrq,"Pz",kNone,kBlack);
  tdrDraw(hru,"Pz",kNone,kGray+2);
  tdrDraw(hrd,"Pz",kNone,kMagenta+2);
  tdrDraw(hrs,"Pz",kNone,kOrange+1);
  tdrDraw(hrc,"Pz",kNone,kGreen+2);
  tdrDraw(hrb,"Pz",kNone,kRed);
  tdrDraw(hrg,"Pz",kNone,kBlue);
  /*

  // Some testing: shift ud response by constant to match with g
  TH1D *hrgsim = (TH1D*)hrq->Clone("hrgsim");
  TH1D *hrgsimb = (TH1D*)hrq->Clone("hrgsimb");
  TH1D *hrgsim2 = (TH1D*)hrq->Clone("hrgsim2");
  // Some testing: scale ud-s difference by power law
  TH1D *hrssim = (TH1D*)hrq->Clone("hrssim");
  for (int i = 0; i != hrq->GetNbinsX()+1; ++i) {
    double pt = hrg->GetBinCenter(i);
    hrgsim->SetBinContent(i, hrq->GetBinContent(i)-0.02);
    hrgsimb->SetBinContent(i, 1+1.2*(hrq->GetBinContent(i)-1));
    hrgsim2->SetBinContent(i, hrq->GetBinContent(i)-0.02-1.2/pt);
    //
    hrssim->SetBinContent(i, hrq->GetBinContent(i)-0.02*pow(pt/100.,-0.3));
  }
  tdrDraw(hrgsim,"HIST",kNone,kCyan+1,kSolid,-1,kNone);
  //tdrDraw(hrgsimb,"HIST",kNone,kCyan+2,kSolid,-1,kNone);
  tdrDraw(hrgsim2,"HIST",kNone,kCyan+3,kSolid,-1,kNone);
  //
  tdrDraw(hrssim,"HIST",kNone,kOrange+2,kSolid,-1,kNone);
*/
  leg1->AddEntry(hrq,"ud jets","PLE");
  leg1->AddEntry(hru,"u jets","PLE");
  leg1->AddEntry(hrd,"d jets","PLE");
  leg1->AddEntry(hrs,"s jets","PLE");
  leg1->AddEntry(hrc,"c jets","PLE");
  leg1->AddEntry(hrb,"b jets","PLE");
  leg1->AddEntry(hrg,"g jets","PLE");

  c1->SaveAs("pdf/drawPFNano_JEC2.pdf");

  
  //TH1D *h2 = tdrHist("h2","N_{cand} per bin (a.u.)",0.006,0.066,//0.8e-2,1e-1,
  //TH1D *h2 = tdrHist("h2","p_{T}-weighted N_{cand} per bin (a.u.)",0,0.20,
  //		     "#DeltaR(cand,jet)",0,0.4);
  // Clone to get better Logx axis
  TH1D *h2 = (TH1D*)hdrq->Clone("h2"); h2->Reset();
  h2->SetYTitle("p_{T}-weighted N_{cand} per bin (a.u.)");
  h2->GetYaxis()->SetRangeUser(1e-3,0.20);
  h2->SetXTitle("#DeltaR(cand,jet)");
  h2->GetXaxis()->SetRangeUser(1e-3,0.40);

  h2->GetXaxis()->SetLabelSize(0.04);
  h2->GetYaxis()->SetLabelSize(0.04);
  h2->GetXaxis()->SetTitleSize(0.045);
  h2->GetYaxis()->SetTitleSize(0.045);
  
  TCanvas *c2 = tdrCanvas("c2",h2,8,11,kSquare);
  //gPad->SetLogx();
  //gPad->SetLogy();
  
  TLegend *leg2 = tdrLeg(0.7,0.90-0.045*6,0.92,0.90);
  leg2->SetY1NDC(leg2->GetY1NDC()-0.07);
  leg2->SetTextSize(0.035);
  tex->SetNDC(); tex->SetTextSize(0.04);
  tex->DrawLatex(0.33,0.86,"|#eta| < 1.3");
  tex->DrawLatex(0.33,0.80,"80 < p^{genjet}_{T} < 100 GeV");
  //tex->DrawLatex(0.33,0.76,"AK4PFPUPPI");
  //tex->DrawLatex(0.33,0.76,"AK4GEN");
 
  int nrebin = 2;//4;
  hdrq->Rebin(nrebin); hdrq->Scale(1./hdrq->Integral());
  hdru->Rebin(nrebin); hdru->Scale(1./hdru->Integral());
  hdrd->Rebin(nrebin); hdrd->Scale(1./hdrd->Integral());
  hdrs->Rebin(nrebin); hdrs->Scale(1./hdrs->Integral());
  hdrc->Rebin(nrebin); hdrc->Scale(1./hdrc->Integral());
  hdrb->Rebin(nrebin); hdrb->Scale(1./hdrb->Integral());
  hdrg->Rebin(nrebin); hdrg->Scale(1./hdrg->Integral());

  tdrDraw(hdrd,"HPz",kNone,kMagenta+2,kSolid,-1,1001,kMagenta-9);
  hdrd->SetFillColorAlpha(kMagenta-9,0.25);
  tdrDraw(hdrg,"HPz",kNone,kBlue,kSolid,-1,1001,kBlue-9);
  hdrg->SetFillColorAlpha(kBlue-9,0.25);

  //tdrDraw(hdrq,"Pz",kNone,kBlack);
  tdrDraw(hdru,"Pz",kNone,kGray+2);
  tdrDraw(hdrs,"Pz",kFullCircle,kOrange+1);
  tdrDraw(hdrc,"Pz",kNone,kGreen+2);
  tdrDraw(hdrb,"Pz",kNone,kRed);

  leg2->AddEntry(hdru,Form("u  %1.3f",hdru->GetMean()),"PLE");
  leg2->AddEntry(hdrd,Form("d  %1.3f",hdrd->GetMean()),"FPLE");
  leg2->AddEntry(hdrs,Form("s  %1.3f",hdrs->GetMean()),"PLE");
  leg2->AddEntry(hdrc,Form("c  %1.3f",hdrc->GetMean()),"PLE");
  leg2->AddEntry(hdrb,Form("b  %1.3f",hdrb->GetMean()),"PLE");
  leg2->AddEntry(hdrg,Form("g  %1.3f",hdrg->GetMean()),"FPLE");

  gPad->RedrawAxis();  

  // Comments on hdr: logy-logx looks quite linear, possibly due to 
  // basic property of QCD that emissions go as 1/theta
  // Very low dR from cutoff, dead cone, jet axis smearing, (pi0) decays?
  //TF1 *f1 = new TF1("f1","[0]/(x+[1])+[2]",0,0.4);
  TF1 *f1 = new TF1("f1","[0]*pow(x,[1])",0.1,0.3);
  //f1->SetParameter(0, hdrq->GetBinContent(hdrq->FindBin(0.2))*0.2);
  f1->SetParameters(2e-3,-1);
  hdrq->Fit(f1,"QRN");
  f1->SetRange(1e-3,0.4);
  f1->SetLineColor(kGray+1);
  f1->Draw("SAME");

  TF1 *f2 = new TF1("f2","[0]*pow(x+[2]/x,[1])",1e-3,0.3);
  f2->SetParameters(f1->GetParameter(0),f1->GetParameter(1),1e-4);
  hdrq->Fit(f2,"QRN");
  f2->SetLineColor(kGray+2);
  f2->Draw("SAME");
  h2->GetXaxis()->SetRangeUser(1e-3,0.4);
  h2->GetYaxis()->SetRangeUser(1e-3,2);
  gPad->SetLogx();
  gPad->SetLogy();
  // Seems to fit very nicely! [1]=-sqrt(3) instead of -1, why?
  // What is the [2] representing? Make binning finer a small dR?
  // Why is [0]/[2]~2?
  // So basically 2*[0]*pow(x+[0]/x,-sqrt(3))?
  TF1 *f3 = new TF1("f3","2*[0]*pow(x+[0]/x,-sqrt(3))",1e-3,0.3);
  f3->SetParameter(0, 0.5*f1->GetParameter(0));
  f3->SetLineColor(kOrange+2);
  f3->Draw("SAME");

  //TF1 *fg = new TF1("fg","2*[0]*pow(x+[0]/x,-sqrt(3))",1e-3,0.3);
  TF1 *fg = new TF1("fg","[0]*pow(x+[2]/x,[1])",1e-3,0.35);
  fg->SetParameters(f1->GetParameter(0),f1->GetParameter(1),1e-4);
  // The next line should update only the third parameter instead of overwriting all:
  fg->SetParameter(2, 0.5 * f1->GetParameter(0));
  //fg->SetParameters(0.5*f1->GetParameter(0),-1);
  hdrg->Fit(fg,"QRN");
  fg->SetLineColor(kCyan+1);
  fg->Draw("SAME");
  // For gluons sqrt(3)->sqrt(e)? [0]=[2]?
  TF1 *fg2 = new TF1("fg2","[0]*pow(x+[0]/x,-sqrt(TMath::E()))",1e-3,0.35);
  fg2->SetParameter(0,0.5*(fg->GetParameter(0)+fg->GetParameter(2)));
  fg2->SetLineColor(kCyan+2);
  fg2->Draw("SAME");
  h2->GetXaxis()->SetTitleOffset(1.1);
  h2->GetYaxis()->SetTitleOffset(1.4);
  //CMS_lumi(c2, 8, 11);

  c2->SaveAs("pdf/drawPFNano_DeltaRa2.pdf");
  
  
  TH1D *h3 = tdrHist("h3","N_{jet} per bin (a.u.)",0,0.14,//1e-4,0.5,
		     "p^{lead}_{T} / p^{jet}_{T}",0.,1.);
  TCanvas *c3 = tdrCanvas("c3",h3,8,11,kSquare);
  //gPad->SetLogy();
  h3->GetXaxis()->SetLabelSize(0.04);
  h3->GetYaxis()->SetLabelSize(0.04);
  h3->GetXaxis()->SetTitleSize(0.045);
  h3->GetYaxis()->SetTitleSize(0.045);
  h3->GetXaxis()->SetTitleOffset(1.1);
  h3->GetYaxis()->SetTitleOffset(1.4);

  TLegend *leg3 = tdrLeg(0.7,0.90-0.045*6,0.92,0.90);
  leg3->SetY1NDC(leg3->GetY1NDC()-0.07);
  leg3->SetTextSize(0.035);
  tex->SetNDC(); tex->SetTextSize(0.04);
  tex->DrawLatex(0.33,0.86,"|#eta| < 1.3");
  tex->DrawLatex(0.33,0.80,"80 < p^{genjet}_{T} < 100 GeV");
  //tex->DrawLatex(0.33,0.76,"AK4PFPUPPI");
  //tex->DrawLatex(0.33,0.76,"AK4GEN");

  int nrebinf = 2;
  hfq->Rebin(nrebinf); hfq->Scale(1./hfq->Integral());
  hfu->Rebin(nrebinf); hfu->Scale(1./hfu->Integral());
  hfd->Rebin(nrebinf); hfd->Scale(1./hfd->Integral());
  hfs->Rebin(nrebinf); hfs->Scale(1./hfs->Integral());
  hfc->Rebin(nrebinf); hfc->Scale(1./hfc->Integral());
  hfb->Rebin(nrebinf); hfb->Scale(1./hfb->Integral());
  hfg->Rebin(nrebinf); hfg->Scale(1./hfg->Integral());

  tdrDraw(hfd,"HPz",kNone,kMagenta+2,kSolid,-1,1001,kMagenta-9);
  hfd->SetFillColorAlpha(kMagenta-9,0.25);
  tdrDraw(hfg,"HPz",kNone,kBlue,kSolid,-1,1001,kBlue-9);
  hfg->SetFillColorAlpha(kBlue-9,0.25);
  
  //tdrDraw(hfq,"Pz",kNone,kBlack);
  tdrDraw(hfu,"Pz",kNone,kGray+2);
  tdrDraw(hfs,"Pz",kFullCircle,kOrange+1);
  tdrDraw(hfc,"Pz",kNone,kGreen+2);
  tdrDraw(hfb,"Pz",kNone,kRed);

  leg3->AddEntry(hfu,Form("u  %1.3f",hfu->GetMean()),"PLE");
  leg3->AddEntry(hfd,Form("d  %1.3f",hfd->GetMean()),"FPLE");
  leg3->AddEntry(hfs,Form("s  %1.3f",hfs->GetMean()),"PLE");
  leg3->AddEntry(hfc,Form("c  %1.3f",hfc->GetMean()),"PLE");
  leg3->AddEntry(hfb,Form("b  %1.3f",hfb->GetMean()),"PLE");
  leg3->AddEntry(hfg,Form("g  %1.3f",hfg->GetMean()),"FPLE");

  c3->SaveAs("pdf/drawPFNano_FragLead2.pdf");
  

  TH1D *h4 = tdrHist("h4","N_{can} per bin (a.u.)",2e-6,9e1,
  		     "p^{cand}_{T} / p^{jet}_{T}",0.4e-2,1.);
  // Clone to get better zoomable Logx axis
  //TH1D *h4 = (TH1D*)hffq->Clone("h4"); h2->Reset();
  //h4->SetYTitle("N_{cand} per bin (a.u.)");
  //h4->GetYaxis()->SetRangeUser(1e-6,1e0);
  //h4->SetXTitle("p_{T,cand} / p_{T,jet}");
  //h4->GetXaxis()->SetRangeUser(1e-3,0.40);
  
  TCanvas *c4 = tdrCanvas("c4",h4,8,11,kSquare);
  gPad->SetLogy();
  gPad->SetLogx();

  TLegend *leg4 = tdrLeg(0.7,0.90-0.045*6,0.92,0.90);
  leg4->SetY1NDC(leg4->GetY1NDC()-0.07);
  leg4->SetTextSize(0.035);
  tex->SetNDC(); tex->SetTextSize(0.04);
  tex->DrawLatex(0.33,0.86,"|#eta| < 1.3");
  tex->DrawLatex(0.33,0.80,"80 < p^{genjet}_{T} < 100 GeV");
  //tex->DrawLatex(0.33,0.76,"AK4PFPUPPI");
  //tex->DrawLatex(0.33,0.76,"AK4GEN");

  int nrebinff = 1;
  hffq->Rebin(nrebinff); hffq->Scale(1./hffq->Integral());
  hffu->Rebin(nrebinff); hffu->Scale(1./hffu->Integral());
  hffd->Rebin(nrebinff); hffd->Scale(1./hffd->Integral());
  hffs->Rebin(nrebinff); hffs->Scale(1./hffs->Integral());
  hffc->Rebin(nrebinff); hffc->Scale(1./hffc->Integral());
  hffb->Rebin(nrebinff); hffb->Scale(1./hffb->Integral());
  hffg->Rebin(nrebinff); hffg->Scale(1./hffg->Integral());

  tdrDraw(hffd,"HPz",kNone,kMagenta+2,kSolid,-1,1001,kMagenta-9);
  hffd->SetFillColorAlpha(kMagenta-9,0.25);
  tdrDraw(hffg,"HPz",kNone,kBlue,kSolid,-1,1001,kBlue-9);
  hffg->SetFillColorAlpha(kBlue-9,0.25);
  //tdrDraw(hffd,"Pz",kNone,kMagenta+2);
  //tdrDraw(hffg,"Pz",kNone,kBlue);
  
  //tdrDraw(hffq,"Pz",kNone,kBlack);
  tdrDraw(hffu,"Pz",kNone,kGray+2);
  tdrDraw(hffs,"Pz",kFullCircle,kOrange+1);
  tdrDraw(hffc,"Pz",kNone,kGreen+2);
  tdrDraw(hffb,"Pz",kNone,kRed);

  hffs->SetMarkerSize(0.5);
  
  leg4->AddEntry(hffu,Form("u  %1.3f",hffu->GetMean()),"PLE");
  leg4->AddEntry(hffd,Form("d  %1.3f",hffd->GetMean()),"FPLE");
  leg4->AddEntry(hffs,Form("s  %1.3f",hffs->GetMean()),"PLE");
  leg4->AddEntry(hffc,Form("c  %1.3f",hffc->GetMean()),"PLE");
  leg4->AddEntry(hffb,Form("b  %1.3f",hffb->GetMean()),"PLE");
  leg4->AddEntry(hffg,Form("g  %1.3f",hffg->GetMean()),"FPLE");

  //TF1 *f1ff0 = new TF1("f1ff0","[0]*pow(x,[1])",0.01,0.2);
  //f1ff0->SetParameters(2e-3,-1);
  //TF1 *f1ff0 = new TF1("f1ff0","[0]*pow(0.5-x,[1])",0.01,0.4);
  //TF1 *f1ff0 = new TF1("f1ff0","[0]*pow(1-x,[1])",0.01,0.2); //good w/o W
  TF1 *f1ff0 = new TF1("f1ff0","[0]*pow(1-x,[1])",0.01,0.2);
  //f1ff0->SetParameters(2e-3,+1);
  f1ff0->SetParameters(0.17,+21); // good w/o W (is 21 Nptcl?)
  hffq->Fit(f1ff0,"QRN");
  f1ff0->SetRange(1e-3,1);//1.9);
  f1ff0->SetLineColor(kGray+1);
  f1ff0->Draw("SAME");

  /*
  //TF1 *f1ff = new TF1("f1ff","[0]/x",0.004,0.1);
  //TF1 *f1ff = new TF1("f1ff","[0]*pow(x,[1])",0.01,0.1);
  //TF1 *f1ff = new TF1("f1ff","[0]*pow(x,[1])*pow((1-x),1)",0.01,0.1);
  //TF1 *f1ff = new TF1("f1ff","[0]*pow(x,[1])*pow((1-x),[2])",0.01,0.1);
  TF1 *f1ff = new TF1("f1ff","[0]*pow(x+[2]/x,[1])",1e-3,0.35);
  f1ff->SetParameters(1e3,1e-2,-1);
  hffg->Fit(f1ff,"QRNW");
  f1ff->SetRange(0.004,1);
  f1ff->SetLineColor(kGray+1);
  f1ff->Draw("SAME");
  */

  h4->GetXaxis()->SetLabelSize(0.04);
  h4->GetYaxis()->SetLabelSize(0.04);
  h4->GetXaxis()->SetTitleSize(0.045);
  h4->GetYaxis()->SetTitleSize(0.045);
  h4->GetXaxis()->SetTitleOffset(1.1);
  h4->GetYaxis()->SetTitleOffset(1.4);

  c4->SaveAs("pdf/drawPFNano_FragOther2.pdf");
  
} // drawPFNano
