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