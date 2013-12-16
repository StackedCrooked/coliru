#include <pthread.h>  
#include <stdio.h>  // printf 
#include <unistd.h> // sleep
#include <iostream> 

#define ACT_POS              printf("\033[6n")
#define UP_LINE              printf("\033[A")
#define ONE_POS_RIGHT        printf("\033[C")
#define RIGHT(Anz)           printf("\033[%dC",Anz)
#define RESTORE_POS          printf("\033[u")
#define STORE_POS            printf("\033[s")
#define POSITION(Ze, Sp)     printf("\033[%d;%dH",Ze,Sp)


pthread_mutex_t outMutex;
pthread_t threadup, threaddown, threadpoint;

void* thread_functionPoint(void*) {

    for (int i=0;i<50;++i)
    {
        pthread_mutex_lock(&outMutex); // Sperre einrichten
    RESTORE_POS;
	UP_LINE;
	UP_LINE;
        UP_LINE;
        int anz = i+1;
        RIGHT(anz);
	if (i == 49) 
	   std::cout << "Ende" << std::endl<< std::endl << std::endl;
	else
	   std::cout << "." << std::endl<< std::endl << std::endl;
	pthread_mutex_unlock(&outMutex); // Sperre aufheben
	usleep(40000);
    }
    return 0; 
}


void* thread_functionUp(void*) { 

    for (int i=0;i<200;++i)
    {
	pthread_mutex_lock(&outMutex); // Sperre einrichten
	RESTORE_POS;
	UP_LINE;
	std::cout << i << std::endl;
	pthread_mutex_unlock(&outMutex); // Sperre aufheben
	usleep(10000);
	
    }
    return 0;
}

void* thread_functionDown(void*) { 
	
    for (int i=0;i<200;++i)
    {
	pthread_mutex_lock(&outMutex); // Sperre einrichten
	RESTORE_POS;
	UP_LINE;
	UP_LINE;
	std::cout << i << std::endl << std::endl;
	
	pthread_mutex_unlock(&outMutex); // Sperre aufheben
	usleep(50000);
	
    }
    return 0;
}

 int main() {

   std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
   STORE_POS;
   pthread_create( &threadup, NULL, thread_functionUp, NULL );
   pthread_create( &threaddown, NULL, thread_functionDown, NULL );
   pthread_create( &threadpoint, NULL, thread_functionPoint, NULL );
   pthread_join( threadup, NULL );
   pthread_join( threaddown, NULL );
   pthread_join( threadpoint, NULL );
   printf("\nEnde\n"); 
   return 0;

}
