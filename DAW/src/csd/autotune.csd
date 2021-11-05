<CsoundSynthesizer>
<CsOptions>
-b128 -B256
</CsOptions>
<CsInstruments>

sr = 44100
ksmps = 64
nchnls = 1

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

instr 1

ain inch 1

interv1 = 2^(p6/12)
interv2 = 2^(p7/12)
	
ain2 	PitchShifter ain*0.5,interv1,0,0.1,5
ain3  PitchShifter ain*0.5,interv2,0,0.1,5

aout 	Autotune 	ain,0.01,p4,p5
aout2 Autotune	ain2,0.01,p4,p5
aout3 Autotune 	ain3,0.01,p4,p5

	out 		(aout+aout2+aout3)*0.5

endin 

</CsInstruments>
<CsScore>

f3 0 8 -2  0 2 4 5 7 9 11 12 ; major mode
f4 0 8 -2  0 2 3 5 7 8 10 12 ; minor mode
f5 0 16384 20 1

;       key mode intvl1 intvl2(semitones)
i1 0 600 9    4   0     3  ; C minor (natural) 6-3 harmonies


</CsScore>
</CsoundSynthesizer>
