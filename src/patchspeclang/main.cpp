#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "modularsynth.hpp"
#include "score.hpp"

int main(int argc, char **argv){
  ModularSynth ms= ModularSynth("synth");
  ms.runPatch();
  Score s= Score("test.ly");
  system("lilypond test.ly");
  return 0;
}
