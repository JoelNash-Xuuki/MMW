#ifndef ModularSynth_H
#define ModularSynth_H
#include <string>
#include <fstream>
#include "Modules.hpp"
#include "Rack.hpp"
using namespace std;

class ModularSynth{
  public:
	ModularSynth(string name);
	void runPatch();

  private:
    void createRackWithModules();
	ofstream orcFile;
	Rack rack;
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
    string readFileIntoString(const string& path);
    int asciiToMidi(char note);
    double calculateFreq(int noteNo);
	void printScore(string file);
};
# endif
