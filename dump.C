                    //if (!isId){
                    //cout << "id: " << GenPartCand_pdgId[iGenCand] << " cand_pt: "<< GenPartCand_pt[iGenCand] << " jet_pt: "<< GenJet_pt[iGenJet] <<endl << flush;
                    //}
                    /*
                    for (int id = 0; id != npid; ++ id) {
                      //if (debug){cout << "idloop" << endl;}
                        if (GenPartCand_pdgId[iGenCand] == vpid3[id]){
                          //isId = true;
                          const char *pid = vpid[id].c_str();
                          const char *hname = Form("h_%s_%s_vs_%s", pid, cq, cx);
                          if (vxvar[ix] == "ptjet") { //swap if doesn't work
                            x = GenJet_pt[iGenJet]; 
                            mh[hname]->Fill(x, w);
                          }
                          if (vxvar[ix] == "ptcand" && pt > 80 && pt < 100) {
                            x = GenPartCand_pt[iGenCand];
                            mh[hname]->Fill(x, w);
                          }
                        }
                        //if (debug){cout << "fillhisto" << hname << endl << flush;}      
                        }  //for id
                      */
                      //if (!isId){
                      //cout << "id " << GenPartCand_pdgId[iGenCand] << endl << flush;
                      //}


/*            for (int iq = 0; iq != nq; ++ iq) {
              //if (debug){cout << "iqloop" << endl;}
              bool isQ = (abs(GenJet_partonFlavour[iGenJet]) == vq2[iq]);
              //if (debug && isQ) { cout << "isQ=" << isQ << ", GenJet_partonFlavour[i]=" << GenJet_partonFlavour[iGenJet] << ", vq2[iq]=" << vq2[iq] << endl; }
              //bool isQ = (abs(GenJet_partonFlavour[i]) == mq[cq]);
              for (int ix = 0; ix != nxvar && isQ; ++ ix) {
                const char *cx = vxvar[ix].c_str();
                const char *cq = vq[iq].c_str();
                double x(0);
                const char *hname_all = Form("h_all_sanslead_%s_vs_%s", cq, cx);
                if (vxvar[ix] == "ptjet") { //swap if doesn't work
                  x = ptlead; 
                  mh[hname_all]->Fill(x, w);
                }
                if (vxvar[ix] == "ptcand" && ptjet > 80 && ptjet < 100) {
                  x = GenPartCand_pt[iGenCand];
                  mh[hname_all]->Fill(x, w);
                }
                bool isId(false);
                //if (debug){cout << "ixloop" << endl;}
                for (std::size_t id = 0; id < vpid3.size() && !isId; ++id) { // Iterate over vectors
                  bool isMatchFound = false;
                  for (std::size_t elem = 0; elem < vpid3[id].size() && !isMatchFound; ++elem) { // Iterate over elements in a vector
                    //if (vpid3[id][elem] == 0) continue; // Skip zeros
                    if (GenPartCand_pdgId[iGenCand] == vpid3[id][elem]) {
                      isMatchFound = true;
		                }
		              }
                  if (isMatchFound) {
                    isId = true;
                    const char *pid = vpid[id].c_str();
                    const char *hname = Form("h_sanslead_%s_%s_vs_%s", pid, cq, cx);
                    if (vxvar[ix] == "ptjet") {
                      x = GenJet_pt[iGenJet];
                      mh[hname]->Fill(x, w);
                    }
                    if (vxvar[ix] == "ptcand" && ptjet > 80 && ptjet < 100) {
                      x = GenPartCand_pt[iGenCand];
                      mh[hname]->Fill(x, w);
                    } // No need to check other vectors if a match is already found for this particle
		              }
		            }
              }
            }
          */


      //if (fabs(GenJet_eta[i]) < 1.3 && ptjet > 80 && ptjet < 100) {
        //h_elead_vs_ejet->Fill(elead/ejet,w);
        //h_deltaR_lead->Fill(p4jet.DeltaR(p4lead),w);
        //h_deltaR_sec->Fill(p4jet.DeltaR(p4sec),w);
        //h_deltaR_sec_e->Fill(p4jet.DeltaR(p4sec), w * elead/ejet);
      //}

      //for (int j = 0; j != nGenJetGenPartCand; ++j) {
        //int iGenJet = GenJetGenPartCand_genJetIdx[j];
        //int iGenCand = GenJetGenPartCand_GenPartCandIdx[j];
        //p4cand.SetPtEtaPhiM(GenPartCand_pt[iGenCand], GenPartCand_eta[iGenCand], GenPartCand_phi[iGenCand], GenPartCand_mass[iGenCand]);
        //if (i == iGenJet) {
          //double ecand = p4cand.E();
          //if (ecand > elead) { 
            //p4lead = p4cand; 
            //elead = ecand;
          //}
          //h_deltaR_sec->Fill(p4jet.DeltaR(p4sec),w);
          //h_deltaR_sec_e->Fill(p4jet.DeltaR(p4sec), w * elead/ejet);
        //}
      //}

                  /*
            if (iGenCand != iLeadGenCand) {
              for (int iq = 0; iq != nq; ++ iq) {
                //if (debug){cout << "iqloop" << endl;}
                bool isQ = (abs(GenJet_partonFlavour[iGenJet]) == vq2[iq]);
                //if (debug && isQ) { cout << "isQ=" << isQ << ", GenJet_partonFlavour[i]=" << GenJet_partonFlavour[iGenJet] << ", vq2[iq]=" << vq2[iq] << endl; }
                //bool isQ = (abs(GenJet_partonFlavour[i]) == mq[cq]);
                for (int ix = 0; ix != nxvar && isQ; ++ ix) {
                  const char *cx = vxvar[ix].c_str();
                  const char *cq = vq[iq].c_str();
                  double x(0);
                  const char *hname_all = Form("h_all_sanslead_%s_vs_%s", cq, cx);
                  if (vxvar[ix] == "ptjet") { //swap if doesn't work
                    x = GenJet_pt[iGenJet]; 
                    mh[hname_all]->Fill(x, w);
                  }
                  if (vxvar[ix] == "ptcand" && ptjet > 80 && ptjet < 100) {
                    x = GenPartCand_pt[iGenCand];
                    mh[hname_all]->Fill(x, w);
                  }
                  bool isId(false);
                  //if (debug){cout << "ixloop" << endl;}
                  for (std::size_t id = 0; id < vpid3.size() && !isId; ++id) { // Iterate over vectors
                    bool isMatchFound = false;
                    for (std::size_t elem = 0; elem < vpid3[id].size() && !isMatchFound; ++elem) { // Iterate over elements in a vector
                      //if (vpid3[id][elem] == 0) continue; // Skip zeros
                      if (GenPartCand_pdgId[iGenCand] == vpid3[id][elem]) {
                        isMatchFound = true;
                      }
                    }
                    if (isMatchFound) {
                      isId = true;
                      const char *pid = vpid[id].c_str();
                      const char *hname = Form("h_sanslead_%s_%s_vs_%s", pid, cq, cx);
                      if (vxvar[ix] == "ptjet") {
                        x = GenJet_pt[iGenJet];
                        mh[hname]->Fill(x, w);
                      }
                      if (vxvar[ix] == "ptcand" && ptjet > 80 && ptjet < 100) {
                        x = GenPartCand_pt[iGenCand];
                        mh[hname]->Fill(x, w);
                      } // No need to check other vectors if a match is already found for this particle
                    } // if match found
                  } // for id
                } // for ix
              } // for iq
            } // if iGenCand != iLeadGenCand
            */

           const char *hsname_all = Form("h_all_%s_vs_ptslead", "s");
  const char *hstitle_all = Form(";p_{T,ptslead}, all;%s N", "s");
  mh[hsname_all] = new TH1D(hsname_all, hstitle_all, nxbins_cand, xbins_cand);
  for (int id = 0; id != npid; ++ id) {
    const char *pid = vpid[id].c_str();
    const char *pid2 = vpid2[id].c_str();
    const char *hsname = Form("h_%s_s_vs_ptslead", pid);
    const char *hstitle = Form(";p_{T,ptslead}, %s;s N", pid2);
    mh[hsname] = new TH1D(hsname, hstitle, nxbins_cand, xbins_cand);
  }
    for (int ic = 0; ic != nc; ++ ic) {
    const char *cc = vc[ic].c_str();
    const char *hsname = Form("h_s_%s_vs_ptslead", cc);
    const char *hstitle = Form(";p_{T,ptslead}, s; %s N", cc);
    mhc[hsname] = new TH1D(hsname, hstitle, nxbins_cand, xbins_cand);
  }

                       if (ptjet>80 && ptjet<100) {
              double x(0);
              const char *hsname_all = Form("h_all_%s_vs_ptslead", "s");
              x = ptslead; 
              mh[hsname_all]->Fill(x, w);
            
              bool isSId(false);
              for (std::size_t id = 0; id < vpid3.size() && !isSId; ++id) { // Iterate over vectors
                bool isSMatchFound = false;
                for (std::size_t elem = 0; elem < vpid3[id].size() && !isSMatchFound; ++elem) { // Iterate over elements in a vector
                  //if (vpid3[id][elem] == 0) continue; // Skip zeros
                  if (GenPartCand_pdgId[iGenCand] == vpid3[id][elem]) {
                    isSMatchFound = true;
                  }
                }
                if (isSMatchFound) {
                  isSId = true;
                  const char *pid = vpid[id].c_str();
                  const char *hsname = Form("h_%s_s_vs_ptslead", pid);
                  x = ptslead;
                  mh[hsname]->Fill(x, w);
                }
              }
            }

                        if (isSjet && ptjet > 80 && ptjet < 100) {
              double x(0);
              for (int ic = 0; ic != nc ; ++ ic) {
                bool isT = visc[ic];
                if (isT){
                  const char *cc = vc[ic].c_str();
                  const char *hsname = Form("h_s_%s_vs_ptslead",cc);
                  x = ptslead;
                  mhc[hsname]->Fill(x, w);
                }
              }
            } 

                          h_all->Fill(GenPartCand_pt[iGenCand], w);
              // For the overall leading candidate
              if (iLeadGenCand == iGenCand) {h_all_lead->Fill(ptlead, w);}
              if (iLeadSCand == iGenCand && ptslead > 0) {h_all_slead->Fill(ptslead, w);}
              if (iLeadUDCand == iGenCand && ptudlead > 0) {h_all_udlead->Fill(ptudlead, w);}
              //cout << "jet parton Flavour with lead S " << GenJet_partonFlavour[iGenJet] << endl << flush;}
              if (iLeadGenCand == iGenCand && isSjet) {h_s_lead->Fill(ptslead, w);}
              if (iLeadGenCand == iGenCand && (isUjet || isDjet)) {h_ud_lead->Fill(ptudlead, w);}
            