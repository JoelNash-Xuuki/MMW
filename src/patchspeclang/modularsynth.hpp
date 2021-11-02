#ifndef ModularSynth_H
#define ModularSynth_H

#include <string>
using namespace std;

#define MODSYN_CHARS (128)
#define MAXMODS (256)

typedef struct {
  char outVar[MODSYN_CHARS];
  char amplitude[MODSYN_CHARS];
} MixOut;

typedef struct {
  char frequency[MODSYN_CHARS];
  char sigOut[MODSYN_CHARS];
  char sigAm[MODSYN_CHARS];
  char sigFm[MODSYN_CHARS];
  char waveForm[MODSYN_CHARS];
  char oMin[MODSYN_CHARS];
  char oMax[MODSYN_CHARS];
} OscMod;

class ModularSynth{
  public:
	bool wasRun; 
    void readOsc(OscMod *oscs, int count);
	void readMix(MixOut *mix, int count);
	void printMix(MixOut mix);
	void printOsc(OscMod oscs);
	void printOrc();
	void printScore(float dur);
  public:
	ModularSynth(string name);
	void testMethod();
	void runPatch();
};
# endif
