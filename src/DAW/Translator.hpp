#include <string>
using namespace std;

#ifndef Translator_H
#define Translator__H
class Translator{
  private:
    double freq;
	int asciiToMidi(char note);
  public:
	Translator();
    double calculateFreq(int noteNo);
	void translate(string score);
};
# endif

