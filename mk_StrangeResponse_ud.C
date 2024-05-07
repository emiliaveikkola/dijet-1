#include "StrangeResponse_ud.h"
#include <fstream>
R__LOAD_LIBRARY(StrangeResponse_ud_C.so);

void mk_StrangeResponse_ud(){
  TChain *c = new TChain("tree");
  string filename;
  ifstream fin("input_files/mcFiles_stlocal__response_ud.txt"); 
  while (fin >> filename) { c->AddFile(filename.c_str()); }
  StrangeResponse_ud s(c);
  s.Loop();
}