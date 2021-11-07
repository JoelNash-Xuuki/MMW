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
ga4 init 0.0
ga1 init 0.0
ga2 init 0.0
ga3 init 0.0
ga4 oscil 1.0, ga1+ga2+ga3, isquare
ga1 randh 1.0, 6.0, .522
ga1 = 20 + (65*ga1 + 65)
ga2 randh 1.0, 7.15, .499
ga2 = 20 + (90*ga2 + 90)
ga3 randh 1.0, 1.33, .131
ga3 = 20 + (240*ga3 + 240)
kenv linseg 0, .05, 10000, p3-0.1,10000, .05,0
out (ga4)*kenv
	endin

