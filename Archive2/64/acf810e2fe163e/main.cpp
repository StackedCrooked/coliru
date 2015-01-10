#include <stdio.h>
#include <unistd.h>

int main()
{
    int ch_id;
    setbuf(stdout, NULL);
    ch_id = fork();
    if(ch_id == 0)
    {
        printf("%d : child process \n", getpid());
        execlp("ls", "ls", NULL);
    }
    else
    {
        printf("%d : parent process \n", getpid());
    }
} 