#include <stdio.h>
#include <string.h>
 
int main() 
{
    char* input = "hello world friend of mine";
    char* space = " ";
    char* pos = input;
    int word_counter = 0;
    
    do {
        pos = strpbrk(pos, space);
        word_counter++;
        pos ? pos++ : pos;
        printf("%d, current pos is:%s\n", word_counter, pos);
    } while (pos != NULL);
}