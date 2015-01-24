#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    double x = 5;
    double y = 6;
    double a = exp(3 * x) * exp(4 * y);

    printf("%f\n", a);
    return 0;
}




        .file   "test.cpp"
        .intel_syntax noprefix
        .def    __main; .scl    2;      .type   32;     .endef
        .section .rdata,"dr"
.LC1:
        .ascii "%f\12\0"
        .section        .text.startup,"x"
        .p2align 4,,15
        .globl  main
        .def    main;   .scl    2;      .type   32;     .endef
        .seh_proc       main
main:
.LFB7:
        sub     rsp, 56
        .seh_stackalloc 56
        .seh_endprologue
        call    __main
        movabs  rdx, 4860292485831894297
        lea     rcx, .LC1[rip]
        mov     QWORD PTR 40[rsp], rdx
        movsd   xmm1, QWORD PTR 40[rsp]
        call    printf
        xor     eax, eax
        add     rsp, 56
        ret
        .seh_endproc
        .ident  "GCC: (GNU) 4.8.3"
        .def    printf; .scl    2;      .type   32;     .endef