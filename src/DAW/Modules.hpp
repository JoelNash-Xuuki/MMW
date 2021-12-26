#ifndef Modules_H
#define Modules_H
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
# endif
