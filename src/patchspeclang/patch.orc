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
ga3 init 0.0
ga2 randi 1.0, 8000, .1
ga1 randh 1.0, 7.45, .1384
ga1 = 200 + (600*ga1 + 600)
ga3 moogvcf ga2, ga1, 0.98
kenv linseg 0, .05, 10000, p3-0.1,10000, .05,0
out (ga3)*kenv
	endin

