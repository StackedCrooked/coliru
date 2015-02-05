#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("Shell> \n");
    
    pid_t pid1 = fork();
    if(pid1 < 0) {
        perror("fork failed");
    }
    
    if(pid1 > 0) {      // Parent
        int status;
        waitpid(pid1, &status, 0);
        printf("\t\t------PID1 Complete (%d) -------\n\n", status);
    } else {              // Child
        printf("ON CHILD\n");

        int fd[2];
        if(pipe(fd) < 0) {
            perror("pipe failed");
            return 1;
        }   

        pid_t pid2 = fork();
        if(pid2 < 0) {
            perror("fork failed");
        }

        if(pid2 > 0) {  // Child -> Parent
            printf("ON CHILD-Parent\n");
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            execlp("sort", "sort", "-r", NULL);
            perror("Problem with execlp");
            return 1;
        } else {          // Child -> Child
            printf("ON CHILD->Child\n");
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);
            execlp("ls", "ls", "-a", NULL);
            perror("Problem with execvp");
            return 1;
        }
    }
    
    printf("\nEnd of program.\n");
}
