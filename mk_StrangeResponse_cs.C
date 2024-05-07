#include "StrangeResponse_cs.h"
#include <fstream>
R__LOAD_LIBRARY(StrangeResponse_cs_C.so);

void mk_StrangeResponse_cs(){
  TChain *c = new TChain("tree");
  string filename;
  ifstream fin("input_files/mcFiles_stlocal_response_cs.txt"); 
  while (fin >> filename) { c->AddFile(filename.c_str()); }
  StrangeResponse_cs s(c);
  s.Loop();
}