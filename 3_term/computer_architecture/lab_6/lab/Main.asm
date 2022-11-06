	.686
	.model flat, stdcall
	.stack

	.data

	A  REAL4 4.3
	C  REAL4 7
	D  REAL4 1.2
	C1 REAL4 4.0
	C2 REAL4 23.0
	C3 REAL4 4.0
	C4 REAL4 8.4
	C5 REAL4 9.0
	C6 REAL4 13.0

	RES REAL4 ?

	.code

main:
	finit ; init
	fld   C1
	fdiv  A; C1 / A

	fld  C
	fmul A; C * A
	fcos ; cos(C*A)

	fsubp ST(1), ST(0); C1/A - cos(C*A)

	fld   C2
	fmul  C
	fsub  C3
	fsqrt ; sqrt(C2*C - C3)

	faddp ST(1), ST(0); sqrt(C2*C - C3) + C1/A - cos(C*A)

	fld  C4
	fmul C; C4 * C

	fld  D
	fdiv C5; D / C5

	fsubp ST(1), ST(0); C4 * C - D / C5

	fld  C6
	fmul A; C6 * A

	faddp ST(1), ST(0); C4 * C - D / C5 + C6 * A

	fdivp ST(1), ST(0); (sqrt(C2*C - C3) + C1/A - cos(C*A)) / (C4 * C - D / C5 + C6 * A)

	fst RES

	RET
	END main
