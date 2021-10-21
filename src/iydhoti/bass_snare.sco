f1 0 4096 10 1

a 0 0 4

; Chorus 1
t 0 60
#include "Snares/Snare_a.sco"
f 0 8
s

{ 3
t 0 60
#include "Reverb/Reverb_a.sco"
#include "Delay/Delay_a.sco"
#include "Snares/Snare_a.sco"
#include "Bass/Bass_a.sco"
s
t 0 60
#include "Reverb/Reverb_a.sco"
#include "Delay/Delay_a.sco"
#include "Snares/Snare_a.sco"
#include "Bass/Bass_b.sco"
s
}
