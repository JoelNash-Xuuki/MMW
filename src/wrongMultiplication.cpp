#include <string>
#include <iostream>
#include <math.h>
using namespace std;

#define SEMITONERATIO pow(2, 1./12.0)
#define OCTAVE 12
#define C4 48

double calInterval(int interval ){
  return pow(SEMITONERATIO, interval);
}

double calculateFreq(int noteNo){
  double freq;
  double semitoneRatio= pow(2, 1./12.0);
  double c4= 220.0 * pow(semitoneRatio, 3);
  double c0= c4 * pow(0.5, 5);
  return freq= c0 * pow(semitoneRatio, noteNo);
}

int main(){
  char a = 97;
  char g = a+6;

  cout << SEMITONERATIO << endl;
  cout << calInterval(OCTAVE) << endl;
  cout << calculateFreq(48 + OCTAVE)<< endl;
  cout << g << endl;
  return 0;
}
