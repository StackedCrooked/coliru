#include <stdio.h>
#include <stdlib.h>

#define isdigit(C) ((C) >= '0' && (C) <= '9')

// Ré-écritures
int strlen(const char* str);
char* strcpy(char* to, const char* from);
char* myItoa(int num, char* str, int base);
// 
char* SumCharsAndDigits(const char* str);
int charvalue(char c);
//
const char* STR_CONST = "azAZ09#";

int main()
{
    //printf(STR_CONST);
    printf(SumCharsAndDigits(STR_CONST));
    return 0;
}

char* SumCharsAndDigits(const char* str)
{
    int len = 0, i = 0, sum = 0;
    char *str_copy = NULL, *result = NULL;
    
    len =  strlen(str);
    str_copy = (char*)malloc(sizeof(char)*(len+1));
    
    strcpy(str_copy, str);
    
    for(i=0;i<len;i++)
    {
        sum += charvalue(str_copy[i]);
    }
    printf("%d\n",sum);
    return myItoa(sum, str_copy, 10);
    
    //return str_copy;
}

int strlen(const char* str)
{
    int len = 0;
    char character = 0;
    do
    {
        character = str[len];
        len++;
    }
    while(character != '\0');

    return len-1;
}

char* strcpy(char* to, const char* from)
{
    int i;
    for (i=0; i <= strlen(from); i++)
        to[i] = from[i];

    to[strlen(from)] = 0;
    return to;
}

int charvalue(char c)
{
    int val = c-'A'+1;
    
    // Digits
    if (val < 0)
    {
        if(val >= -16 && val <= -7) // between '0' and '9' in ASCII
            val += 16;
    }
    // Letters
    if (val > 26)  // after 'Z' in ASCII
    {
        if(val >= 33 && val <= 58) // between 'a' and 'z' in ASCII
        {
            val -= 32;   
        }
    }
    
    if(val < 0 || val > 26) // Other char
        return 0;
        
    
    return val;   
}

char* myItoa(int num, char* str, int base)
{
    int v = num;
    int it;
    int reste;
    int l;

    l = strlen(str);
    it = 1;
    
    reste = v % base;
    str[l - it] = reste + '0';
        
    while ( v > (base-1) ) { 
        it++;
        v = v / 10;
        reste = v % base;
        str[l - it] = reste + '0'; // ?2
    }
    
    return str + l - it;
}