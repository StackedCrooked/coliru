#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>


int main()
{
    char line[81], filename[21];
    int i;
    FILE *inFile;

    printf("\nPlease enter the name of a file: ");
    fgets(filename, sizeof(filename), stdin);

    for (i = strlen(filename); i>0; --i)
    {
        switch(filename[i-1])
        {
            case '\n':
            case '\r': filename[i-1] = '\0';
                       continue;
        }
        break;
    }
    
    inFile = fopen(filename, "r");
    if (inFile == NULL)
    {
        printf("\nThe file %s was not successfully opened.", filename);
        printf("\nPlease check that the specified file exists.");
        getchar();
        exit(1);
    }

    while (fgets(line, sizeof(line), inFile) != NULL)
        printf("%s", line);
    for(i = 0; line[i]; ++i)
    {
        line[i] = toupper(line[i]);
    }

    printf("\nPrinted in UPPER case: \n\n");
    rewind(inFile);
    printf("\n%s", line);
    getchar();
}