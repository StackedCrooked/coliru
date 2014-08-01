#include <iostream>
int main()
{
    int n = 7;
    // extended inline assembly
    asm ("leal (%0,%0,4),%0"
         : "=r" (n)
         : "0" (n));
    std::cout << "7*5 = " << n << '\n';
 
    // standard inline assembly
    asm ("movq $60, %rax\n\t" // the exit syscall number on Linux
         "movq $2,  %rdi\n\t" // this program returns 2
         "syscall");
}