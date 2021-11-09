sr = 44100 
ksmps = 32 
nchnls = 2 
0dbfs  = 1 

gacmb	init	0
garvb	init	0

instr	1 
iamp	= 	p4 
ifreq	= 	p5 
ifn	= 	p6 
ilpf    =       p7
ihpf    =       p8
ipan	=	p9 
icmbsnd =	p10
irvbsnd =	p11

a1	loscil	iamp, ifreq, ifn
a1	butterlp a1, ilpf
a1	butterhp a1, ihpf
    	outs a1*ipan, a1*ipan
gacmb   = gacmb+(a1*icmbsnd)
garvb   = garvb+(a1*irvbsnd)
    	endin

instr	198 ;DELAY
idur	=		p3
itime 	= 		p4
iloop 	= 		p5
ipan    =               p6
kenv	linen	1, .01, idur, .01
acomb 	comb	gacmb, itime, iloop, 0
		outs	(acomb*kenv)*ipan, (acomb*kenv)*ipan
gacmb	=		0
		endin

instr 	199 ;REVERB
idur	=		p3					
irvbtim	=		p4
ihiatn	=		p5
ipan    =               p6
arvb	reverb2	garvb, irvbtim, ihiatn
		outs arvb*ipan, arvb*ipan
garvb	=		0
		endin


