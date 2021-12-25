#include <string>
#include <math.h>
#include "Modularsynth.hpp"
#include <cstring>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

Rack::Rack(){
  oscCount= 0;
}

ModularSynth::ModularSynth(string name){
	this->wasRun = false;
	createRackWithModules();
}

void ModularSynth::testMethod(){
  this->wasRun = true;
}

void ModularSynth::runPatch(){
  printOrc("patch.orc");
  printScore("patch.sco"); 
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

void ModularSynth::readVcf(VcfMod *vcf, int count){
  scanf("%s %s %s %s", vcf[count].sigOut, 
			           vcf[count].input,
				       vcf[count].cutoff,
					   vcf[count].resonance);
}

void ModularSynth::readMix(MixOut *mix, int count){
  scanf("%s %s", mix[count].outVar, mix[count].amplitude);
}

void ModularSynth::createRackWithModules(){
  rack= Rack();
}

void ModularSynth::printOrc(string fileName){
  
  NoiseMod *sahs;
  VcfMod *vcfs;
  MixOut *mixes;

  int oscCount= 0, 
	  noiseCount= 0, 
	  sahCount= 0, 
	  vcfCount= 0,
	  mixCount= 0;
  float duration = 10.0;
  char moduleName[64];
  int i;
  const char* patch = "~/MMW/doc/patches/FM";
  FILE *patchFile = fopen(patch, "FM");

  rack.oscs= (OscMod *) malloc(MAXMODS * sizeof(OscMod));
  rack.noises= (NoiseMod *) malloc(MAXMODS * sizeof(NoiseMod));
  sahs= (NoiseMod *) malloc(MAXMODS * sizeof(NoiseMod));
  vcfs= (VcfMod *) malloc(MAXMODS * sizeof(VcfMod));
  mixes= (MixOut *) malloc(MAXMODS * sizeof(MixOut));

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
	  readOsc(rack.oscs, rack.oscCount++); 
    } else if(! strcmp(moduleName, "MIXOUT")){ 
	  readMix(mixes, mixCount++);
	} else if(! strcmp(moduleName, "NOISE")) {
	  readNoise(rack.noises, noiseCount++);
	} else if(! strcmp(moduleName, "SAH")){
	  readNoise(sahs, sahCount++);
	} else if(! strcmp(moduleName, "VCF")){
      readVcf(vcfs, vcfCount++);
	} else if (! strcmp(moduleName, "DURATION")){
	  scanf("%f", &duration);
	} else{
	  fprintf(stderr, "%s is an unknown module\n", 
 								      moduleName);
	}
  }

  initialiseGlobals(rack.oscCount, 
					rack.noises, 
					noiseCount,
					sahs, 
					sahCount,
				    vcfs, 
					vcfCount,
					orcFile);
  
  for(i=0; i< rack.oscCount; i++)
    printOsc(rack.oscs[i], orcFile);

  for(i=0; i< noiseCount; i++)
    printNoise(rack.noises[i], orcFile);

  for(i=0; i< sahCount; i++)
    printSah(sahs[i], orcFile);

  for(i=0; i< vcfCount; i++)
    printVcf(vcfs[i], orcFile);

  for(i=0; i< mixCount; i++)
    printMix(mixes[i], orcFile);

  orcFile << "\tendin\n\n";

  orcFile.close();
}

string ModularSynth::readFileIntoString(const string& path) {
  ifstream input_file(path);
  if (!input_file.is_open()) {
    cerr << "Could not open the file - '"
      << path << "'" << endl;
   exit(EXIT_FAILURE);
  }
  return string((istreambuf_iterator<char>(input_file)), 
  		 istreambuf_iterator<char>());
}

int ModularSynth::asciiToMidi(char note){
  return note - 39; 
}

