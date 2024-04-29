#include "StrangeTaggerSamples.h"
#include <fstream>
R__LOAD_LIBRARY(StrangeTaggerSamples_C.so);

void mk_StrangeTaggerSamples(){
  TChain *c = new TChain("tree");
  string filename;
  ifstream fin("input_files/mcFiles_stlocal_emilia.txt");
  while (fin >> filename) { c->AddFile(filename.c_str()); }
  StrangeTaggerSamples s(c);
  s.Loop();
}