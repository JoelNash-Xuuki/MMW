#include <string>
#include "modularsynth.hpp"
#include <cstring>
using namespace std;

ModularSynth::ModularSynth(string name){
	this->wasRun = false;
}

void ModularSynth::testMethod(){
  this->wasRun = true;
}

void ModularSynth::patch(){
  OscMod *oscs;
  int oscCount= 0, i;
  char moduleName[64];
  oscs= (OscMod *) malloc(MAXMODS * sizeof(OscMod));

  while(scanf("%s", moduleName) != EOF){
    if(! strcmp(moduleName, "OSC")){
	  readOsc(oscs, oscCount++); 
	} else{
	  fprintf(stderr, "%s is an unknown module\n", moduleName);
	}
  }
  for(i=0; i< oscCount; i++)
    printOsc(oscs[i]);
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

void ModularSynth::printOsc(OscMod osc){
  float oMin, oMax;
  float mo2;
  printf("%s oscil ", osc.sigOut);

  if(!strcmp(osc.sigAm, "NONE")){
    printf("1.0, ");
  } else{
    printf("%s ", osc.sigAm); 
  }

  if(!strcmp(osc.sigFm, "NONE")){
    printf("%s, ", osc.frequency);
  } else{
	printf("%s * (1.0 + %s), ", osc.frequency, osc.sigFm);
  }

  if(!strcmp(osc.waveForm, "SINE")){
    printf("isine\n"); 
  }
  else if(!strcmp(osc.waveForm, "TRIANGLE")){
    printf("itriangle\n");
  }
  else if(!strcmp(osc.waveForm, "SAWTOOTH")){
    printf("isawtooth\n");
  }
  else if(!strcmp(osc.waveForm, "SQUARE")){
    printf("isquare\n");
  }
  else if(!strcmp(osc.waveForm, "PULSE")){
    printf("ipulse\n");
  }
  else {
    fprintf(stderr, "printOsc: %s is unknown"
			"- using sine instead\n", osc.waveForm);
	printf("isine\n");
  }
  sscanf(osc.oMin, "%f", &oMin);
  sscanf(osc.oMax, "%f", &oMax);
  if(oMin != -1.0 || oMax != 1.0){
    mo2= (oMax- oMin) / 2.0;
    printf("%s = %s + (%f*%s + %f)\n",
	  		osc.sigOut,
  			osc.oMin,
			mo2,
			osc.sigOut,
			mo2);
  }
}
