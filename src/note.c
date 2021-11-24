#include <stdio.h>

void triad(float basefreq, char *waveform);

int main(int argc, char **argv){
	note(440.0, "OSC");
}

void triad(float basefreq, char *waveform)
{
	printf ("OSC ga1 %.4f %s NONE NONE -1 1\n",basefreq, waveform);
	printf ("MIXOUT ga1 3000\n");
}
