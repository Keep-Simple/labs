Stack_Size EQU 0x00000400
     AREA STACK, NOINIT, READWRITE, ALIGN = 3
Stack_Mem SPACE Stack_Size
__initial_sp
     PRESERVE8
     THUMB
     AREA RESET, DATA, READONLY
     EXPORT __Vectors
     EXPORT __Vectors_End
     EXPORT __Vectors_Size
__Vectors DCD __initial_sp  
     DCD Reset_Handler          
     DCD NMI_Handler           
__Vectors_End
__Vectors_Size EQU __Vectors_End - __Vectors
     AREA |.text|, CODE, READONLY
Reset_Handler PROC
     EXPORT Reset_Handler [WEAK]
     ldr R0, =0xE000ED88
     ldr R1, [R0]
     orr R1, R1, #(0xF << 20)
     str R1, [R0]
     dsb
     isb
     IMPORT MyProg
     LDR r0, =MyProg      
     BX r0                          
     ENDP                         
NMI_Handler PROC
     EXPORT NMI_Handler [WEAK]
     B .
     ENDP                          
     ALIGN
     END
