#include "skimslim.h"
#include <fstream>
R__LOAD_LIBRARY(skimslim_C.so);

void mk_skimslim(){
  TChain *c = new TChain("Events");
  string filename;
  ifstream fin("input_files/mcFiles_local_emilia_skimslim.txt");
  while (fin >> filename) { c->AddFile(filename.c_str()); }
  //c->MakeClass("skimslimNew");
  skimslim s(c);
  s.Loop();
}