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
ga2 init 0.0
ga1 init 0.0
ga2 oscil ga1, 380, isine
ga1 randi 1.0, 100, .222
kenv linseg 0, .05, 1000, p3-0.1,1000, .05,0
out (ga2)*kenv
	endin

