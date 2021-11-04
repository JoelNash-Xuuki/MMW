#ifndef ModularSynth_H
#define ModularSynth_H
#include <string>
#include <fstream>
using namespace std;
#define MODSYN_CHARS (128)
#define MAXMODS (256)
typedef struct {
  char speed[MODSYN_CHARS];
  char sigOut[MODSYN_CHARS];
  char seed[MODSYN_CHARS];
  char oMin[MODSYN_CHARS];
  char oMax[MODSYN_CHARS];
} NoiseMod;
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
  private:
	ofstream orcFile;
	bool wasRun; 
    void readOsc(OscMod *oscs, int count);
    void readNoise(NoiseMod *unit, int count);
	void readMix(MixOut *mix, int count);
	void printOsc(OscMod osc, ofstream& orcFile);
	void printNoise(NoiseMod noise, ofstream& orcFile);
	void printMix(MixOut mix, ofstream& orcFile);
	void printOrc(string file);
	void printScore(float dur, string file);

	void initialiseGlobals(OscMod *oscs, 
						   int oscCount, 
					       NoiseMod *noises, 
						   int noiseCount, 
						   ofstream& orcFile);
  public:
	ModularSynth(string name);
	void testMethod();
	void runPatch();
};
# endif
