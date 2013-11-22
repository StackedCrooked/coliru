#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char DELIMS[] = "\t ";
#define MAX_LENGTH 100

int main ()
{
    char buf[]="ls -ltr /";
    int status = 0;
    char *argv[MAX_LENGTH];
    int j=0;
    pid_t pid;
    argv[j++] = strtok (buf, DELIMS);
    while (j<MAX_LENGTH && (argv[j++]=strtok(NULL," "))!=NULL);

    pid = fork();
    if(pid < 0) {
       printf("Error occured");
       exit(-1);
    } else if(pid == 0) {
         execvp(argv[0],argv);
    } else if( pid > 0) {
         wait(& status);
    }
}
