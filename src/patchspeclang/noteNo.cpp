#include <math.h>
#include <fstream> 
#include <sstream>
#include <string>
#include <iostream>


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
  char note;
  int noteNo;

  note= 'c';

  switch('c'){
    case 'c':
      noteNo= 48;
	  break;
    default:
      printf("Error, not a note");
  }
  cout << calculateFreq(48) << endl;
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

