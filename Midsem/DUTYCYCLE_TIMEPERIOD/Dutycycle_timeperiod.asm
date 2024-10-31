ORG 0H
LJMP MAIN
ORG 100H


MAIN:
//Roll number is 22b3914
//So duty cycle is 10% and time period is 4ms
OUTPUT_LOOP:
SETB P1.0
CALL DELAY_400us
CLR P1.0
CALL delay_3600us
SJMP OUTPUT_LOOP

ORG 130H
	
//Measured Values are
//Time period = 4ms
//On period = 402us
//Duty cycle = 4.02%

DELAY_400us:
mov r0, #2
h2: acall delay_200us
djnz r0, h2
ret

delay_3600us:
mov r0, #18
h3: acall delay_200us
djnz r0, h3
ret
 delay_200us:
push 00h
mov r0, #194
h1: djnz r0, h1
pop 00h
ret
END