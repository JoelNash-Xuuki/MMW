#include <string>
#include <math.h>
#include "Translator.hpp"
#include <regex>
#include <iostream>

using namespace std;

Translator::Translator(){}

double Translator::calculateFreq(int noteNo){
  double freq;
  double semitoneRatio= pow(2, 1./12.0);
  double c4= 220.0 * pow(semitoneRatio, 3);
  double c0= c4 * pow(0.5, 5);
  return freq= c0 * pow(semitoneRatio, noteNo);
}

int Translator::asciiToMidi(char note){
  return note - 39; 
}

void Translator::translate(string score){

  regex noteLetter("[a-gr]| [a-gr] ");
  regex rhythmPat("4");

  smatch noteLetterMatches;
  smatch rhythmMatches;
  char scoreTest= 0;
  
  if(regex_search(score, noteLetterMatches, noteLetter)){
    if(score[0] > 96 && score[0] < 104 ){
	  cout << "Test!" << calculateFreq(asciiToMidi(score[0]));
	}
  }
}
