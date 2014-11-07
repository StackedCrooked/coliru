#include <signal.h>
#include <stdio.h> 
#include <time.h> 
int i=1;
void capture (int sig) { 
    printf("Signal recu %d\n", sig); 
    i=0;
} 

int main () {
  signal (SIGINT, capture);
  while (i) { 
	  printf("Hello World!\n"); 
 
	}
}

