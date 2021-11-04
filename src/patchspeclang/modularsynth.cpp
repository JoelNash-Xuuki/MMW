#include <string>
#include "modularsynth.hpp"
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;
ModularSynth::ModularSynth(string name){
	this->wasRun = false;
}
void ModularSynth::testMethod(){
  this->wasRun = true;
}
void ModularSynth::runPatch(){
  printOrc("patch.orc");
  printScore(10.0, "patch.sco"); 
}
void ModularSynth::readOsc(OscMod *oscs, int count){
  scanf("%s %s %s %s %s %s %s",
	  oscs[count].sigOut, 
	  oscs[count].frequency,
	  oscs[count].waveForm, 
	  oscs[count].sigAm,
	  oscs[count].sigFm,
	  oscs[count].oMin,
	  oscs[count].oMax);
  if(count >= MAXMODS){
    fprintf(stderr, 
			"Number of oscillators has exceeded maximum: %d\n", 
		    MAXMODS);
    exit(1);
  }
}
void ModularSynth::readNoise(NoiseMod *unit, int count){
  scanf("%s %s %s %s %s", unit[count].sigOut,
						  unit[count].speed,
					      unit[count].seed,
						  unit[count].oMin,
						  unit[count].oMax);
}
void ModularSynth::readMix(MixOut *mix, int count){
  scanf("%s %s", mix[count].outVar, mix[count].amplitude);
}
void ModularSynth::printOsc(OscMod osc, ofstream& orcFile){
  float oMin, oMax;
  float mo2;
  orcFile << osc.sigOut << " oscil ";

  if(!strcmp(osc.sigAm, "NONE")){
    orcFile << "1.0, ";
  } else{
    orcFile << osc.sigAm << ", "; 
  }

  if(!strcmp(osc.sigFm, "NONE")){
    orcFile << osc.frequency << ", ";
  } else{
    orcFile << osc.frequency << " * (1.0+ "<<osc.sigFm << "), ";
  }

  if(!strcmp(osc.waveForm, "SINE")){
    orcFile << "isine\n"; 
  }
  else if(!strcmp(osc.waveForm, "TRIANGLE")){
    orcFile << "itriangle\n";
  }
  else if(!strcmp(osc.waveForm, "SAWTOOTH")){
    orcFile << "isawtooth\n";
  }
  else if(!strcmp(osc.waveForm, "SQUARE")){
    orcFile << "isquare\n";
  }
  else if(!strcmp(osc.waveForm, "PULSE")){
    orcFile << "ipulse\n";
  }
  else {
    fprintf(stderr, "printOsc: %s is unknown"
    		"- using sine instead\n", osc.waveForm);
    orcFile << "isine\n";
  }
  sscanf(osc.oMin, "%f", &oMin);
  sscanf(osc.oMax, "%f", &oMax);
  if(oMin != -1.0 || oMax != 1.0){
    mo2= (oMax- oMin) / 2.0;
    orcFile << osc.sigOut << "=" << osc.oMin << " + (" << mo2 << 
    " * " << osc.sigOut << " + " << mo2 << ")\n";
  }
}
void ModularSynth::printNoise(NoiseMod noise, ofstream& orcFile){
  float  oMin, oMax, mo2;
  orcFile << noise.sigOut << " randi 1.0, " << noise.speed << ", " << noise.seed << endl;
  sscanf(noise.oMin,"%f",&oMin);
  sscanf(noise.oMax,"%f",&oMax);
  if(oMin != -1.0 || oMax != 1.0){
    mo2= (oMax - oMin) / 2.0;
	orcFile << noise.sigOut << " = " << noise.oMin << " + (" << mo2 << "*" 
            <<  noise.sigOut << " + " << mo2 << ")" << endl;  
  }
}
void ModularSynth::printMix(MixOut mix, ofstream& orcFile){
  float amp;
  sscanf(mix.amplitude, "%f", &amp);
  orcFile << "kenv linseg 0, .05, " << amp << 
  ", p3-0.1," << amp << ", .05,0\n";
  orcFile <<"out (" << mix.outVar << ")*kenv\n";
}
void ModularSynth::printOrc(string fileName){
  OscMod *oscs;
  NoiseMod *noises;
  MixOut *mixes;

  int oscCount= 0, noiseCount= 0, mixCount= 0;
  float duration = 10.0;
  char moduleName[64];
  int i;
  const char* filename = "patch";
  FILE *patchFile = fopen(filename, "r");

  oscs= (OscMod *) malloc(MAXMODS * sizeof(OscMod));
  mixes= (MixOut *) malloc(MAXMODS * sizeof(MixOut));
  noises= (NoiseMod *) malloc(MAXMODS * sizeof(MixOut));

  orcFile.open(fileName);

  orcFile << "sr= 44100\n";
  orcFile << "kr= 4410\n";
  orcFile << "ksmps= 10\n";
  orcFile << "nchnls= 1\n\n";
  orcFile << "\tinstr 1\n";
  orcFile << "isine= 1\n";
  orcFile << "itriangle= 2\n";
  orcFile << "isawtooth= 3\n";
  orcFile << "isquare= 4\n";
  orcFile << "ipulse= 5\n";

  while(scanf("%s", moduleName) != EOF){
    if(! strcmp(moduleName, "OSC")){
	  readOsc(oscs, oscCount++); 
    } else if(! strcmp(moduleName, "MIXOUT")){ 
	  readMix(mixes, mixCount++);
	} else if(! strcmp(moduleName, "NOISE")) {
	  readNoise(noises, noiseCount++);
	} else if (! strcmp(moduleName, "DURATION")){
	  scanf("%f", &duration);
	} else{
	  fprintf(stderr, "%s is an unknown module\n", moduleName);
	}
  }

  initialiseGlobals(oscs, 
					oscCount, 
					noises, 
					noiseCount,
					orcFile);
  
  for(i=0; i< oscCount; i++)
    printOsc(oscs[i], orcFile);

  for(i=0; i< noiseCount; i++)
    printNoise(noises[i], orcFile);

  for(i=0; i< mixCount; i++)
    printMix(mixes[i], orcFile);

  orcFile << "\tendin\n\n";

  orcFile.close();
}
void ModularSynth::printScore(float dur, string file){
orcFile.open(file);
orcFile << "f1 0 8192 10 1;sine \n";
orcFile << "f2 0 8192 10 1 0 .111 0 .04 0 .02 0;tri\n";
orcFile << "f3 0 8192 10 1 .5 .333 .25 .2 .166 .142 .125;sawtth\n";
orcFile << "f4 0 8192 10 1 0 .333 0 .2 0 .142 0 .111;square\n";
orcFile << "f5 0 8192 10 1 1 1 1 1 1 1 1 1 1 1 1 1;pulse\n";
orcFile << "i1 0 " <<  dur << endl;
orcFile << "e";
}
void ModularSynth::initialiseGlobals(OscMod *oscs, 
									 int oscCount, 
							         NoiseMod *noises, 
									 int noiseCount, 
                                     ofstream& orcFile){
  int i; 
  for(i= 0; i < oscCount; i++){
    orcFile << oscs[i].sigOut << " init 0.0\n";
  }
  for(i= 0; i < noiseCount; i++){
    orcFile << noises[i].sigOut << " init 0.0\n";
  }
}
