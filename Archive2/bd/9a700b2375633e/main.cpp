#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>
#include <getopt.h>

#define sampleSize 1

typedef struct
{
    double basicTime;
    double spacialTime;
    double temporalTime;
    double spacialTemporalTime;
} TimeEntry;

int main()
{
     TimeEntry* timeThings;
    int i;
    time_t startTime;
    time_t stopTime;

    //Allocate an array for storing all of the timeThings
    timeThings = (TimeEntry*)malloc(sampleSize * sizeof(TimeEntry));

    for (i = 0; i < sampleSize; i++);
    {

        time(&startTime);
        sleep(1);
        time(&stopTime);
        timeThings[i].basicTime = difftime(stopTime, startTime);

        time(&startTime);
        sleep(1);
        time(&stopTime);
        timeThings[i].spacialTime = difftime(stopTime, startTime);

        time(&startTime);
        sleep(1);
        time(&stopTime);
        timeThings[i].spacialTemporalTime = difftime(stopTime, startTime);

        time(&startTime);
        sleep(1);
        time(&stopTime);
        timeThings[i].temporalTime = difftime(stopTime, startTime);
    }

    free(timeThings);

    return 0;
}