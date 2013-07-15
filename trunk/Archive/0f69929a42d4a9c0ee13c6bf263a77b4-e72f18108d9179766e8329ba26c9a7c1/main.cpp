#include <stdio.h>
#include <stdlib.h>

#define sqr2(x) ((x)*(x))
#define frand() ((double) rand() / (RAND_MAX))
#define MAXLEN 1000


int circumscribed(int radius){
    float xcoord = frand();
    float ycoord = frand(); 
    float coord = sqr2(xcoord) + sqr2(ycoord);

    if(coord <= radius)
        return 1;
    return -1;      
}

int main()
{
    int i;
    int circles = 0, rect = 0;;
    for(i = 0; i < MAXLEN; i++)
    {
        if(circumscribed(1) > 0)   // if(circumscribed(1)) shoul be enough but it doesn't work. Very odd in my opinion.
            circles++;
        rect++;  //this is equal to MAXLEN, I just used it for debugging
    }

    float PI = 4.0 * circles / rect;
    printf("PI is %2.4f: \n", PI);
    return 0;   
}