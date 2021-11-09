#include <math.h>
#include <fstream> 
#include <sstream>
#include <string>
#include <iostream>
#include <cstring>


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

double calculateFreq(int noteNo){
  double freq;
  double semitoneRatio= pow(2, 1./12.0);
  double c4= 220.0 * pow(semitoneRatio, 3);
  double c0= c4 * pow(0.5, 5);
  return freq= c0 * pow(semitoneRatio, noteNo);
}

int main(){
  string file("test.note");
  string note = readFileIntoString(file);


  int noteNo;
  int i= 0;
  while(note[i] != '\n'){
    switch(note[i]){
      case 'c':
	    if(note[i+1] == '\''){
		  noteNo= (48+12);
		  i++;
		}
		else
          noteNo= 48;
        cout << calculateFreq(noteNo) << endl;
        break;
      default:
        cout << "Error, " << note[i] << "not a note" << endl;
    }
    i++;
  }
  
  return 0;
} 

/*
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

*/

