#include <stdlib.h> // Required for malloc()
#include <stdio.h> // Required for printf()

#define STRINGMAXSIZE 10000000 // I meant reasonable max size
#define WORDMAXSIZE 1000

char* SumCharsAndDigits(const char*);
void PrintWordsSorted(const char * str);

int main()
{
    char str [30] = "mon code est cool !??";
    char* result = SumCharsAndDigits(str);
        if ( result == NULL )   return -1;
        //printf("%s",result);
    
    PrintWordsSorted(str);
    
    return 0;
}

unsigned int charToValue(char c) // Easier to do another little function
{
    if (48 <= c && c <= 57) // 0123456789
        return (unsigned int) c - 48; // '0' = 48 -> 0 etc
    else if ( 65 <= c && c <= 90) //ABCDEFGHIJKLMNOPQRSTUVWXYZ
        return (unsigned int) c - 64; // 'A' = 65 -> 1 etc
    else if ( 97 <= c && c <= 122) //abcdefghijklmnopqrstuvwxyz
        return (unsigned int) c - 96; // 'a' = 97 -> 1 etc
    else return 0;
}

char* SumCharsAndDigits(const char* str) // First exercise
{
    if (str == NULL)
        return NULL;
        
    unsigned int i,j = 0;
    unsigned int l = 0;
    
    // check string length
    for ( i = 0 ; i < STRINGMAXSIZE ; i++)
    {   if ( *(str+i) == '\0' )
        {   l = i;
            break;
        }
    }
    
    if ( l == 0 ) return NULL;
    
    unsigned int sum = 0;
    char current = '\0';
    
    for ( i = 0 ; i < l ; i++ )
    {   current = *(str+i);
        sum += charToValue(current);
    }
    
    unsigned int outputSize = 0;
    unsigned int sumCopy = sum;
    
    while ( sumCopy != 0 )
    {   sumCopy /= 10;
        outputSize++;
    }
    
    char* finalString = (char *) malloc ( outputSize + 1 ); // + 1 for the '\0'
        if (finalString == NULL) return NULL;

    // Now we have to convert our sum into a string
    unsigned int digit = 0;
    for ( i = 0 ; i < outputSize ; i++ )
    {   digit = sum;
        for ( j = i ; j < outputSize - 1 ; j++ )    digit /= 10;
        digit = digit % 10;
        *(finalString + i ) = 48+digit;
    }
    *(finalString + outputSize ) = '\0';
    return finalString;
}







unsigned int SumCharsAndDigits2(const char* str) // USEFULL for second ex
{
    if (str == NULL)
        return 0;
        
    unsigned int i = 0;
    unsigned int l = 0;
    
    // check string length
    for ( i = 0 ; i < STRINGMAXSIZE ; i++)
    {   if ( *(str+i) == '\0' )
        {   l = i;
            break;
        }
    }
    
    if ( l == 0 ) return 0;
    
    unsigned int sum = 0;
    char current = '\0';
    
    for ( i = 0 ; i < l ; i++ )
    {   current = *(str+i);
        sum += charToValue(current);
    }
    return sum;
}







void PrintWordsSorted(const char * str)
{
    if (str == NULL)
        return;
    unsigned int nWord = 1;
    unsigned int l = 0;
    unsigned int i,j = 0;
    
    for ( i = 0 ; i < STRINGMAXSIZE ; i++)
    {   if ( *(str+i) == '\0' )
        {   l = i;
            break;
        }
        else if ( *(str+i) == ' ' )
        {   nWord++;
        }
    }
    
    unsigned int * scores = (unsigned int*) malloc ( nWord );
    char ** substr = (char **) malloc ( nWord );
    unsigned int actualWord = 0;
    unsigned int actualWordLength = 0;
    unsigned int startingWord = 0;
    
    for ( i = 0 ; i < l + 1 ; i++)
    {   if ( *(str+i) == ' ')
        {   actualWordLength = i - startingWord;
            *(substr+actualWord) = (char*) malloc ( actualWordLength + 1 );
            for ( j = 0 ; j < actualWordLength ; j++ ) // Recopy
            {   *(*(substr+actualWord)+j) = *(str+startingWord+j);
            }
            *(*(substr+actualWord)+actualWordLength) = '\0';
            printf("%s %d\n",*(substr+actualWord),(substr+actualWord));
            *(scores+actualWord) = SumCharsAndDigits2(*(substr+actualWord));
            actualWord++;
            startingWord = i+1;
            printf("%s + %d\n",*(substr),(substr));
        }
    }
    
    
    for ( i = 0 ; i < nWord ; i++)
    {   unsigned int best = 4000000000;
        unsigned int besti = 0;
        for ( j = 0 ; j < nWord ; j++)
        {   if ( *(scores+j) < best )
            {   besti = j;
                best = *(scores+j);
            }
        }
        printf("\n%d: %s  %d  %d",*(scores+besti),*(substr+besti),besti,(substr+besti));
        *(scores+besti) = 4000000001;
    }
    
    
}

