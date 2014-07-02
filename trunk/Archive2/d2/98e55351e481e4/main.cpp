#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
int main(void)
{
    const char *robikawe;
    int n;
    srand(time(NULL)); 
    n = rand();
    switch (n % 4)
    {
        case 0: robikawe = "Kuba";
        case 1: robikawe = "Pawel";
        case 2: robikawe = "Jacek";
        case 3: robikawe = "Krzysiu";
    }
    printf("Robi kawe: %s !!!\n", robikawe);
    return 0;
}