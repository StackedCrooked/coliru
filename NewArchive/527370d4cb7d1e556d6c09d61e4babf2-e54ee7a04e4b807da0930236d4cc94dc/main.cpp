#include <iostream>


__asm__ (R"foo(
.globl checksum16
.type checksum16,@function
.align 16
checksum16:
    xor %eax, %eax
    test $7, %edi
    jne 7f
0:  mov %esi, %ecx
    shr $6, %ecx
    je 2f
    clc

.align 16
1:  adc 0(%rdi), %rax
    adc 8(%rdi), %rax
    adc 16(%rdi), %rax
    adc 24(%rdi), %rax
    adc 32(%rdi), %rax
    adc 40(%rdi), %rax
    adc 48(%rdi), %rax
    adc 56(%rdi), %rax
    lea 64(%rdi), %rdi
    dec %ecx
    jne 1b
    
    adc $0, %rax
    
2:  mov %esi, %ecx
    shr $3, %ecx
    and $7, %ecx  # Also clears the carry flag
    je 4f

3:  adc (%rdi), %rax
    lea 8(%rdi), %rdi
    dec %ecx
    jne 3b

4:  adc $0, %rax
    and $7, %esi
    jne  6f # Some odd bytes to do
    
    # Fold down to 16 bits
5:  mov %eax, %edx
    shr $32, %rax
    add %edx, %eax
    adc $0, %eax
    mov %eax, %edx
    shr $16, %eax
    add %dx, %ax
    adc $0, %ax

    not %ax
    retq

    # Add in last bytes
6:  lea (,%esi,8),%ecx
    mov $-1, %rdx
    neg %ecx
    shr %cl, %rdx
    and (%rdi), %rdx
    add %rdx, %rax
    adc $0, %rax
    jmp 5b

7:  test $1, %edi
    jne 11f # Odd-aligned is annoying
    
    mov %edi, %ecx
    neg %ecx
    and $0x7, %ecx
    
    cmp %ecx, %esi
    cmovl %esi, %ecx  # Work to do is min(size, alignment)
    sub %ecx, %esi
        
    test $4, %ecx
    je  8f
    movl (%rdi), %edx
    add %rdx, %rax
    adc $0, %rax
    add $4, %rdi

8:  test $2, %ecx
    je 9f
    movzwq (%rdi), %rdx
    add %rdx, %rax
    adc $0, %rax
    add $2, %rdi

9:  test $1, %ecx
    je 10f
    movzbq (%rdi), %rdx
    add %rdx, %rax
    adc $0, %rax
    add $1, %rdi

10: test %esi, %esi # Nothing left to do?
    je 5b
    
    # Continue with the rest
    jmp 0b

11: movzbw (%rdi), %r8w
    inc %rdi
    dec %esi
    je 12f # Only one byte to do?
    call checksum16
    not %ax
    xchg %al, %ah
    add %r8w, %ax
    adc $0, %ax
    not %ax
    retq

12: mov %r8w, %ax
    not %ax
    retq
.size checksum16, .-checksum16
)foo");


extern "C" unsigned short checksum16(const unsigned char*, int);


int main()
{
    const unsigned char data[] = { 0x01, 0x02, 0x03, 0x04, 0x05 };
    std::cout << checksum16(data, sizeof(data));
}
