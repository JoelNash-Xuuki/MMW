#ifndef Rack_H
#define Rack_H
#include "Modules.hpp"

class Rack{
  public:
	Rack();
    OscMod *oscs;
    NoiseMod *noises;
    NoiseMod *sahs;
    VcfMod *vcfs;
    MixOut *mixes;
    int oscCount;
    int noiseCount;
    int sahCount;
    int vcfCount;
	int mixCount;
};
# endif
