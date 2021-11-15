sr	=	44100		
ksmps	=	32
nchnls	=	2

gacmb	init	0
garvb	init	0

opcode  PitchShifter, a, akkii 
        setksmps  1                   ; kr=sr 
asig,kpitch,kfdb,idel,iwin  xin 
kdelrate = (kpitch-1)/idel 
avdel   phasor -kdelrate               ; 1 to 0 
avdel2  phasor -kdelrate, 0.5          ; 1/2 buffer offset  
afade  tablei avdel, iwin, 1, 0, 1     ; crossfade windows 
afade2 tablei avdel2,iwin, 1, 0, 1 
adump  delayr idel                  
atap1  deltapi avdel*idel           ; variable delay taps 
atap2  deltapi avdel2*idel 
amix   =   atap1*afade + atap2*afade2  ; fade in/out the delay taps 
       delayw  asig+amix*kfdb          ; in+feedback signals 
       xout  amix 
endop

/**** autotune  ***********************************/
/* aout Autotune asig,ism,ikey,ifn[,imeth]        */
/* asig - input                                   */
/* ism - smoothing time in secs                   */
/* ikey - key (0 = C,... ,11 = B    		  */
/* ifn - table containing scale pitch classes (7) */
/* imeth - pitch track method: 0 - pitch (default)*/
/*         1 - ptrack, 2 - pitchamdf              */
/**************************************************/

opcode Autotune, a, aiiio

iwinsize = 1024
ibase = 440
ibasemidi = 69

asig,ism,itrans,ifn,im  xin

if im == 0 then
kfr, kamp pitch asig,0.1,6.00,9.00,0
kfr = cpsoct(kfr)
elseif im == 1 then
kfr, kamp ptrack asig, 1024
else
kfr, kamp pitchamdf asig,130,1040
endif
 
if (kfr > 10) kgoto ok
kfr = 440
ok: 

ktemp = 12 * (log(kfr / ibase) / log(2)) + ibasemidi
ktet = round(ktemp)

kpos init 0
itrans = 2
test:
knote table kpos, ifn     ; get a pitch class from table
ktest = ktet % 12       ;  note mod 12
knote = (knote+itrans) % 12 ; plus transpose interval mod 12
if ktest == knote kgoto next ; test if note matches pitch class + transposition
kpos = kpos + 1           ; increment table pos
if kpos >= 7  kgoto shift ; if more than or pitch class set we need to shift it
kgoto test                ; loop back

shift:
if (ktemp >= ktet) kgoto plus
ktet = ktet - 1
kgoto next
plus:
ktet = ktet + 1

next:
kpos = 0
ktarget = ibase * (2 ^ ((ktet - ibasemidi) / 12))
kratio = ktarget/kfr
kratioport port kratio, ism, ibase 

aout PitchShifter asig,kratioport,0,0.1,5
  
      xout     aout
endop

instr 180

ain inch 1

interv1 = 2^(p6/12)
interv2 = 2^(p7/12)
	
ain2  PitchShifter ain*0.5,interv1,0,0.1,5
ain3  PitchShifter ain*0.5,interv2,0,0.1,5

aout 	Autotune 	ain,0.01,p4,p5
aout2 Autotune	ain2,0.01,p4,p5
aout3 Autotune 	ain3,0.01,p4,p5

	out 		(aout+aout2+aout3)*0.5

endin 
	instr 	901
imaxamp		=	ampdb(p4)
kcarfreq	=	p5

imodfreq	=	p6
ilowndx		=	p7
indxdiff	=	p8-ilowndx

iattPch  	= 	p9
idecPch 	= 	p10
isusPch		=	p11
irelPch		= 	p12
iendPch		= 	p13

ipchAttLen 	= 	p14 
ipchDecLen 	= 	p15
ipchSusLen	=	p16
ipchRelLen	= 	p17

iattAmp  	= 	p18    
idecAmp   	= 	p19    
isusAmp 	= 	p20    
irelAmp 	= 	p21    
iendAmp     	= 	p22

iattLen  	= 	p23
idecLen   	= 	p24
isusLen 	= 	p25
irelLen 	= 	p26

iattAmpFD  	= 	p27    
idecAmpFD   	= 	p28    
isusAmpFD 	= 	p29    
irelAmpFD 	= 	p30    
iendAmpFD     	= 	p31

iattLenFD 	= 	p32
idecLenFD 	= 	p33
isusLenFD 	= 	p34
irelLenFD 	= 	p35

irvbsnd		= 	p36
icmbsnd		= 	p37

kpan 		line 	p38, p3, p39

kpchbnd		linseg	iattPch, ipchAttLen*p3, idecPch, ipchDecLen*p3, isusPch, ipchSusLen*p3, irelPch, ipchRelLen*p3, iendPch
aampenv		linseg	iattAmp, iattLen*p3, idecAmp, idecLen*p3, isusAmp, isusLen*p3, irelAmp, irelLen*p3, iendAmp

