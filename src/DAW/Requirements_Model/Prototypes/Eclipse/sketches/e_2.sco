f1 0 16384 10 1
f2 0 0 1 "patch4.wav" 0 4 0
f3 0 0 1 "patch3.wav" 0 4 0
f5 0 0 1 "patch5.wav" 0 4 0
f6 0 0 1 "HiHat1.wav" 0 4 0
f7 0 0 1 "sine_patch.wav" 0 4 0

f101 0 4096 7 0 1 1 600 0 0   					; LINEAR AR ENV
f102 0 1024 7 0 128 1 128 .6 512 .6 256 0		; LINEAR ADSR ENV
f103 0 1024 5 .001 256 1 192 .5 256 .5 64 .001	; EXP ADSR

f104 0 1024 5 .001 100 1 824 .75 100 .001 
f105 0 1024 7 0 5 1 10 1 10 0 0 
f106 0 1024 5 .001 100 1 824 .75 100 .001

t 0 56

;M1
;Sub
i 901 0 4 78 51.91 	1 0 5 .0 1.0 .75 .66 .0  	.17 .17 .49 .17 	.0  1.0 .75 .66 .0  	.17 .17 .49 .17 	0.5  0.5
;Bass
i 901 0 0.3 78 103.83 	1 0 5 .0 1.0 .75 .66 .0 	.17  .17  .49 .17	.0  1.0 .75 .66 .0 		.17 .17  .49 .17 	0.5  0.5
i 901 4 0.3 78 130.81 	1 0 5 .0 1.0 .75 .66 .0  	.17 .17 .49 .17 	.0  1.0 .75 .66 .0  	.17 .17 .49 .17 	0.5  0.5
i 901 6 0.3 78 98.00 	1 0 5 .0 1.0 .75 .66 .0  	.17 .17 .49 .17 	.0  1.0 .75 .66 .0  	.17 .17 .49 .17 	0.5  0.5

;Harmony
i 901 0 8 48 207.65 	0.1 0 5 .0 1.0 .75 .66 .0  		.17 .17 .49 .17  	.0  1.0 .75 .66 .0  	.17 .17 .49 .17 	1    1
i 901 0 8 48 261.63 	0.1 0 5 .0 1.0 .75 .66 .0  		.17 .17 .49 .17  	.0  1.0 .75 .66 .0  	.17 .17 .49 .17 	0.15 0.8
i 901 0 8 48 311.13 	0.1 0 5 .0 1.0 .75 .66 .0  		.17 .17 .49 .17  	.0  1.0 .75 .66 .0  	.17 .17 .49 .17 	0.25 0.9 
i 901 0 8 48 392.00 	0.1 0 5 .0 1.0 .75 .66 .0  		.17 .17 .49 .17  	.0  1.0 .75 .66 .0  	.17 .17 .49 .17 	0 0

;Percussion
i 901 1 0.2 58 123.47 		161 0 25	.75 .8   1.0 .15 .0 	.125 .125 .25 .5  		1.0 .0  .0  .0  .0 		.125 .25 .25 .25 	0.0	 0.0
i 901 1.75 0.15 58 127.47 		161 0 25	.75 .8   1.0 .15 .0 	.125 .125 .25 .5  		1.0 .0  .0  .0  .0 		.125 .25 .25 .25 	0.0	 0.0
i 901 2.5 0.2 78 103.83 		55 	0 5 	.75 .8   1.0 .15 .0 	.125 .125 .25 .5  		1.0 .0  .0  .0  .0 		.125 .25 .25 .25 	1.0  1.0
i 901 3 0.15 58 117.47 		161 0 25	.75 .8   1.0 .15 .0 	.125 .125 .25 .5  		1.0 .0  .0  .0  .0 		.125 .25 .25 .25 	0.0	 0.0
i 901 3.25 0.2 68 207.65 		55 0 25		.75 .8   1.0 .15 .0 	.125 .125 .25 .5  		1.0 .0  .0  .0  .0 		.125 .25 .25 .25 	0.1	 0.1

;M2
;Sub
i 901 4 2 78 65.41 	0.1 0 5 .0 1.0 .75 .66 .0  	.17 .17 .49 .17 	.0  1.0 .75 .66 .0  	.17 .17 .49 .17 	0.5  0.5
i 901 6 2 78 49.00 	1 0 5 .0 1.0 .75 .66 .0  	.17 .17 .49 .17 	.0  1.0 .75 .66 .0  	.17 .17 .49 .17 	0.5  0.5

;Percussion
i 901 5 0.2 58 123.47 		161 0 25	.75 .8   1.0 .15 .0 	.125 .125 .25 .5  		1.0 .0  .0  .0  .0 		.125 .25 .25 .25 	0.0	 0.0
i 901 5.75 0.15 58 127.47 		161 0 25	.75 .8   1.0 .15 .0 	.125 .125 .25 .5  		1.0 .0  .0  .0  .0 		.125 .25 .25 .25 	0.0	 0.0
i 901 6.5 0.2 78 103.83 		55 	0 5 	.75 .8   1.0 .15 .0 	.125 .125 .25 .5  		1.0 .0  .0  .0  .0 		.125 .25 .25 .25 	1.0  1.0
i 901 7 0.15 58 117.47 		161 0 25	.75 .8   1.0 .15 .0 	.125 .125 .25 .5  		1.0 .0  .0  .0  .0 		.125 .25 .25 .25 	0.0	 0.0
i 901 7.25 0.2 68 207.65 		55 0 25		.75 .8   1.0 .15 .0 	.125 .125 .25 .5  		1.0 .0  .0  .0  .0 		.125 .25 .25 .25 	0.1	 0.1

; imma keep keep my love in a tub on a boat out at sea while i cut my thoart so i die when bleed
; frame the whole scene from high up seat in moon light while ocean was silence but one single scream 
; two eyes behind purple blinds did they see
; fine decore and an on going phone call, a man short of dream
; unless we behold him caught in between
; somewhere beyond while they force to get in
; but they can't get in
; a barricade and a violin 
; two white gloves and a shiny grin 
; one true love and a violent end
; with the sail up, the horizon bends
; the whole scene spins in the eye of a wren
; in a cotten tie does it flys off again  

; the meaning lost and a trial 10
; months later it was daylight again
; they had pictures with nobody in
; we may have wishes to go back again 

; the whether changed, the love did too in was in the news
; 5ft 10 born in 1992
; sad and confused, 
; back on land theres a show of hands for the tragity true, mad and abused
; into the blue
; they met at work think hes into you
; checkered shirt and light perfume
; friends are jerks i forget them too
; two fish caugh in a net
;


; in a cotton a tie and a wife when his in
; a tree on the beach and two towels by a bin

; some where right him  
; one grey cloud 
; back on land

; the whthere changed
; back on land theres a show of hands

 
; dip a toe in the water

; but things move on and we know that my friend k
;

; born 92 in was on the news
;

; you can see through win
; do you kjk
; 

; 5ft 10 ; 

; a violent act 
; sigh and then let my breath hit the sails
; say cheese
; squat team

; back there bags before th emilirary
