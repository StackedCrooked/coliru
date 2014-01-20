#include <stdio.h>
#include <string.h>

int my_find_sub_str( 
    const char * a_pcStr, // string to search in
    const char * a_pcSubStr // sub string to search for
)
{
    int iLen1 = strlen( a_pcStr);
    int iLen2 = strlen( a_pcSubStr);
    int iMaxPos = (iLen1 - iLen2);
    if (iMaxPos < 0)
        return -1;
    const char * pc;
    int iPos;
    for (iPos = 0, pc = a_pcStr; iPos < iMaxPos && memcmp( pc, a_pcSubStr, iLen2); iPos++, pc++);
    if (iPos <= iMaxPos)
        return iPos;
    else
        return -1;
}

int stdlib_find_sub_str( 
    const char * a_pcStr, // string to search in
    const char * a_pcSubStr // sub string to search for
)
{
    const char * pc = strstr( a_pcStr, a_pcSubStr);
    if (pc)
        return (pc - a_pcStr);
    else
        return -1;
}

int main()
{
    static char szStr [] = "Dies ist ein Teststring für diese Aufgabe";
    static char szSubStr [] = "aDies ist ein Teststring für diese Aufgabe";
    // static char szSubStr [] = "ist ein";

// use my function
    int iPos = my_find_sub_str( szStr, szSubStr);
    if (iPos >= 0)
        printf( "Found substring at position %d with my_find_sub_str()\n", iPos);
    else
        printf( "Substring not found with my_find_sub_str() :-(\n");

    // use std lib function
    int iPos2 = stdlib_find_sub_str( szStr, szSubStr);
    if (iPos2 >= 0)
        printf( "Found substring at position %d with strstr()\n", iPos2);
    else
        printf( "Substring not found with strstr() :-(\n");
}
