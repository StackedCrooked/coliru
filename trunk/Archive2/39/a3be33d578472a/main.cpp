#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{    
    int fd[2], nbytes, status;
    pid_t pid1, pid2;

    pipe(fd);
    
    pid1 = fork();
    
    switch(pid1){
        case 0:  
        dup2(fd[1], 1);
        
        close(fd[1]);      
        char* command[] = {"cat", "input.txt", 0};
        close(fd[0]);
        
        execvp(command[0], command);
        exit(EXIT_FAILURE);
        break;
        
        case -1:
        perror("fork");
        exit(EXIT_FAILURE);
        break;
    }
    
    pid2 = fork();
    
    switch(pid2){
        case 0:  
        dup2(fd[0], 0);
        close(fd[0]);  
        close(fd[1]);
        
        char* command[] = {"grep", "1", 0};
        
        execvp(command[0], command);
        exit(EXIT_FAILURE);
        break;
        
        case -1:
        perror("fork");
        exit(EXIT_FAILURE);
        break;
        
        default:
        break;
    }
    close(fd[0]);
    close(fd[1]);
    
    waitpid(pid1, NULL, 0);
    waitpid(pid2, &status, 0);
    exit(status);    

    return 0;
}