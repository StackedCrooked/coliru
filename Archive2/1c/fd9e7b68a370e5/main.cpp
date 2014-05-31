#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

//I'm told that volatile tells the compiler not to cache the address of the pointer.
volatile int * volatile i;
void seg_fault_handler(int TrapID)
{
    i = (volatile int *) malloc(sizeof(int));
    puts("seg fault avoided");
}

int main()
{
    signal(SIGSEGV, seg_fault_handler);
    *i += 1;
    return 0;
}