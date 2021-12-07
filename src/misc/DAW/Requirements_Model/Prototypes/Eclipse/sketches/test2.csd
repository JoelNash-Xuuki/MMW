<CsoundSynthesizer>
<CsOptions>
</CsOptions>
<CsInstruments>

sr		=	44100		
kr		=	4410
ksmps	=	10
nchnls	=	2

gacmb	init	0
garvb	init	0

	instr 	901
inotedur	=		p3
imaxamp		=		ampdb(p4)
kcarfreq	=		p5

kpchbnd		linseg	1, p7*p3, p6, p8*p3, 1

imodfreq	=		p9
ilowndx		=		p10
indxdiff	=		p11-p10

; PARAMETERS DEFINING THE ADSR AMPLITUDE ENVELOPE
; TIMES ARE A PERCENTAGE OF p3
;   attack amp  = p12    attack length  = p17
;   decay amp   = p13    decay length   = p18
;   sustain amp = p14    sustain length = p19
;   release amp = p15    release length = p20
;   end amp     = p16

; PARAMETERS DEFINING THE ADSR FREQ DEVIATION ENVELOPE
; TIMES ARE A PERCENTAGE OF p3
;   attack amp  = p21    attack length  = p26
;   decay amp   = p22    decay length   = p27
;   sustain amp = p23    sustain length = p28
;   release amp = p24    release length = p29
;   end amp     = p25

kpan line p30, p3, p31

irvbsnd	= p32
icmbsnd	= p33

aampenv		linseg	p9, p14*p3, p10, p15*p3, p11, p16*p3, p12, p17*p3, p13
adevenv		linseg	p18, p23*p3, p19, p24*p3, p20, p25*p3, p21, p26*p3, p22
amodosc		oscili	(ilowndx+indxdiff*adevenv)*imodfreq, imodfreq, 1
acarosc		oscili	imaxamp*aampenv, (kcarfreq*kpchbnd)+amodosc, 1
			outs	acarosc*kpan, acarosc*(1-kpan) 
;garvb		=		garvb+(acarosc*kpan*irvbsnd)
;gacmb		=		gacmb+(acarosc*(1-kpan)*icmbsnd)
			endin

</CsInstruments>
<CsScore>

f1 0 16384 10 1
f2  0 4096 10   1  .5 .333 .25 .2 .166 .142 .125 .111 .1 .09 .083 .076 .071 .066 .062 ;16 patials of saw wave

f101 0 4096 7 0 1 1 600 0 0   					; LINEAR AR ENV
f102 0 1024 7 0 128 1 128 .6 512 .6 256 0		; LINEAR ADSR ENV
f103 0 1024 5 .001 256 1 192 .5 256 .5 64 .001	; EXP ADSR

f104 0 1024 5 .001 100 1 824 .75 100 .001 
f105 0 1024 7 0 5 1 10 1 10 0 0 
f106 0 1024 5 .001 100 1 824 .75 100 .001

t 0 56
r4
i901 0 4 78 103.83		1 0.1 0.1	 		
1 0 0 		
.0 1.0 .75 .66 .0 	.17 .17 .49 .17		.0 1.0 .75 .66 .0 		.17 .17 .49 .17 
0.5  0.5 	
0 0

i901 1 0.02 40 223.47		1 0.1 0.1	 		
161 0 25 		
.75 .8 1.0 .15 .0 	.125 .125 .25 .5  		1.0 .0  .0  .0  .0 		.125 .25 .25 .25 
0.5  0.5 	
0 0

f 0 4
s
</CsScore>
</CsoundSynthesizer>










