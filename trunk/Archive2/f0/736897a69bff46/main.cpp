#include <stdlib.h>
 #include <stdio.h>
 #include <pthread.h>
 #include <semaphore.h>

 #define RAND_DIVISOR 10000000
 #define TRUE 1
 #define BUFFER_SIZE 5

 sem_t full, empty; /* Les semaphores */
 int buffer[BUFFER_SIZE]; /* Le buffer (tampon) */
 int counter; /* Compteur du buffer */

 pthread_t tid; /* Thread ID*/
 pthread_attr_t attr; /* Attribut de la Thread */


 void initializeData() {

 /* Créer un sémaphore full initialisé à 0 */
 sem_init(&full, 0, 0);

 /* Créer un sémaphore empty initialisé à BUFFER_SIZE */
 sem_init(&empty, 0, BUFFER_SIZE);

 /* Préparer les atributs par défaut pour la thread */
 pthread_attr_init(&attr);

 /* initialisation du compteur */
 counter = 0;
 }



 /* Produire un objet */
 int production(int item) {
 if(counter < BUFFER_SIZE) {
 buffer[counter] = item;
 counter++;
 printf("Producteur %u a produit %d\n", pthread_self(),item);
 }
 else
 printf("Producteur signale une erreur !!\n");
 }



 /* Consommer un objet */
 int consommation(int *item) {
 if(counter > 0) {
 *item = buffer[(counter-1)];
 counter--;
 printf("Consommateur %u a consommé %d\n", pthread_self(),*item);
 }
 else
 printf("Consommateur signale une erreur !!\n");

 }

 /* Thread Producteur */
 void *producer(void *param) {
 int item;
 while(TRUE) {
 /* dormir un temps aléatoire */
 int rNum = rand() / RAND_DIVISOR;
 usleep(rNum);
 
 /* generer un objet (nombre aléatoire) */
/* /home/loic/enseignement/temps…urce/producer_consumer_sujet.c Page 2 of 2
*/
item = rand();

 sem_wait(&empty);

 production(item);

sem_post(&full);
 }
 }



 /* Thread Consommateur */
 void *consumer(void *param) {
 int item;

 while(TRUE) {
 /* dormir un temps aléatoire */
 int rNum = rand() / RAND_DIVISOR;
 usleep(rNum);

 sem_wait(&full);

 consommation(&item);

 sem_post(&empty);
 }
 }




 int main(int argc, char *argv[]) {

 int i;

 /* Verifier que le nombre d'arguments passé au programme est correct */
 if(argc != 4) {
 fprintf(stderr, "USAGE:./producer_consumer <ARG1> <ARG2> <ARG3>\n");
 }
 /*Lire les arguments dans argv[] Note: argv[0] contient le nom du programme lui-même*/
 int mainSleepTime = atoi(argv[1]); /* Temps en microseconde pour le sommeil du main */
 int numProd = atoi(argv[2]); /* Nombre de threads producteurs */
 int numCons = atoi(argv[3]); /* Nombre de threads consommateurs */

 /* Initialisation */
 initializeData();

 for(i = 0; i < numProd; i++) {
 pthread_create(&tid,&attr,producer,NULL);
 }

 for(i = 0; i < numCons; i++) {
 pthread_create(&tid,&attr,consumer,NULL);
 }

 usleep(mainSleepTime);

 printf("Fin du programme\n");
 exit(0);
 }