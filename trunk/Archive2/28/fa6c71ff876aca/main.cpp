// call exit(0) on 32-bit x86 Linux
asm("movl $1,%%eax;
     xorl %%ebx,%%ebx;
     int  $0x80"
    );