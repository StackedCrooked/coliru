#define CHAR 25

#include <stdio.h>
#include <string.h>

int main()
{
char string[CHAR] = ""; int i = 0, k = 0, j = 0, s = 0;

printf("Please enter your name\n");
printf("**********************\n\n");
fgets(string, CHAR, stdin);
puts(string);
printf("The size of the string is %zd\n", strlen(string));

    int line_width = 6;

    for (i = 0; i < line_width; i++)
    {
        for (s = 0; s < i; ++s)
            printf(" ");
        for (k = i; k < line_width - 1; k++){
            if (string[j] == ' ')
                ++j;
            printf("%c ", string[j]);
            ++j;
        }
        printf("\n");
    
    }
}