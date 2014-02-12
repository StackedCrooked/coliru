#include <ctime>
#include <iostream>
#include <locale>
#include <stdio.h>
 
int main()
{
    struct tm tm_obj;
    strptime("2014-01-01T00:00:00", "%Y-%m-%dT%H:%M:%S", &tm_obj);
    
    printf("strptime year: %d\n", tm_obj.tm_year);
    printf("month: %d\n", tm_obj.tm_mon);
    printf("day: %d\n", tm_obj.tm_mday);
    printf("hour: %d\n", tm_obj.tm_hour);
    printf("min: %d\n", tm_obj.tm_min);
    printf("sec: %d\n", tm_obj.tm_sec);

    
    char *fout = new char[14];

    strftime(fout, 10, "%D - %T %s", &tm_obj);
    printf("\n%d here's the output:[%s]\n",__LINE__, fout);
    
    strftime(fout, 10, "%B", &tm_obj);
    printf("\n%d here's the output:[%s]\n",__LINE__, fout);
    
}