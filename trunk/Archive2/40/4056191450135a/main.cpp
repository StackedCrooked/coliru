int wrap(int(*asmfn)(int,int,int,int), int param1, int param2, int param3, int param4) {
    int x;
    asm (
R"(
push %1;
push %5;
push %4;
pushl %3;
push %2;
call *%1;
pop %2;
pop %3;
pop %4;
pop %5;
pop %1;
mov %%eax, %0;
)"

          : "=X" (x)
          : "c" (asmfn), "d" (param1), "b" (param2), "S" (param3), "D" (param4)
          : "cc", "memory", "%eax" );
    return x;
}
