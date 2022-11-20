	AREA myCode, CODE, READONLY
MyProg
	EXPORT MyProg

	LDR r0, =a
	VLDM r0, {s0-s2}  ; s0=a, s1=c, s2=d
	
	LDR r0, =n1
	VLDM r0, {s7-s11}  ; n1, n2 ... n5

	VMUL.F32 s3, s0, s1
	VCMP.F32 s2, s3
	VMRS APSR_nzcv, FPSCR ; load cmp resulting flags to cpu register
	BGE FIRST      ; d >= a*c
	BLT SECOND      ; d < a*c

FIRST
  VMUL.F32 s3, s7, s1 ; 5.8*c

  VMOV.F32 s4, #17.0
  VMUL.F32 s4, s4, s2 ; 17*d
  VADD.F32 s4, s9
  VSQRT.F32 s4, s4 ; sqrt(9.9 + 17*d)

  VMUL.F32 s5, s1, s0 ; c*a

  VSUB.F32 s3, s4
  VSUB.F32 s3, s5 ; 5.8 * c - sqrt(9.9 + 17 * d) - c * a;

  LDR r0, =y      
  VSTM r0, {s3}
  B STOP

SECOND
  VMUL.F32 s3, s8, s0 ; 9.8*a

  VDIV.F32 s4, s1, s10 ; c/4.3

  VMUL.F32 s5, s2, s11 ; 8.4*d

  VSUB.F32 s3, s4
  VADD.F32 s3, s5

	VABS.F32 s3, s3
	VSQRT.F32 s3, s3
	
  LDR r0, =y      
  VSTM r0, {s3}
  B STOP

STOP B STOP

a   DCFS 7.3
c   DCFS 6.3
d   DCFS 5.4

n1  DCFS 5.8
n2  DCFS 9.8
n3  DCFS 9.9
n4  DCFS 4.3
n5  DCFS 8.4


ALIGN
	AREA MyData, DATA, ReadWrite
y   DCFS 0.0
	END