adevenv		linseg	iattAmpFD, iattLenFD*p3, idecAmpFD, idecLenFD*p3, isusAmpFD, isusLenFD*p3, irelAmpFD, irelLenFD*p3, iendAmpFD

amodosc		oscili	(ilowndx+indxdiff*adevenv)*imodfreq, imodfreq, 1
acarosc		oscili	imaxamp*aampenv, (kcarfreq*kpchbnd)+amodosc, 1
adeclk 		linsegr 0, .004, 1, p3, 1, .05, 0.01

		outs	(acarosc*kpan)*adeclk, (acarosc*(1-kpan))*adeclk
garvb		=	garvb+(acarosc*irvbsnd)
gacmb		=	gacmb+(acarosc*icmbsnd)
			endin

		instr 1
iamp = ampdb(p4)
ilen tableng p5
aphas phasor 1/(ilen/sr)
iphaseSet = 0
aphas = (aphas + iphaseSet) * ilen
kenv oscil iamp, 1
asig tablekt aphas, p5
adeclk linsegr 0, .004, 1, p3, .0, .0, 0
asig = ((asig * iamp) * adeclk) * kenv 
	out asig
	endin

	instr 2
a1 oscil p4, p5, p6
adeclk linsegr 0, .004, 1, p3, .0, .0, 0
	out (a1*adeclk)
	endin

	instr 3
ain1 in 
adel linseg 0, p3*.5, 0.02, p3*.5, 0
aout flanger ain1, adel, .7
out aout
	endin

	instr 4
iamp = ampdb(p4)
kpchbnd		linseg	p5, p8*p3, p6, p9*p3, p7
a1	pluck iamp, p5+kpchbnd, p10, p11, p12
kpan line p13, p3, p14
	outs a1*kpan, a1*(1-kpan)
	endin

	instr 	5

kamp	= ampdb(p4)
kfreq   = p5
kdens	= p6
kampDev = p7
kpitchDev = p8
kgdur = p9
igfn = p10

;a1 	grain 	kamp, kfreq, kdens, kampDev, kpitchDev, kgdur, igfn  
a1 	grain kamp, kfreq, kdens, kampDev, kpitchDev, kgdur, igfn, 3, 1  
	out a1
	endin

	instr	6
iamp	= 	ampdb(p4)
ifreq	= 	p5
ifn	= 	p6
irvbsnd = 	p7
icmbsnd =       p8
a1	loscil	iamp, ifreq, ifn
garvb		=		garvb+(a1*irvbsnd)
gacmb		=		gacmb+(a1*icmbsnd)
	
	outs a1, a1
	endin

	instr 7
iamp	= 	p4
ipitch  = 	p5
iskip	=       p6
irvbsnd = 	p7
icmbsnd =       p8

a1, a2 diskin2 "Audio/test.wav", ipitch, iskip
	outs a1*iamp, a2*iamp
garvb		=		garvb+(a1*irvbsnd)
gacmb		=		gacmb+(a1*icmbsnd)
	endin 

		instr	128
idur	=		p3
iamp	=		ampdb(p4)
ifrq	=		p5
iatk	=		p6
irel	=		p7
icf1	=		p8
icf2	=		p9
ibw1	=		p10
ibw2	=		p11
kpan line p12, p3, p13
irvbsnd	= p14
icmbsnd	= p15

kenv	expseg	.001, iatk, iamp, idur/6, iamp*.4, idur-(iatk+irel+idur/6), iamp*.6, irel,.01
anoise	rand	ifrq
kcf		expon	icf1, idur, icf2
kbw		line	ibw1, idur, ibw2
afilt	reson	anoise, kcf, kbw, 2
       	outs  	(afilt*kenv)*kpan, (afilt*kenv)*(1-kpan)  
garvb		=		garvb+(afilt*irvbsnd)
gacmb		=		gacmb+(afilt*icmbsnd)
		endin

		instr 1001
ain1 		inch 1
		fout "Audio/vocal1.wav", 14, ain1
		outs ain1

;garvb		=		garvb+(ainauto*irvbsnd)
;gacmb		=		gacmb+(ainauto*icmbsnd)		
		endin


; EFFECTS

; DELAY
		instr	198
idur	=		p3
itime 	= 		p4
iloop 	= 		p5
kenv	linen	1, .01, idur, .01
acomb 	comb	gacmb, itime, iloop, 0
		out		acomb*kenv
gacmb	=		0
		endin

;REVERB
		instr 	199
idur	=		p3					
irvbtim	=		p4
ihiatn	=		p5
arvb	reverb2	garvb, irvbtim, ihiatn
		out		arvb
garvb	=		0
		endin



