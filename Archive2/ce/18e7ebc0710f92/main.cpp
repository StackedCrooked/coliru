#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int g = 0;
int main()
{
    int var = 0;
    pid_t pid;
    while (++var < 7)
        if ((pid = fork()) < 0) {
            perror("fork error");
            exit(1);
        } else if (pid == 0) {
            var+=2;
        } else {
            g++;
            var++;
            if (waitpid(pid, NULL, 0) != pid) {
                perror("waitpid error");
                exit(1);
            }
       }
       printf("mypid = %d parentpid = %d var = %d g = %d\n",
              getpid(), getppid(), var, g);
       exit(0);
}
