#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char Serial[11];
char Original[11];

char CHARS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
int nCHARS = 0;


unsigned long ulKeysTried = 0;
unsigned long ulKeysFound = 0;

void Gen(char * Serial)
{
    ulKeysTried++;

    for(int i = 0; i < 2; i++)
    {
        *(unsigned int*)(Serial + i * 4) ^= 0x1234567;
        *(unsigned char*)(Serial + i * 4) &= 0xE;
    }

    unsigned char Val1 = *(unsigned char*)(Serial + 8);
    for(int i = 0; i < 10; i++)
    {
        Val1 += *(unsigned char*)(Serial + i);
        *(unsigned char*)(Serial+8) = Val1;
    }

    for(int i = 0; i < 2; i++)
    {
        *(unsigned int*)(Serial+i*4) ^= 0x89ABCDE;
        *(unsigned char*)(Serial+i*4) &= 0xE;
    }

    unsigned char Val2 = *(unsigned char*)(Serial+9);
    for(int i = 0; i < 10; i++)
    {
        Val2 += *(unsigned char*)(Serial + i);
        *(unsigned char*)(Serial+9) = Val2;
    }
    return;
}

int main()
{
    srand(time(NULL));
    nCHARS = strlen(CHARS);

    while(1)
    {
        for(int n = 0; n < 10; n++)
        {
            Serial[n] = CHARS[rand()%(nCHARS-1)];

            Original[n] = Serial[n];
        }

        Gen(Serial);
        if(Serial[8] == 66 && Serial[9] == -34)
        {
            Original[10] = '\0';
            printf("Found: %s\nTried %lu keys so far.\n", Original, ulKeysTried);
            ulKeysFound++;
            if(ulKeysFound > 10)
                return 1;
        }
    }

    return 0;
}
