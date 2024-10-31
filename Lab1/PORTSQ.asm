ORG 0H
LJMP MAIN
ORG 100H //Changed 100 to 100H
MAIN:
CALL FINDn // N in R5
MOV 30H, R5
MOV R0, #40H
CALL FINDr // R6 <= r
BACK: MOV R0, #40H
MOV A, @R0
MOV R5, 30H
BACKIN:
MOV B, R6
MUL AB //Changed MULT to MUL
MOV P1, A //Changed @P1 to P1
ACALL DELAY //Changed CALL to ACALL
DJNZ R5, BACKIN
JMP BACK

ORG 200H //Changed 200 to 200H
FINDn:
PUSH 0
MOV R0, #50H
MOV A, @R0
MOV R5, A //N
POP 0
RET

FINDr:
INC R0
MOV A, @R0
DEC R0
MOV B, @R0
DIV AB //Changed BA to AB
MOV R6, A
RET

DELAY:
PUSH ACC
PUSH B
PUSH 5
PUSH 6
MOV R5, #0FFh //Changed #FFh to #0FFh 
MOV R6, #0FFh //Changed #FFh to #0FFh 
HERE1: DEC R5
HERE2: DJNZ R6, HERE2
MOV A, R5
JNZ HERE1
POP 6
POP 5
POP B
POP ACC
RET

END