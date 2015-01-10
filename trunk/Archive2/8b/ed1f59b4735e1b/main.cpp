//Interprocess communication 
//pipes are used for inter-process communication here
//unnamed pipes are used for communication bw related processes
//for communication bw unrelated process use named pipe/fifo
#include <stdio.h>
#include <unistd.h>
#include <cstring>

int main()
{
    int fd[2];
    pipe(fd);
    setbuf(stdout, NULL);
    
    int ch_id = fork();
    if(ch_id == 0)
    {
        printf("%d sending \"rahul nangia\" to parent process %d\n", getpid(), getppid());
        close(fd[0]);
        char str[] = "rahul nangia";
        write(fd[1], str, strlen(str) +1);
    }
    else
    {
        close(fd[1]);
        char buffer[80];
        read(fd[0], buffer, 80);
        printf("%d printing %s", getpid(), buffer);
    }
} 