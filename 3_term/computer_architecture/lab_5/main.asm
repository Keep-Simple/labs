.586P 
.MODEL FLAT, STDCALL 
_DATA SEGMENT 
b                        DD -22
ci                       DD 81
m                        DD 7       
n                        DD 6       
matrix                   DD 15, -24, 45, 58, -60, 83
                         DD 12, -17, 22, 27, -37, 42
                         DD 24, -28, -52, 62, -66, 69
                         DD 19, -25, 27, -31, 52, 56
                         DD 14, -75, 16, -39, 29, -35
                         DD 17, -21, 99, -40, 53, 70
                         DD 19, -25, 27, -31, 52, 56
matrixTranposed          DD 42 DUP(0)
tmpCol                   DD 0
scalarMult               DD 0
condCount                DD 0
condSum                  DD 0
_DATA ENDS 

_TEXT SEGMENT 
START:
    lea ESI, matrix ; ESI - source index
	  lea EDI, matrixTranposed ; EDI - destination index
	  mov EBP, m ; outer loop

OUTER_LOOP:
    mov ECX, n ; inner loop 

INNER_LOOP:
    mov EAX, [ESI]
    mov [EDI], EAX
    add ESI, 4 ; move matrix element pointer
    add EDI, 28 ; 7(m)*4(bytes) move pointer to the next cell in column
    dec ECX
    jnz INNER_LOOP;

    add tmpCol, 4 ; move to the next cell in row
    lea EDI, matrixTranposed
    add EDI, tmpCol
    dec EBP
    jnz OUTER_LOOP

SCALAR_PREPARE:
    lea EBX, matrix                                
    add EBX, 120 ; 5*6*4 = 120 (move offset to first element in 6th row)
    mov ECX, n
SCALAR:     
    mov EAX, [EBX]
    imul EAX, [EBX + 24] ; 6*4 = 24 (matching cell of 6th row from 7th row)
    add EBX, 4
    add scalarMult, EAX            
    loop SCALAR

ROW_SUM:
    lea EBX, matrix 
    add EBX, 8 ; 2*4 (first element in 3rd column)
    mov ECX, n
CONDITION:     
    mov EAX, [EBX]
    cmp EAX, b
    jl TRUE ; ai < b
    cmp EAX, ci
    jge TRUE ; ai >= c
    jmp FALSE
TRUE:
    inc condCount
    add condSum, EAX
FALSE:
    add EBX, 6*4 ; move to the next row
    loop CONDITION
RET                                                
_TEXT ENDS 
END START

