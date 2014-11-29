#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#include <signal.h>
#include <syslog.h>

bool bBreakJob = false;

void sig_handler(int sig)
{
    switch(sig)
    {
    case SIGHUP:
        //rneed to reload config
        break;
    case SIGINT:
        printf("SIGINT \n");
        bBreakJob = true;
        openlog("mydaemon", LOG_PID | LOG_CONS, LOG_DAEMON);
        syslog(LOG_INFO, "Catched SIGINT");
        closelog();
        break;
    case SIGQUIT:
        printf("SIGQUIT \n");
        openlog("mydaemon", LOG_PID | LOG_CONS, LOG_DAEMON);
        syslog(LOG_INFO, "Catched SIGQUIT");
        bBreakJob = true;
        break;
    case SIGPIPE:
        printf("SIGPIPE \n");
        break;
    }
}

int main(int argc, char** argv)
{
    struct sigaction act, oact;
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGHUP);
    sigaddset(&set, SIGPIPE);
    sigaddset(&set, SIGQUIT);
    sigprocmask(SIG_UNBLOCK, &set, NULL);
    act.sa_mask = set;
    act.sa_handler = sig_handler;
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGHUP, &act, NULL);
    sigaction(SIGPIPE, &act, NULL);
    sigaction(SIGQUIT, &act, NULL);

    int fds[0], res, fmax;
    fd_set wset;
    fd_set rset;

    //next line code to open socket 
    int listen_socket = socket(AF_INET, SOCK_STREAM, 0); 
    int iFlags = fcntl(listen_socket, F_GETFL);
    iFlags |= O_NONBLOCK;
    fcntl(listen_socket, F_SETFL, iFlags);
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(4000);
    bind(listen_socket, (struct sockaddr *)&sin, sizeof(sin));
    listen(listen_socket, 20);

    fds[0] = listen_socket;
    FD_ZERO(&wset);
    FD_SET(fds[0], &wset);
    fmax = fds[0] + 1;
    while (FD_ISSET(fds[0], &wset))
    {
        rset = wset;
        res = select(fmax, &rset, NULL, NULL, NULL);
        if (res < 0)
        {
            if (errno == EINTR)
            {   //debug message  
                printf("Loop broken by select's result EINTR");
                break;
            } else
            {
                printf("select(...) fails in listed loop. errno %d (%s)", errno, strerror(errno));
                exit(1);
            }

        }
        else if (res == 0)
        {
          //if timeout is handled
        }
        else if (res > 0)
        {
            if (FD_ISSET(fds[0], &rset))
            {
                //Handle socket input 
            }
        }
        if(bBreakJob)
        {
          printf("Loop broken by signal handler");
          break; 
        }
    } //while( 1 );
    FD_CLR(fds[0], &wset);
    if(bBreakJob)
    { //debug message 
      printf("signal SIGINT is handled ");
    }

}