#include <stdio.h>
#include <time.h>
#include <stdlib.h>
 
int main(void)
{
        struct tm *time_inicial;
        struct tm *time_final;
        time_t current_time1;
        time_t current_time2;
        current_time1 = time(NULL);     // Guarda a hora atual
        time_inicial = gmtime(&current_time1);
        printf("Hora atual: %dh%02dmin%02ds\n", (time_inicial->tm_hour-3)%24,time_inicial->tm_min,time_inicial->tm_sec);
        sleep(10);
        printf("LeitSmart antes: Hora inicio: %dh%02dmin%02ds\n", (time_inicial->tm_hour-3)%24,time_inicial->tm_min,time_inicial->tm_sec);
        current_time2 = time(NULL);     // Guarda a hora atual
        printf("LeitSmart depois: Hora inicio: %dh%02dmin%02ds\n", (time_inicial->tm_hour-3)%24,time_inicial->tm_min,time_inicial->tm_sec);
        time_final = gmtime(&current_time2);
        printf("LeitSmart depois do depois: Hora inicio: %dh%02dmin%02ds\n", (time_inicial->tm_hour-3)%24,time_inicial->tm_min,time_inicial->tm_sec);
   
}