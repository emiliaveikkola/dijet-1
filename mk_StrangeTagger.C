#include "StrangeTagger.h"
#include <fstream>
R__LOAD_LIBRARY(StrangeTagger_C.so);

void mk_StrangeTagger(){
  TChain *c = new TChain("tree");
  string filename;
  ifstream fin("input_files/mcFiles_stlocal_emilia.txt");
  while (fin >> filename) { c->AddFile(filename.c_str()); }
  StrangeTagger s(c);
  s.Loop();
}