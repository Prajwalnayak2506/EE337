ORG 0H
LJMP MAIN
ORG 100H
MAIN:
ACALL DET
MOV R6,69H
CJNE R6,#0,INVERTIBLE
	MOV R3,#9
	MOV R1,#70H
	SINGULAR_OUT:
	MOV @R1,#0FFH
	INC R1
	DJNZ R3,SINGULAR_OUT
	SJMP HERE
INVERTIBLE:
	ACALL COFACTOR_MATRIX
	ACALL ADJ_FROM_CO
HERE: SJMP HERE
ORG 130H

DET:
MOV R3, 64H
MOV R4, 68H
MOV R5, 65H
MOV R6, 67H
ACALL AB_SUB_CD
MOV B,R2
MOV A,60H
MUL AB
MOV 69H,A
//Temporary Determinant at 75H

MOV R3, 65H
MOV R4, 66H
MOV R5, 63H
MOV R6, 68H
ACALL AB_SUB_CD
MOV B,R2
MOV A,61H
MUL AB
ADD A,69H
MOV 69H,A

MOV R3, 63H
MOV R4, 67H
MOV R5, 64H
MOV R6, 66H
ACALL AB_SUB_CD
MOV B,R2
MOV A,62H
MUL AB
ADD A,69H
MOV 69H,A


RET

//USING R3,R4,R5,R6 as inputs
//Store output at R2
AB_SUB_CD:
MOV A,R5
MOV B,R6
MUL AB
MOV R2,A
MOV A,R3
MOV B,R4
MUL AB
CLR C
SUBB A,R2
MOV R2,A
RET

COFACTOR_MATRIX:
//C00
MOV R3, 64H
MOV R4, 68H
MOV R5, 65H
MOV R6, 67H
ACALL AB_SUB_CD
MOV 70H,R2
//C01
MOV R3, 65H
MOV R4, 66H
MOV R5, 63H
MOV R6, 68H
ACALL AB_SUB_CD
MOV 71H,R2
//C02
MOV R3, 63H
MOV R4, 67H
MOV R5, 64H
MOV R6, 66H
ACALL AB_SUB_CD
MOV 72H,R2


//C10
MOV R3, 62H
MOV R4, 67H
MOV R5, 61H
MOV R6, 68H
ACALL AB_SUB_CD
MOV 73H,R2
//C11
MOV R3, 60H
MOV R4, 68H
MOV R5, 62H
MOV R6, 66H
ACALL AB_SUB_CD
MOV 74H,R2
//C12
MOV R3, 61H
MOV R4, 66H
MOV R5, 60H
MOV R6, 67H
ACALL AB_SUB_CD
MOV 75H,R2



//C20
MOV R3, 61H
MOV R4, 65H
MOV R5, 64H
MOV R6, 62H
ACALL AB_SUB_CD
MOV 76H,R2
//C21
MOV R3, 63H
MOV R4, 62H
MOV R5, 60H
MOV R6, 65H
ACALL AB_SUB_CD
MOV 77H,R2
//C22
MOV R3, 60H
MOV R4, 64H
MOV R5, 61H
MOV R6, 63H
ACALL AB_SUB_CD
MOV 78H,R2


RET

ADJ_FROM_CO:
MOV A,70H
MOV B,69H
DIV AB
MOV 70H,A

MOV A,74H
MOV B,69H
DIV AB
MOV 74H,A

MOV A,78H
MOV B,69H
DIV AB
MOV 78H,A

MOV A,71H
MOV B,69H
DIV AB
MOV R2,A
MOV A,73H
MOV B,69H
DIV AB
MOV 71H,A
MOV 73H,R2

MOV A,72H
MOV B,69H
DIV AB
MOV R2,A
MOV A,76H
MOV B,69H
DIV AB
MOV 72H,A
MOV 76H,R2

MOV A,75H
MOV B,69H
DIV AB
MOV R2,A
MOV A,77H
MOV B,69H
DIV AB
MOV 75H,A
MOV 77H,R2


RET

END


