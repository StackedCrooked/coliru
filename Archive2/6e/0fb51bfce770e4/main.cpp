#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

static void child_handler(int sig)
{
    pid_t pid;
    int status;
    printf("Child Killmurdered");
    /* EEEEXTEERMINAAATE! */
    while((pid = waitpid(-1, &status, WNOHANG)) > 0)
        ;
}

int main()
{

struct sigaction sa;

sa.sa_handler = child_handler;
sigemptyset(&sa.sa_mask);
sa.sa_flags = 0;
sa.sa_handler = child_handler;

sigaction(SIGCHLD, &sa, NULL);

if(system("uname -a"))
  fprintf(stderr, "system() failed\n");

}