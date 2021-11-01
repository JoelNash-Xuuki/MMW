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
	const char* output;

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
	  csound->SetOption(this->output);
	}

  public:
	CsoundPerformanceThread* perfThread; 
	Instrument(){}

	Instrument(string orc, string sco, const char* output){
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

class Sound{
  private:
  Instrument snare;
  Instrument basse;
  Instrument mix;

  public:
  Sound(){
    snare= Instrument("orc/o.orc", "sco/snare.sco", "-osnare.wav");
    basse= Instrument("orc/o.orc", "sco/basse.sco", "-obasse.wav");
  }
  void perform(){
    snare.play();
    basse.play();
  }

  void playMix(){
    mix= Instrument("orc/o.orc", "sco/mix.sco", "-odac");
	mix.play();
  }
};


int main(){
  Sound s= Sound();
  s.perform();
  s.playMix();

  return 0;
}

