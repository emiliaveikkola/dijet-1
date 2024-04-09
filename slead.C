bool isSjet = (abs(GenJet_partonFlavour[i]) == 3);
// Pre-loop to find leading candidate in jet
for (int k = 0; k != nGenJetGenPartCand; ++k) {
    if (GenJetGenPartCand_genJetIdx[k]==i) {
        int j = GenJetGenPartCand_GenPartCandIdx[k];
        double pt = GenPartCand_pt[j];
        if (pt>ptlead) {
            p4lead.SetPtEtaPhiM(GenPartCand_pt[j],GenPartCand_eta[j],
                GenPartCand_phi[j],GenPartCand_mass[j]);
            ptlead = pt;
            elead = p4lead.E(); //leading pt particle energy != leading energy particle
            p4lead = p4cand; 
            iLeadGenCand = j;
        } //if pt>ptlead
        if (isSjet && pt > ptslead){
            ptslead = pt;
        }
    } // if GenJetGenPartCand_genJetIdx[k]==i
} // for k

// Loop over candidates in these jets
for (int k = 0; k != nGenJetGenPartCand; ++k) {
int iGenJet = GenJetGenPartCand_genJetIdx[k];
int iGenCand = GenJetGenPartCand_GenPartCandIdx[k];

    if (i == iGenJet) {
        if (fabs(GenJet_eta[iGenJet]) < 1.3) {
            
            if (ptjet > 80 && ptjet < 100) {
                h_all->Fill(GenPartCand_pt[iGenCand], w);
                if (iLeadGenCand == iGenCand) {h_all_lead->Fill(ptlead, w);}
                h_all_slead->Fill(ptslead, w);
                if (iLeadGenCand == iGenCand && isSjet) {h_s_lead->Fill(ptslead, w);}
            }
        }
    }
}
