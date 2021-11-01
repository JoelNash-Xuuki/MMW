#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "csound.hpp"
#include "csPerfThread.hpp"

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
	string orc;
    string sco;
	string output;

  void  setOrc(){ 
	  string file(orc);
	  orc = readFileIntoString(file);
	  char * corc = new char [orc.length()+1];
      strcpy(corc, orc.c_str());
	  csound->CompileOrc(corc);
  }

  void setSco(){
      string scofile(sco);
      sco =  readFileIntoString(scofile);
      char * csco = new char [sco.length()+1];
      strcpy(csco, sco.c_str());
      csound->ReadScore(csco);
    }

	void options(){
	  csound->SetOption("-odac");
	}

  public:
	CsoundPerformanceThread* perfThread; 
	Instrument(string orc, string sco, string output){
	  csound = new Csound();
	  this->orc= orc; 
	  this->sco= sco;
	  this->output= output;
	}

    void play(){
	  setOrc();
	  setSco();
	  options();
	  csound->Start();
	  csound->Perform();
	  delete csound;
	}
	
    void playThread(){
	  setOrc();
	  setSco();
	  options();
	  csound->Start();
      perfThread = new CsoundPerformanceThread(csound); 
	  perfThread->Play();
	  while(perfThread->GetStatus() == 0);

	}	  


    void stopThread(){
	  delete csound;
 	  delete perfThread;
	}
};


int main(){
  Instrument snare = Instrument("orc/o.orc", "sco/snare.sco", "a"); 
  Instrument basse = Instrument("orc/o.orc", "sco/basse.sco", "a");
  snare.playThread();
  basse.playThread();


  
  return 0;
}

