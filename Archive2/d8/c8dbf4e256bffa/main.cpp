#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
void* maFonction(void* data);
void* maFonction1(void* data);
void* maFonction2(void* data);

int main()
{
    int i; 
    	//On crée un thread 
		pthread_t thread;
          pthread_t thread1;
          
        pthread_t thread2;
		//permet d'exécuter la fonction maFontion en parallèle
	
        pthread_create(&thread,NULL,maFonction , NULL);
	    //AFFICHE 50 FOIS 1 
        for(i=0;i<50 ;i++)
        printf(" 1 ");
          
        pthread_create(&thread1,NULL,maFonction1, NULL);   
        pthread_create(&thread2,NULL,maFonction2, NULL);   
    	//Attend la fin du thread créé  
    	pthread_join(thread,NULL);
            pthread_join(thread1,NULL);
                pthread_join(thread2,NULL);
                
   
        return 0;

}

void* maFonction(void* data)
{
    int i;
    //Affiche 50 fois 2
    printf("\n");
    for(i=0 ; i<50 ;i++)
        
    printf(" 2 ");
    return NULL;
}

void* maFonction1(void* data)
{
    int i;
    //Affiche 50 fois 2
    printf("\n");
    for(i=0 ; i<50 ;i++)
        
    printf(" 3 ");
    return NULL;
}

void* maFonction2(void* data)
{
    int i;
    //Affiche 50 fois 2
    printf("\n");
    for(i=0 ; i<50 ;i++)
    printf(" 4 ");
    return NULL;
}