sr = 44100
ksmps = 32
nchnls = 2
0dbfs  = 1

	instr 1 
ain1 	inch 1 
fout 	"../db/vocal.wav", 14, ain1
	out ain1
	endin

	instr	6
iamp	= 	p4
ifreq	= 	p5
ifn	= 	p6
kpan    =       p7
a1	loscil	iamp, ifreq, ifn
	
	outs a1*kpan, a1*kpan
	endin


