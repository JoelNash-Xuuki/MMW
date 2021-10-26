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

class Instrument{
  private:
    Csound* csound; 
  public:
	Instrument(){
	  csound = new Csound();
	}

    void  setOrc(){ 
      string orcfile("orc/o.orc");
	  string orc = readFileIntoString(orcfile);
	  char * corc = new char [orc.length()+1];
      strcpy(corc, orc.c_str());
	  csound->CompileOrc(corc);
	}

    void setSco(){
      string scofile("sco/a.sco");
      string sco =  readFileIntoString(scofile);
      char * csco = new char [sco.length()+1];
      strcpy(csco, sco.c_str());
      csound->ReadScore(csco);
    }

	void options(){
	  csound->SetOption("-odac");
	}

    void play(){
	  setOrc();
	  setSco();
	  options();
	  csound->Start();
      csound->Perform();	
      delete csound;
	}
};


int main(){
  Instrument i = Instrument(); 
  i.play();
  
  return 0;
}

