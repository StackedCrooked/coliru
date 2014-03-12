#include <stdio.h>
#include <time.h>
#include <math.h>
#define g 9.81
 
int main()
{
    time_t now;
    time_t start;
    int i = 0;
    double height = 500.0;
    double seconds = 0.0;
    double timeBoom = sqrt(2 * height / g);
    time(&start);    
    while (seconds < timeBoom) {
    if (seconds >= i) {
    printf("%.0fs %.1fm\n", seconds, height - g * (seconds * seconds) / 2);
    i++;
    }
    seconds = difftime(time(&now), start);
    }
    printf("%.3fs BOOM!!!\n", timeBoom);
    return 0;
}