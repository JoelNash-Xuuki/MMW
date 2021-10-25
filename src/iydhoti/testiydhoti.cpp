#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "csound.hpp"

using namespace std;

string readFileIntoString(const string& path) {
  ifstream input_file(path);
  if (!input_file.is_open()) {
    cerr << "Could not open the file - '"
      << path << "'" << endl;
   exit(EXIT_FAILURE);
  }
  return string((istreambuf_iterator<char>(input_file)), istreambuf_iterator<char>());
}

int main(){
  Csound* csound = new Csound();

  string orcfile("o.orc");
  string orc = readFileIntoString(orcfile);;
  char * corc = new char [orc.length()+1];
  strcpy(corc, orc.c_str());

  string scofile("bass_snare.sco");
  string sco =  readFileIntoString(scofile);
  char * csco = new char [sco.length()+1];
  strcpy(csco, sco.c_str());

  csound->CompileOrc(corc);
  csound->ReadScore(csco);
  csound->Start();
  csound->Perform();	
  delete csound;
  return 0;
}

