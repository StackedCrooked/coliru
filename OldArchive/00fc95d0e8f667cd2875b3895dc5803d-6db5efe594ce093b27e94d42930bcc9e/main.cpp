#include <stdio.h>
#include <stdlib.h> /*memory functions*/
#include <string.h> /*strlen*/
#include <ctype.h> /*for input testing*/

enum RET { SUCCESS = 0, FAIL = 1 };
enum RETERROR { INV_ARG = 2, INP_MAXLEN, INP_MALLOC, INP_INVALID };

#define MAXPASSLEN 20

int main (int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Error: Invalid number of arguments\n");
        return INV_ARG;
    }
    
    unsigned int input_length = (strlen(argv[1])/sizeof(char));
    if(input_length > MAXPASSLEN)
    {
        printf("Error: Input exceeds max length\n");
        return INP_MAXLEN;
    }

    char *input = NULL;
    input = (char *)calloc(sizeof(char), (input_length+1));
    if(input == NULL)
    {
        printf("Error: Could not allocate input string\n");
        return INP_MALLOC;
    }
    input = (char *)memcpy(input, argv[1], (input_length+1));

    char *output = NULL;
    input = (char *)calloc(sizeof(char), (input_length+1));
    if(input == NULL)
    {
        printf("Error: Could not allocate input string\n");
        return INP_MALLOC;
    }
    input = (char *)memcpy(input, argv[1], (input_length+1));
    
    unsigned short int lindex = 0;
    for(lindex = 0; lindex < input_length; lindex++)
    {
        if(!isdigit(input[lindex]) && !islower(input[lindex]))
        {
            printf("Error: Input contains invalid characters");
            free(input);
            return INP_INVALID;
        }
    }

    free(input);
    return 0;
}
