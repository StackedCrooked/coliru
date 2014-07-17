#include <stdio.h>
#include <signal.h>
 
/* A user-defined signal handler can process one or more signals. */
static void signal_handler(int signo)
{
    switch(signo)
    {
        case SIGABRT : puts("Process SIGABRT signal here."); break;
        case SIGFPE  : puts("Process SIGFPE  signal here."); break;
        case SIGILL  : puts("Process SIGILL  signal here."); break;
        case SIGINT  : puts("Process SIGINT  signal here."); break;
        case SIGSEGV : puts("Process SIGSEGV signal here."); break;
        case SIGTERM : puts("Process SIGTERM signal here."); break;
    }
 
    /* some cleanup here */
    /* exit(signo);      */
}
 
int main(void)
{
    /* Register a user-defined signal handler. */
    signal(SIGABRT, signal_handler);
    signal(SIGFPE,  signal_handler);
    signal(SIGILL,  signal_handler);
    signal(SIGINT,  signal_handler);
    signal(SIGSEGV, signal_handler);
    signal(SIGTERM, signal_handler);
 
    /* Raise a signal. */
    raise(SIGABRT);
    raise(SIGFPE);
    raise(SIGILL);
    raise(SIGINT);
    raise(SIGSEGV);
    raise(SIGTERM);
 
    return 0;
}