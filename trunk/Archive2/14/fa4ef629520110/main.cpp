#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    // read integer from a specified line in text file
    int line_number = 47; // first line is line number 1

    printf("try to read integer from line %d of file " __FILE__ "\n", line_number); 
    FILE *file = fopen(__FILE__, "r");

    int ch;

    while (line_number > 1 && (ch = fgetc(file)) != EOF)
        if (ch == '\n')
            --line_number; // skip till we reach the required line

    double numbers[20];
    size_t numbers_len = 0;
    char buffer[100];
    char *result = fgets(buffer, sizeof buffer, file);

    if (result != NULL && !feof(file))
    {
        char *token = strtok(buffer, " ");

        printf("At line %d, strain name is \"%s\".\n", line_number, token);

        while ((token = strtok(NULL, " ")) != NULL)
            numbers[numbers_len++] = strtod(token, NULL);

        printf("A total number of %zu numbers were extracted.\n", numbers_len);
        printf("They are: ");

        for (size_t i=0; i < numbers_len; ++i)
            printf("%f ", numbers[i]);

        printf("\n");
    }
}

/*
    StrainOne   0.000234 0.00237 0.00241 0.00089
    StrainTwo   1.000234 1.00237 1.00241 1.00089 1.03220
    StrainThree 2.000234 2.00237 2.00241 2.00089 2.03220 2.39921
    StrainFour  3.000234 3.00237 3.00241 3.00089 3.03220 3.39921 3.90200
*/
