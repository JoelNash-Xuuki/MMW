#ifndef ModularSynth_H
#define ModularSynth_H
#include <string>
#include <fstream>
using namespace std;
#define MODSYN_CHARS (128)
#define MAXMODS (256)

typedef struct {
  char frequency[MODSYN_CHARS];
  char sigOut[MODSYN_CHARS];
  char sigAm[MODSYN_CHARS];
  char sigFm[MODSYN_CHARS];
  char waveForm[MODSYN_CHARS];
  char oMin[MODSYN_CHARS];
  char oMax[MODSYN_CHARS];
} OscMod;

typedef struct {
  char sigOut[MODSYN_CHARS];
  char input[MODSYN_CHARS];
  char cutoff[MODSYN_CHARS];
  char resonance[MODSYN_CHARS];
} VcfMod;

typedef struct {
  char sigOut[MODSYN_CHARS];
  char speed[MODSYN_CHARS];
  char seed[MODSYN_CHARS];
  char oMin[MODSYN_CHARS];
  char oMax[MODSYN_CHARS];
} NoiseMod;

typedef struct {
  char outVar[MODSYN_CHARS];
  char amplitude[MODSYN_CHARS];
} MixOut;

class Rack{
  public:
    OscMod *oscs;
	NoiseMod *noises;
};

class ModularSynth{
  private:
	ofstream orcFile;
	Rack rack;
	bool wasRun; 
    void readOsc(OscMod *oscs, int count);
    void readNoise(NoiseMod *unit, int count);
    void readVcf(VcfMod *vcf, int count);
	void readMix(MixOut *mix, int count);
	void initialiseGlobals(int oscCount, 
					       NoiseMod *noises, 
						   int noiseCount, 
						   NoiseMod *sahs, 
						   int sahCount,
						   VcfMod *vcfs,
					       int vcfCount,
						   ofstream& orcFile);
	void printOrc(string file);
	void printOsc(OscMod osc, ofstream& orcFile);
	void printNoise(NoiseMod noise, ofstream& orcFile);
    void printSah(NoiseMod noise, ofstream& orcFile);
    void printVcf(VcfMod vcf, ofstream& orcFile);
	void printMix(MixOut mix, ofstream& orcFile);
	void createRackWithModules();

    string readFileIntoString(const string& path);
    int asciiToMidi(char note);
    double calculateFreq(int noteNo);
	void printScore(string file);

	
  public:
	ModularSynth(string name);
	void testMethod();
	void runPatch();
};
# endif
