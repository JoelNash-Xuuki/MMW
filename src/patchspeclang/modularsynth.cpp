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
  printScore(10.0); 
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
    orcFile << osc.sigAm << " "; 
  }

  if(!strcmp(osc.sigFm, "NONE")){
    orcFile << osc.frequency << " ";
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

void ModularSynth::printMix(MixOut mix, ofstream& orcFile){
  float amp;
  sscanf(mix.amplitude, "%f", &amp);
  orcFile << "kenv linseg 0, .05, " << amp << 
  ", p3-0.1," << amp << ", .05,0\n";
  orcFile <<"out (" << mix.outVar << ")*kenv\n";
}

void ModularSynth::printOrc(string file){
  OscMod *oscs;
  MixOut *mixes;
  int oscCount= 0;
  int mixCount= 0;
  int i;
  char moduleName[64];

  oscs= (OscMod *) malloc(MAXMODS * sizeof(OscMod));
  mixes= (MixOut *) malloc(MAXMODS * sizeof(MixOut));

  orcFile.open(file);
  orcFile << "sr= 44100\n";
  orcFile << "kr= 4410\n";
  orcFile << "ksmps= 10\n";
  orcFile << "nchnls= 1\n\n";
  orcFile << "instr 1\n";
  orcFile << "isine= 1\n";
  orcFile << "itriangle= 2\n";
  orcFile << "isawtooth= 3\n";
  orcFile << "isquare= 4\n";
  orcFile << "ipulse= 5\n";
  orcFile << "instr 1\n";

  while(scanf("%s", moduleName) != EOF){
    if(! strcmp(moduleName, "OSC")){
	  readOsc(oscs, oscCount++); 
    } else if(! strcmp(moduleName, "MIXOUT")){ 
	  readMix(mixes, mixCount++);
	} else{
	  fprintf(stderr, "%s is an unknown module\n", moduleName);
	}
  }
  for(i=0; i< oscCount; i++)
    printOsc(oscs[i], orcFile);

  for(i=0; i< mixCount; i++)
    printMix(mixes[i], orcFile);

  orcFile << "\tendin\n\n";

  orcFile.close();
}

void ModularSynth::printScore(float dur){
  printf("f1 0 8192 10 1;sine \n");
  printf("f2 0 8192 10 1 0 .111 0 .04 0 .02 0;tri\n");
  printf("f3 0 8192 10 1 .5 .333 .25 .2 .166 .142 .125;sawtth\n");
  printf("f4 0 8192 10 1 0 .333 0 .2 0 .142 0 .111;square\n");
  printf("f5 0 8192 10 1 1 1 1 1 1 1 1 1 1 1 1 1;pulse\n");
  printf("i1 0 %f\n\n", dur);
  printf("e");

}
