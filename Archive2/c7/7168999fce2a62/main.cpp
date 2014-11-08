#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    char name[100];
    float share;
    int seats;
}faction;

faction Parties(){

/*
 *      Some variables
 */

    faction council[20];

    int percentage = 0;
    int currentFactionCount = 0;
    char currentFactionName[100];
    float currentFactionShare = 0;
    int totalPartiesCount = 0;

/*
 *      Get party names and vote shares
 */

while(percentage<100){
    printf("Geben Sie den Namen der %d. Partei an.\n", currentFactionCount+1);
    fflush(stdout);
    scanf("%s", currentFactionName);

    printf("Geben Sie den Stimmenanteil der %d. Partei an.\n", currentFactionCount+1);
    fflush(stdout);
    scanf("%f", &currentFactionShare);

    strcpy(council[currentFactionCount].name, currentFactionName);
    council[currentFactionCount].share = currentFactionShare;

    currentFactionCount++;
    percentage += currentFactionShare;
}

    totalPartiesCount = currentFactionCount;

/*
 *      New distribution of votes to parties over the 5% threshold
 */

    int totalSeats = 199;
    float totalShare = 0;

/* new percentages of the parties with more than 5% */
for(currentFactionCount = 0;currentFactionCount<totalPartiesCount;currentFactionCount++){
    if(council[currentFactionCount].share>=5.){
        totalShare += council[currentFactionCount].share;
    }
}

/* parties and seats of parties with more than 5% */
for(currentFactionCount = 0;currentFactionCount<totalPartiesCount;currentFactionCount++){
    if(council[currentFactionCount].share>=5.){
        council[currentFactionCount].seats = (int) totalSeats*(council[currentFactionCount].share/totalShare) ;
    }
    else{
        council[currentFactionCount].seats = 0;
    }
}

for(currentFactionCount = 0;currentFactionCount<totalPartiesCount;currentFactionCount++){
    printf("Parteiname: %s \n", council[currentFactionCount].name);
    printf("Stimmanteil: %f \n", council[currentFactionCount].share);
    printf("Sitze: %d \n", council[currentFactionCount].seats);
    printf("\n");
}

return council[20];
}
