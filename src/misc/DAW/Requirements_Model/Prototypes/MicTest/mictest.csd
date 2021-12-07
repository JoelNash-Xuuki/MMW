<CsoundSynthesizer>
<CsOptions>
-odac -iadc
</CsOptions>
<CsInstruments>

sr = 44100
ksmps = 32
nchnls = 1
0dbfs  = 1

	instr 1 

	ain1 in 
;	adel linseg 0, p3*.5, 2.02, p3*.5, 0	;max delay time = 20ms
;	aout flanger ain1, adel, 0.2
    out ain1
	endin

</CsInstruments>
<CsScore>

i 1 0 100
e
</CsScore>
</CsoundSynthesizer>
