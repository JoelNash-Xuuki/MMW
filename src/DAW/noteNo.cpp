#include <math.h>
#include <fstream> 
#include <sstream>
#include <string>
#include <iostream>
#include <cstring>

using namespace std; 

#define SEMITONERATIO pow(2, 1./12.0)
#define OCTAVE 12
#define C4 48.0

string readFileIntoString(const string& path) {
  ifstream input_file(path);
  if (!input_file.is_open()) {
    cerr << "Could not open the file - '"
      << path << "'" << endl;
   exit(EXIT_FAILURE);
  }
  return string((istreambuf_iterator<char>(input_file)), 
  		 istreambuf_iterator<char>());
}

double calculateFreq(int noteNo){
  double freq;
  double semitoneRatio= pow(2, 1./12.0);
  double c4= 220.0 * pow(semitoneRatio, 3);
  double c0= c4 * pow(0.5, 5);
  return freq= c0 * pow(semitoneRatio, noteNo);
}

bool isValidNote(string note){
  if(note[0] == 97)
	  return true;

  return false;
}

int asciiToMidi(string note){
  return note[0] - 39; 
}

int getNote(string note){
  return asciiToMidi(note);
}

bool getNoteOct(string note){
  int i= 0;
  return note[i+1] == '\'' 
		 && note[i+2] == ' ' 
		 || note[i+2] == '\n'; 
}

int notesToFreq(string note){
  if(isValidNote(note)){
    return calculateFreq(getNote(note));
  }
  return -1; 
}

int main(){
  string file("test.note");
  string note = readFileIntoString(file);
  cout << notesToFreq(note);
  return 0;
} 