double ModularSynth::calculateFreq(int noteNo){
  double freq;
  double semitoneRatio= pow(2, 1./12.0);
  double c4= 220.0 * pow(semitoneRatio, 3);
  double c0= c4 * pow(0.5, 5);
  return freq= c0 * pow(semitoneRatio, noteNo);
}

void ModularSynth::printScore(string file){
  double freq;
  bool octDownOne, octDownTwo;
  double startTime= 0;
  orcFile.open(file);
  string notes= readFileIntoString("doc/Score/test.score");
  double duration= 0.25;

  orcFile << "f1 0 8192 10 1;sine \n";
  orcFile << "f2 0 8192 10 1 0 .111 0 .04 0 .02 0;tri\n";
  orcFile << "f3 0 8192 10 1 .5 .333 .25 .2 .166 .142 .125;sawtth\n";
  orcFile << "f4 0 8192 10 1 0 .333 0 .2 0 .142 0 .111;square\n";
  orcFile << "f5 0 8192 10 1 1 1 1 1 1 1 1 1 1 1 1 1;pulse\n";
  orcFile << "t0 76" << endl;
  
  regex noteLetter("[a-gr]| [a-gr] ");
  regex rhythmPat("4");

  freq /= 2;
  
  smatch noteLetterMatches;
  smatch rhythmMatches;
  
  if(regex_search(notes, noteLetterMatches, noteLetter)){
    if(notes[0] > 96 && notes[0] < 104 ){
      freq= calculateFreq(asciiToMidi(notes[0]));
	}
    cout << "Test Letter: " << noteLetterMatches[0];
  }
  
  if(regex_search(notes, rhythmMatches, rhythmPat)){
    cout << "Test rhythme: " << rhythmMatches[0];
  }
  
  orcFile << "i1 "<< startTime << " " <<  duration 
    << " " << freq << endl;
  startTime += 4;
    orcFile << "e";
}

void ModularSynth::initialiseGlobals(int oscCount, 
							         NoiseMod *noises, 
									 int noiseCount, 
									 NoiseMod *sahs, 
									 int sahCount,
									 VcfMod *vcfs,
									 int vcfCount,
                                     ofstream& orcFile){
  int i; 
  for(i= 0; i < oscCount; i++){
    orcFile << rack.oscs[i].sigOut << " init 0.0\n";
  }
  for(i= 0; i < noiseCount; i++){
    orcFile << noises[i].sigOut << " init 0.0\n";
  }
  for(i= 0; i < sahCount; i++){
    orcFile << sahs[i].sigOut << " init 0.0\n";
  }
  for(i= 0; i < vcfCount; i++){
    orcFile << vcfs[i].sigOut << " init 0.0\n";
  }
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

void ModularSynth::printSah(NoiseMod noise, ofstream& orcFile){
 float  oMin, oMax, mo2;
  orcFile << noise.sigOut << " randh 1.0, " << noise.speed << ", " << noise.seed << endl;
  sscanf(noise.oMin,"%f",&oMin);
  sscanf(noise.oMax,"%f",&oMax);
  if(oMin != -1.0 || oMax != 1.0){
    mo2= (oMax - oMin) / 2.0;
	orcFile << noise.sigOut << " = " << noise.oMin << " + (" << mo2 << "*" 
            <<  noise.sigOut << " + " << mo2 << ")" << endl;  
  }
}

void ModularSynth::printVcf(VcfMod vcf, ofstream& orcFile){
  float oResonance;
  orcFile << vcf.sigOut << " moogvcf " << vcf.input << ", " << vcf.cutoff; 
  sscanf(vcf.resonance, "%f", &oResonance);
  orcFile << ", " << oResonance << endl;
}

void ModularSynth::printMix(MixOut mix, ofstream& orcFile){
  float amp;
  sscanf(mix.amplitude, "%f", &amp);
  orcFile << "kenv linseg 0, .05, " << amp << 
  ", p3-0.1," << amp << ", .05,0\n";
  orcFile <<"out (" << mix.outVar << ")*kenv\n";
}

