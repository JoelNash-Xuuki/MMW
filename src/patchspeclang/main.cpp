#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "modularsynth.hpp"

int main(int argc, char **argv){
  ModularSynth ms= ModularSynth("synth");
  ms.patch();

  return 0;
}
