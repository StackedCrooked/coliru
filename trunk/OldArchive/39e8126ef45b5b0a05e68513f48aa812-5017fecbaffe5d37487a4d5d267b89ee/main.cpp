#include <stdio.h>

/*
http://ja.wikipedia.org/wiki/CPUID
*/

int main(void) {
    char venderID[16]={0};
	char processorBland[64]={0};
	char* pVenderID=&venderID[0];
	char* pProcessorBland=&processorBland[0];
	__asm__ volatile (
		"movl %0,%%esi\n\t"
		"movl %1,%%edi\n\t"

		"movl $0,%%eax\n\t"
		"cpuid\n\t"
		"movl %%ebx,(%%esi)\n\t"
		"movl %%edx,4(%%esi)\n\t"
		"movl %%ecx,8(%%esi)\n\t"

		"movl $0x80000000,%%eax\n\t"
		"cpuid\n\t"
		"cmp $0x80000004,%%eax\n\t"
		"jle nobland\n\t"
		"movl $0x80000002,%%eax\n\t"
		"cpuid\n\t"
		"movl %%eax,(%%edi)\n\t"
		"movl %%ebx,4(%%edi)\n\t"
		"movl %%ecx,8(%%edi)\n\t"
		"movl %%edx,12(%%edi)\n\t"
		"movl $0x80000003,%%eax\n\t"
		"cpuid\n\t"
		"movl %%eax,16(%%edi)\n\t"
		"movl %%ebx,20(%%edi)\n\t"
		"movl %%ecx,24(%%edi)\n\t"
		"movl %%edx,28(%%edi)\n\t"
		"movl $0x80000004,%%eax\n\t"
		"cpuid\n\t"
		"movl %%eax,32(%%edi)\n\t"
		"movl %%ebx,36(%%edi)\n\t"
		"movl %%ecx,40(%%edi)\n\t"
		"movl %%edx,44(%%edi)\n\t"
		"nobland:\n\t"
	: /* output register : NIL */
	: "m" (pVenderID), "m" (pProcessorBland)
	: "%eax","%ebx","%ecx","%edx");
	printf("Vender    ID    : %s\n",venderID);
	printf("Processor Bland : %s\n",processorBland);
	return 0;
}