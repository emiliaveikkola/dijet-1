#include "StrangeTagger_DATA.h"
#include <fstream>
R__LOAD_LIBRARY(StrangeTagger_DATA_C.so);

void mk_StrangeTagger_DATA(){
  TChain *c = new TChain("tree");
  string filename;
  ifstream fin("input_files/mcFiles_stlocal_emilia.txt"); 
  //input_files/mcFiles_stlocal_emilia.txt
  //input_files/mcFiles_stlocal_emilia_udsample.txt
  //input_files/mcFiles_stlocal_emilia_cssample.txt
  while (fin >> filename) { c->AddFile(filename.c_str()); }
  StrangeTagger_DATA s(c);
  s.Loop();
}