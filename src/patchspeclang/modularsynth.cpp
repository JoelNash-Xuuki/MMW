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

void ModularSynth::runPatch(){
  printOrc();
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

void ModularSynth::printMix(MixOut mix){
  float amp;
  sscanf(mix.amplitude, "%f", &amp);
  printf("kenv linseg 0, .05, %f, p3-0.1, %f, .05, 0\n",amp, amp);
  printf("out (%s)*kenv\n", mix.outVar);
}

void ModularSynth::printOrc(void){
  OscMod *oscs;
  MixOut *mixes;
  int oscCount= 0;
  int mixCount= 0;
  int i;
  char moduleName[64];

  oscs= (OscMod *) malloc(MAXMODS * sizeof(OscMod));
  mixes= (MixOut *) malloc(MAXMODS * sizeof(MixOut));

  printf("sr= 44100\n");
  printf("kr= 4410\n");
  printf("ksmps= 10\n");
  printf("nchnls= 1\n\n");
  printf("instr 1\n");
  printf("isine= 1\n");
  printf("itriangle= 2\n");
  printf("isawtooth= 3\n");
  printf("isquare= 4\n");
  printf("ipulse= 5\n");

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
    printOsc(oscs[i]);

  for(i=0; i< mixCount; i++)
	printMix(mixes[i]);
}

void ModularSynth::printScore(float dur){
  printf("\tendin\n\n");
  printf("f1 0 8192 10 1;sine \n");
  printf("f2 0 8192 10 1 0 .111 0 .04 0 .02 0;tri\n");
  printf("f3 0 8192 10 1 .5 .333 .25 .2 .166 .142 .125;sawtth\n");
  printf("f4 0 8192 10 1 0 .333 0 .2 0 .142 0 .111;square");
  printf("f5 0 8192 10 1 1 1 1 1 1 1 1 1 1 1 1 1;pulse\n");
  printf("i1 0 %f\n\n", dur);
  printf("e");

}
