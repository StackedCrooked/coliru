#include <stdio.h>
//#include "print.h"
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

pid_t pid;

void go(int signo)
{
      kill(getppid(),SIGUSR1);
}
void move(int signo){
      printf("司机说:move to next station!\n");
}
void stop(int signo){
      
      kill(getppid(),SIGUSR2);
}

void stop_bus(int signo){
      printf("司机说:stop the bus!\n");
}

void arrive(int signo){
      kill(pid,SIGUSR1);      
}

void get_station(int signo){
      printf("售票员说:all get off the bus!\n");
}

int main(int argc,char *argv[])
{

      if( (pid = fork()) < 0){
        perror("fork");
	    exit(1);
      }else if(pid > 0){ //司机
	    printf("parent pid is %d\n",getpid());
	    signal(SIGINT,SIG_IGN);
	    signal(SIGQUIT,SIG_IGN);
	    signal(SIGUSR1,move);
	    signal(SIGUSR2,stop_bus);
	    signal(SIGTSTP,arrive);
	    while(1)
		  pause();
      }else{//售票员
	    printf("child pid is %d\n",getpid());
	    signal(SIGTSTP,SIG_IGN);
	    signal(SIGINT,go);
	    signal(SIGQUIT,stop);
	    signal(SIGUSR1,get_station);
	    while(1)
		  pause();

      }
      return 0;
}
