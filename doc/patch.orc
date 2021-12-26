sr= 44100
kr= 4410
ksmps= 10
nchnls= 1

	instr 1
isine= 1
itriangle= 2
isawtooth= 3
isquare= 4
ipulse= 5
a1 init 0.0
a2 init 0.0
a3 init 0.0
a1 oscil 1.0, 0.25, isine
a1=0.1 + (0.45 * a1 + 0.45)
a2 oscil a1, 120, isine
a2=-0 + (0 * a2 + 0)
a3 oscil 1.0, p4 * (1.0+ a2), isine
kenv linseg 0, .05, 10000, p3-0.1,10000, .05,0
out (a3)*kenv
	endin

