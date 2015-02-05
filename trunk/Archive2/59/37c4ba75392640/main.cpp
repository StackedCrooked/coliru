#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    printf("Shell> \n"); fflush(stdout);
    
    pid_t pid1 = fork();
    if(pid1 < 0) {
        perror("fork failed\n");
    }
    
    if(pid1 > 0) {      // Parent
        waitpid(pid1, NULL, 0);
        printf("\t\t------PID1 Complete-------\n\n");                   
    } else {              // Child
        printf("ON CHILD\n"); fflush(stdout);

        int fd[2];
        if(pipe(fd) < 0) {
            perror("Problem with pipe\n");
            return 1;
        }   

        pid_t pid2 = fork();
        if(pid2 < 0) {
            perror("fork failed\n");
        }

        if(pid2 > 0) {  // Child -> Parent
            printf("ON CHILD-Parent\n"); fflush(stdout);
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            execlp("sort", "sort", "-r", NULL);
            perror("Problem with execlp\n");
            return 1;
        } else {          // Child -> Child
            printf("ON CHILD->Child\n"); fflush(stdout);
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);
            execlp("ls", "ls", "-a", NULL);
            perror("Problem with execvp\n");
            return 1;
        }
    }
    
    printf("\nEnd of program.\n");
}
