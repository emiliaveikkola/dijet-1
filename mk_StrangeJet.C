#include "StrangeJet.h"
R__LOAD_LIBRARY(StrangeJet_C.so);

void mk_StrangeJet(){
  TChain *c = new TChain("Events");
  c->AddFile("tree_JMEPFNano_qcd.root");
  StrangeJet s(c);
  s.Loop();
}
