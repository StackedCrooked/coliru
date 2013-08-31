#include <stdio.h>
#include <stdlib.h> /*memory functions*/
#include <string.h> /*strlen*/
#include <ctype.h> /*for input testing*/

enum RET { SUCCESS = 0, FAIL = 1 };
enum RETERROR { INV_ARG = 2, INP_MAXLEN, INP_MALLOC, INP_INVALID, OUT_MALLOC };

#define MAXPASSLEN 20

int main (int argc, char *argv[])
{
    /*VALIDATION*/
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
    
    char *output = NULL;
    output = (char *)calloc(sizeof(char), ((input_length*4)+1));
    if(output == NULL)
    {
        printf("Error: Could not allocate output string\n");
        return OUT_MALLOC;
    }
    
    /*ENCIPHER*/
    char temp = '\0';
    for(lindex = 0; lindex < input_length; lindex++)
    {
        temp = input[lindex];
        
        switch ((lindex+1))
        {
            case 1:
                if(isdigit(temp))
                {
                    output[(lindex*4)] = '5';
                    switch (temp)
                    {
                        case '0':
                            output[(lindex*4)+1] = '1';
                            break;
                        case '1':
                            output[(lindex*4)+1] = '0';
                            break;
                        case '2':
                            output[(lindex*4)+1] = '3';
                            break;
                        case '3':
                            output[(lindex*4)+1] = '2';
                            break;
                        case '4':
                            output[(lindex*4)+1] = '5';
                            break;
                        case '5':
                            output[(lindex*4)+1] = '4';
                            break;
                        case '6':
                            output[(lindex*4)+1] = '7';
                            break;
                        case '7':
                            output[(lindex*4)+1] = '6';
                            break;
                        case '8':
                            output[(lindex*4)+1] = '9';
                            break;
                        case '9':
                            output[(lindex*4)+1] = '8';
                            break;
                    }
                }
                else if(islower(temp))
                {
                    switch (temp)
                    {
                        case 'a':
                            output[(lindex*4)] = '0';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'b':
                            output[(lindex*4)] = '0';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'c':
                            output[(lindex*4)] = '0';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'd':
                            output[(lindex*4)] = '0';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 'e':
                            output[(lindex*4)] = '0';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 'f':
                            output[(lindex*4)] = '0';
                            output[(lindex*4)+1] = '7';
                            break;
                        case 'g':
                            output[(lindex*4)] = '0';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 'h':
                            output[(lindex*4)] = '0';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 'i':
                            output[(lindex*4)] = '0';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 'j':
                            output[(lindex*4)] = '0';
                            output[(lindex*4)+1] = 'b';
                            break;
                        case 'k':
                            output[(lindex*4)] = '0';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 'l':
                            output[(lindex*4)] = '0';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'm':
                            output[(lindex*4)] = '0';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'n':
                            output[(lindex*4)] = '0';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'o':
                            output[(lindex*4)] = '0';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'p':
                            output[(lindex*4)] = '1';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'q':
                            output[(lindex*4)] = '1';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'r':
                            output[(lindex*4)] = '1';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 's':
                            output[(lindex*4)] = '1';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 't':
                            output[(lindex*4)] = '1';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 'u':
                            output[(lindex*4)] = '1';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 'v':
                            output[(lindex*4)] = '1';
                            output[(lindex*4)+1] = '7';
                            break;
                        case 'w':
                            output[(lindex*4)] = '1';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 'x':
                            output[(lindex*4)] = '1';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 'y':
                            output[(lindex*4)] = '1';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 'z':
                            output[(lindex*4)] = '1';
                            output[(lindex*4)+1] = 'b';
                            break;
                    }
                }
                else
                {
                    output[(lindex*4)] = 'X';
                    output[(lindex*4)+1] = 'X';
                }
                output[(lindex*4)+2] = 'd';
                output[(lindex*4)+3] = '6';
                break;
            case 2:
                if(isdigit(temp))
                {
                    output[(lindex*4)] = 'e';
                    switch (temp)
                    {
                        case '0':
                            output[(lindex*4)+1] = '4';
                            break;
                        case '1':
                            output[(lindex*4)+1] = '5';
                            break;
                        case '2':
                            output[(lindex*4)+1] = '6';
                            break;
                        case '3':
                            output[(lindex*4)+1] = '7';
                            break;
                        case '4':
                            output[(lindex*4)+1] = '0';
                            break;
                        case '5':
                            output[(lindex*4)+1] = '1';
                            break;
                        case '6':
                            output[(lindex*4)+1] = '2';
                            break;
                        case '7':
                            output[(lindex*4)+1] = '3';
                            break;
                        case '8':
                            output[(lindex*4)+1] = 'c';
                            break;
                        case '9':
                            output[(lindex*4)+1] = 'd';
                            break;
                    }
                }
                else if(islower(temp))
                {
                    switch (temp)
                    {
                        case 'a':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 'b':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 'c':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '7';
                            break;
                        case 'd':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'e':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'f':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'g':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'h':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'i':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'j':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'k':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'l':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 'm':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 'n':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 'o':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = 'b';
                            break;
                        case 'p':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 'q':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 'r':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 's':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '7';
                            break;
                        case 't':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'u':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'v':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'w':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'x':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'y':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'z':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = 'e';
                            break;
                    }
                }
                else
                {
                    output[(lindex*4)] = 'X';
                    output[(lindex*4)+1] = 'X';
                }
                output[(lindex*4)+2] = 'e';
                output[(lindex*4)+3] = '9';
                break;
            case 3:
                if(isdigit(temp))
                {
                    output[(lindex*4)] = 'e';
                    switch (temp)
                    {
                        case '0':
                            output[(lindex*4)+1] = 'd';
                            break;
                        case '1':
                            output[(lindex*4)+1] = 'c';
                            break;
                        case '2':
                            output[(lindex*4)+1] = 'f';
                            break;
                        case '3':
                            output[(lindex*4)+1] = 'e';
                            break;
                        case '4':
                            output[(lindex*4)+1] = '9';
                            break;
                        case '5':
                            output[(lindex*4)+1] = '8';
                            break;
                        case '6':
                            output[(lindex*4)+1] = 'b';
                            break;
                        case '7':
                            output[(lindex*4)+1] = 'a';
                            break;
                        case '8':
                            output[(lindex*4)+1] = '5';
                            break;
                        case '9':
                            output[(lindex*4)+1] = '4';
                            break;
                    }
                }
                else if(islower(temp))
                {
                    switch (temp)
                    {
                        case 'a':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'b':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'c':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'd':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 'e':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 'f':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = 'b';
                            break;
                        case 'g':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 'h':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 'i':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 'j':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '7';
                            break;
                        case 'k':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 'l':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'm':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'n':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'o':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'p':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'q':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'r':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 's':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 't':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 'u':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 'v':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = 'b';
                            break;
                        case 'w':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 'x':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 'y':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 'z':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '7';
                            break;
                    }
                }
                else
                {
                    output[(lindex*4)] = 'X';
                    output[(lindex*4)+1] = 'X';
                }
                output[(lindex*4)+2] = 'f';
                output[(lindex*4)+3] = '0';
                break;
            case 4:
                if(isdigit(temp))
                {
                    output[(lindex*4)] = 'c';
                    switch (temp)
                    {
                        case '0':
                            output[(lindex*4)+1] = 'b';
                            break;
                        case '1':
                            output[(lindex*4)+1] = 'a';
                            break;
                        case '2':
                            output[(lindex*4)+1] = '9';
                            break;
                        case '3':
                            output[(lindex*4)+1] = '8';
                            break;
                        case '4':
                            output[(lindex*4)+1] = 'f';
                            break;
                        case '5':
                            output[(lindex*4)+1] = 'e';
                            break;
                        case '6':
                            output[(lindex*4)+1] = 'd';
                            break;
                        case '7':
                            output[(lindex*4)+1] = 'c';
                            break;
                        case '8':
                            output[(lindex*4)+1] = '3';
                            break;
                        case '9':
                            output[(lindex*4)+1] = '2';
                            break;
                    }
                }
                else if(islower(temp))
                {
                    switch (temp)
                    {
                        case 'a':
                            output[(lindex*4)] = '9';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 'b':
                            output[(lindex*4)] = '9';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 'c':
                            output[(lindex*4)] = '9';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 'd':
                            output[(lindex*4)] = '9';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'e':
                            output[(lindex*4)] = '9';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'f':
                            output[(lindex*4)] = '9';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'g':
                            output[(lindex*4)] = '9';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'h':
                            output[(lindex*4)] = '9';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'i':
                            output[(lindex*4)] = '9';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'j':
                            output[(lindex*4)] = '9';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'k':
                            output[(lindex*4)] = '9';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'l':
                            output[(lindex*4)] = '9';
                            output[(lindex*4)+1] = '7';
                            break;
                        case 'm':
                            output[(lindex*4)] = '9';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 'n':
                            output[(lindex*4)] = '9';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 'o':
                            output[(lindex*4)] = '9';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 'p':
                            output[(lindex*4)] = '8';
                            output[(lindex*4)+1] = 'b';
                            break;
                        case 'q':
                            output[(lindex*4)] = '8';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 'r':
                            output[(lindex*4)] = '8';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 's':
                            output[(lindex*4)] = '8';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 't':
                            output[(lindex*4)] = '8';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'u':
                            output[(lindex*4)] = '8';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'v':
                            output[(lindex*4)] = '8';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'w':
                            output[(lindex*4)] = '8';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'x':
                            output[(lindex*4)] = '8';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'y':
                            output[(lindex*4)] = '8';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'z':
                            output[(lindex*4)] = '8';
                            output[(lindex*4)+1] = '1';
                            break;
                    }
                }
                else
                {
                    output[(lindex*4)] = 'X';
                    output[(lindex*4)+1] = 'X';
                }
                output[(lindex*4)+2] = 'f';
                output[(lindex*4)+3] = '2';
                break;
            case 5:
                if(isdigit(temp))
                {
                    output[(lindex*4)] = '6';
                    switch (temp)
                    {
                        case '0':
                            output[(lindex*4)+1] = 'b';
                            break;
                        case '1':
                            output[(lindex*4)+1] = 'a';
                            break;
                        case '2':
                            output[(lindex*4)+1] = '9';
                            break;
                        case '3':
                            output[(lindex*4)+1] = '8';
                            break;
                        case '4':
                            output[(lindex*4)+1] = 'f';
                            break;
                        case '5':
                            output[(lindex*4)+1] = 'e';
                            break;
                        case '6':
                            output[(lindex*4)+1] = 'd';
                            break;
                        case '7':
                            output[(lindex*4)+1] = 'c';
                            break;
                        case '8':
                            output[(lindex*4)+1] = '3';
                            break;
                        case '9':
                            output[(lindex*4)+1] = '2';
                            break;
                    }
                }
                else if(islower(temp))
                {
                    switch (temp)
                    {
                        case 'a':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 'b':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 'c':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 'd':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'e':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'f':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'g':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'h':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'i':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'j':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'k':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'l':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '7';
                            break;
                        case 'm':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 'n':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 'o':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 'p':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = 'b';
                            break;
                        case 'q':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 'r':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 's':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 't':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'u':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'v':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'w':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'x':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'y':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'z':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '1';
                            break;
                    }
                }
                else
                {
                    output[(lindex*4)] = 'X';
                    output[(lindex*4)+1] = 'X';
                }
                output[(lindex*4)+2] = '6';
                output[(lindex*4)+3] = '4';
                break;
            case 6:
                if(isdigit(temp))
                {
                    output[(lindex*4)] = '0';
                    switch (temp)
                    {
                        case '0':
                            output[(lindex*4)+1] = '5';
                            break;
                        case '1':
                            output[(lindex*4)+1] = '4';
                            break;
                        case '2':
                            output[(lindex*4)+1] = '7';
                            break;
                        case '3':
                            output[(lindex*4)+1] = '6';
                            break;
                        case '4':
                            output[(lindex*4)+1] = '1';
                            break;
                        case '5':
                            output[(lindex*4)+1] = '0';
                            break;
                        case '6':
                            output[(lindex*4)+1] = '3';
                            break;
                        case '7':
                            output[(lindex*4)+1] = '2';
                            break;
                        case '8':
                            output[(lindex*4)+1] = 'd';
                            break;
                        case '9':
                            output[(lindex*4)+1] = 'c';
                            break;
                    }
                }
                else if(islower(temp))
                {
                    switch (temp)
                    {
                        case 'a':
                            output[(lindex*4)] = '5';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 'b':
                            output[(lindex*4)] = '5';
                            output[(lindex*4)+1] = '7';
                            break;
                        case 'c':
                            output[(lindex*4)] = '5';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 'd':
                            output[(lindex*4)] = '5';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'e':
                            output[(lindex*4)] = '5';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'f':
                            output[(lindex*4)] = '5';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'g':
                            output[(lindex*4)] = '5';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'h':
                            output[(lindex*4)] = '5';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'i':
                            output[(lindex*4)] = '5';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'j':
                            output[(lindex*4)] = '5';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'k':
                            output[(lindex*4)] = '5';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'l':
                            output[(lindex*4)] = '5';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 'm':
                            output[(lindex*4)] = '5';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 'n':
                            output[(lindex*4)] = '5';
                            output[(lindex*4)+1] = 'b';
                            break;
                        case 'o':
                            output[(lindex*4)] = '5';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 'p':
                            output[(lindex*4)] = '4';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 'q':
                            output[(lindex*4)] = '4';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 'r':
                            output[(lindex*4)] = '4';
                            output[(lindex*4)+1] = '7';
                            break;
                        case 's':
                            output[(lindex*4)] = '4';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 't':
                            output[(lindex*4)] = '4';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'u':
                            output[(lindex*4)] = '4';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'v':
                            output[(lindex*4)] = '4';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'w':
                            output[(lindex*4)] = '4';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'x':
                            output[(lindex*4)] = '4';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'y':
                            output[(lindex*4)] = '4';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'z':
                            output[(lindex*4)] = '4';
                            output[(lindex*4)+1] = 'f';
                            break;
                    }
                }
                else
                {
                    output[(lindex*4)] = 'X';
                    output[(lindex*4)+1] = 'X';
                }
                output[(lindex*4)+2] = 'a';
                output[(lindex*4)+3] = 'd';
                break;
            case 7:
                if(isdigit(temp))
                {
                    output[(lindex*4)] = '8';
                    switch (temp)
                    {
                        case '0':
                            output[(lindex*4)+1] = '7';
                            break;
                        case '1':
                            output[(lindex*4)+1] = '6';
                            break;
                        case '2':
                            output[(lindex*4)+1] = '5';
                            break;
                        case '3':
                            output[(lindex*4)+1] = '4';
                            break;
                        case '4':
                            output[(lindex*4)+1] = '3';
                            break;
                        case '5':
                            output[(lindex*4)+1] = '2';
                            break;
                        case '6':
                            output[(lindex*4)+1] = '1';
                            break;
                        case '7':
                            output[(lindex*4)+1] = '0';
                            break;
                        case '8':
                            output[(lindex*4)+1] = 'f';
                            break;
                        case '9':
                            output[(lindex*4)+1] = 'e';
                            break;
                    }
                }
                else if(islower(temp))
                {
                    switch (temp)
                    {
                        case 'a':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 'b':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 'c':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 'd':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'e':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'f':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'g':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'h':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'i':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'j':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'k':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'l':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = 'b';
                            break;
                        case 'm':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 'n':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 'o':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 'p':
                            output[(lindex*4)] = 'c';
                            output[(lindex*4)+1] = '7';
                            break;
                        case 'q':
                            output[(lindex*4)] = 'c';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 'r':
                            output[(lindex*4)] = 'c';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 's':
                            output[(lindex*4)] = 'c';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 't':
                            output[(lindex*4)] = 'c';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'u':
                            output[(lindex*4)] = 'c';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'v':
                            output[(lindex*4)] = 'c';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'w':
                            output[(lindex*4)] = 'c';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'x':
                            output[(lindex*4)] = 'c';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'y':
                            output[(lindex*4)] = 'c';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'z':
                            output[(lindex*4)] = 'c';
                            output[(lindex*4)+1] = 'd';
                            break;
                    }
                }
                else
                {
                    output[(lindex*4)] = 'X';
                    output[(lindex*4)+1] = 'X';
                }
                output[(lindex*4)+2] = 'c';
                output[(lindex*4)+3] = '8';
                break;
            case 8:
                if(isdigit(temp))
                {
                    output[(lindex*4)] = '2';
                    switch (temp)
                    {
                        case '0':
                            output[(lindex*4)+1] = '9';
                            break;
                        case '1':
                            output[(lindex*4)+1] = '8';
                            break;
                        case '2':
                            output[(lindex*4)+1] = 'b';
                            break;
                        case '3':
                            output[(lindex*4)+1] = 'a';
                            break;
                        case '4':
                            output[(lindex*4)+1] = 'd';
                            break;
                        case '5':
                            output[(lindex*4)+1] = 'c';
                            break;
                        case '6':
                            output[(lindex*4)+1] = 'f';
                            break;
                        case '7':
                            output[(lindex*4)+1] = 'e';
                            break;
                        case '8':
                            output[(lindex*4)+1] = '1';
                            break;
                        case '9':
                            output[(lindex*4)+1] = '0';
                            break;
                    }
                }
                else if(islower(temp))
                {
                    switch (temp)
                    {
                        case 'a':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 'b':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = 'b';
                            break;
                        case 'c':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 'd':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'e':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'f':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'g':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'h':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'i':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'j':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'k':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'l':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 'm':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 'n':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '7';
                            break;
                        case 'o':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 'p':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 'q':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 'r':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = 'b';
                            break;
                        case 's':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 't':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'u':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'v':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'w':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'x':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'y':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'z':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '3';
                            break;
                    }
                }
                else
                {
                    output[(lindex*4)] = 'X';
                    output[(lindex*4)+1] = 'X';
                }
                output[(lindex*4)+2] = '7';
                output[(lindex*4)+3] = '5';
                break;
            case 9:
                if(isdigit(temp))
                {
                    output[(lindex*4)] = 'd';
                    switch (temp)
                    {
                        case '0':
                            output[(lindex*4)+1] = 'c';
                            break;
                        case '1':
                            output[(lindex*4)+1] = 'd';
                            break;
                        case '2':
                            output[(lindex*4)+1] = 'e';
                            break;
                        case '3':
                            output[(lindex*4)+1] = 'f';
                            break;
                        case '4':
                            output[(lindex*4)+1] = '8';
                            break;
                        case '5':
                            output[(lindex*4)+1] = '9';
                            break;
                        case '6':
                            output[(lindex*4)+1] = 'a';
                            break;
                        case '7':
                            output[(lindex*4)+1] = 'b';
                            break;
                        case '8':
                            output[(lindex*4)+1] = '4';
                            break;
                        case '9':
                            output[(lindex*4)+1] = '5';
                            break;
                    }
                }
                else if(islower(temp))
                {
                    switch (temp)
                    {
                        case 'a':
                            output[(lindex*4)] = '8';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'b':
                            output[(lindex*4)] = '8';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'c':
                            output[(lindex*4)] = '8';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'd':
                            output[(lindex*4)] = '8';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 'e':
                            output[(lindex*4)] = '8';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 'f':
                            output[(lindex*4)] = '8';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 'g':
                            output[(lindex*4)] = '8';
                            output[(lindex*4)+1] = 'b';
                            break;
                        case 'h':
                            output[(lindex*4)] = '8';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 'i':
                            output[(lindex*4)] = '8';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 'j':
                            output[(lindex*4)] = '8';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 'k':
                            output[(lindex*4)] = '8';
                            output[(lindex*4)+1] = '7';
                            break;
                        case 'l':
                            output[(lindex*4)] = '8';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'm':
                            output[(lindex*4)] = '8';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'n':
                            output[(lindex*4)] = '8';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'o':
                            output[(lindex*4)] = '8';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'p':
                            output[(lindex*4)] = '9';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'q':
                            output[(lindex*4)] = '9';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'r':
                            output[(lindex*4)] = '9';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 's':
                            output[(lindex*4)] = '9';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 't':
                            output[(lindex*4)] = '9';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 'u':
                            output[(lindex*4)] = '9';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 'v':
                            output[(lindex*4)] = '9';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 'w':
                            output[(lindex*4)] = '9';
                            output[(lindex*4)+1] = 'b';
                            break;
                        case 'x':
                            output[(lindex*4)] = '9';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 'y':
                            output[(lindex*4)] = '9';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 'z':
                            output[(lindex*4)] = '9';
                            output[(lindex*4)+1] = '6';
                            break;
                    }
                }
                else
                {
                    output[(lindex*4)] = 'X';
                    output[(lindex*4)+1] = 'X';
                }
                output[(lindex*4)+2] = '3';
                output[(lindex*4)+3] = '1';
                break;
            case 10:
                if(isdigit(temp))
                {
                    output[(lindex*4)] = '1';
                    switch (temp)
                    {
                        case '0':
                            output[(lindex*4)+1] = 'b';
                            break;
                        case '1':
                            output[(lindex*4)+1] = 'a';
                            break;
                        case '2':
                            output[(lindex*4)+1] = '9';
                            break;
                        case '3':
                            output[(lindex*4)+1] = '8';
                            break;
                        case '4':
                            output[(lindex*4)+1] = 'f';
                            break;
                        case '5':
                            output[(lindex*4)+1] = 'e';
                            break;
                        case '6':
                            output[(lindex*4)+1] = 'd';
                            break;
                        case '7':
                            output[(lindex*4)+1] = 'c';
                            break;
                        case '8':
                            output[(lindex*4)+1] = '3';
                            break;
                        case '9':
                            output[(lindex*4)+1] = '2';
                            break;
                    }
                }
                else if(islower(temp))
                {
                    switch (temp)
                    {
                        case 'a':
                            output[(lindex*4)] = '4';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 'b':
                            output[(lindex*4)] = '4';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 'c':
                            output[(lindex*4)] = '4';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 'd':
                            output[(lindex*4)] = '4';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'e':
                            output[(lindex*4)] = '4';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'f':
                            output[(lindex*4)] = '4';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'g':
                            output[(lindex*4)] = '4';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'h':
                            output[(lindex*4)] = '4';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'i':
                            output[(lindex*4)] = '4';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'j':
                            output[(lindex*4)] = '4';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'k':
                            output[(lindex*4)] = '4';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'l':
                            output[(lindex*4)] = '4';
                            output[(lindex*4)+1] = '7';
                            break;
                        case 'm':
                            output[(lindex*4)] = '4';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 'n':
                            output[(lindex*4)] = '4';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 'o':
                            output[(lindex*4)] = '4';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 'p':
                            output[(lindex*4)] = '5';
                            output[(lindex*4)+1] = 'b';
                            break;
                        case 'q':
                            output[(lindex*4)] = '5';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 'r':
                            output[(lindex*4)] = '5';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 's':
                            output[(lindex*4)] = '5';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 't':
                            output[(lindex*4)] = '5';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'u':
                            output[(lindex*4)] = '5';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'v':
                            output[(lindex*4)] = '5';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'w':
                            output[(lindex*4)] = '5';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'x':
                            output[(lindex*4)] = '5';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'y':
                            output[(lindex*4)] = '5';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'z':
                            output[(lindex*4)] = '5';
                            output[(lindex*4)+1] = '1';
                            break;
                    }
                }
                else
                {
                    output[(lindex*4)] = 'X';
                    output[(lindex*4)+1] = 'X';
                }
                output[(lindex*4)+2] = 'b';
                output[(lindex*4)+3] = 'c';
                break;
            case 11:
                if(isdigit(temp))
                {
                    output[(lindex*4)] = '7';
                    switch (temp)
                    {
                        case '0':
                            output[(lindex*4)+1] = '2';
                            break;
                        case '1':
                            output[(lindex*4)+1] = '3';
                            break;
                        case '2':
                            output[(lindex*4)+1] = '0';
                            break;
                        case '3':
                            output[(lindex*4)+1] = '1';
                            break;
                        case '4':
                            output[(lindex*4)+1] = '6';
                            break;
                        case '5':
                            output[(lindex*4)+1] = '7';
                            break;
                        case '6':
                            output[(lindex*4)+1] = '4';
                            break;
                        case '7':
                            output[(lindex*4)+1] = '5';
                            break;
                        case '8':
                            output[(lindex*4)+1] = 'a';
                            break;
                        case '9':
                            output[(lindex*4)+1] = 'b';
                            break;
                    }
                }
                else if(islower(temp))
                {
                    switch (temp)
                    {
                        case 'a':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'b':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'c':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'd':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 'e':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '7';
                            break;
                        case 'f':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 'g':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 'h':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 'i':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = 'b';
                            break;
                        case 'j':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 'k':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 'l':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'm':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'n':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'o':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'p':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'q':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'r':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 's':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 't':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 'u':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '7';
                            break;
                        case 'v':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 'w':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 'x':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 'y':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = 'b';
                            break;
                        case 'z':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '8';
                            break;
                    }
                }
                else
                {
                    output[(lindex*4)] = 'X';
                    output[(lindex*4)+1] = 'X';
                }
                output[(lindex*4)+2] = 'f';
                output[(lindex*4)+3] = '8';
                break;
            case 12:
                if(isdigit(temp))
                {
                    output[(lindex*4)] = 'e';
                    switch (temp)
                    {
                        case '0':
                            output[(lindex*4)+1] = '9';
                            break;
                        case '1':
                            output[(lindex*4)+1] = '8';
                            break;
                        case '2':
                            output[(lindex*4)+1] = 'b';
                            break;
                        case '3':
                            output[(lindex*4)+1] = 'a';
                            break;
                        case '4':
                            output[(lindex*4)+1] = 'd';
                            break;
                        case '5':
                            output[(lindex*4)+1] = 'c';
                            break;
                        case '6':
                            output[(lindex*4)+1] = 'f';
                            break;
                        case '7':
                            output[(lindex*4)+1] = 'e';
                            break;
                        case '8':
                            output[(lindex*4)+1] = '1';
                            break;
                        case '9':
                            output[(lindex*4)+1] = '0';
                            break;
                    }
                }
                else if(islower(temp))
                {
                    switch (temp)
                    {
                        case 'a':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 'b':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = 'b';
                            break;
                        case 'c':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 'd':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'e':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'f':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'g':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'h':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'i':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'j':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'k':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'l':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 'm':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 'n':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '7';
                            break;
                        case 'o':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 'p':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 'q':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 'r':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = 'b';
                            break;
                        case 's':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 't':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'u':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'v':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'w':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'x':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'y':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'z':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '3';
                            break;
                    }
                }
                else
                {
                    output[(lindex*4)] = 'X';
                    output[(lindex*4)+1] = 'X';
                }
                output[(lindex*4)+2] = '0';
                output[(lindex*4)+3] = 'c';
                break;
            case 13:
                if(isdigit(temp))
                {
                    output[(lindex*4)] = '7';
                    switch (temp)
                    {
                        case '0':
                            output[(lindex*4)+1] = 'b';
                            break;
                        case '1':
                            output[(lindex*4)+1] = 'a';
                            break;
                        case '2':
                            output[(lindex*4)+1] = '9';
                            break;
                        case '3':
                            output[(lindex*4)+1] = '8';
                            break;
                        case '4':
                            output[(lindex*4)+1] = 'f';
                            break;
                        case '5':
                            output[(lindex*4)+1] = 'e';
                            break;
                        case '6':
                            output[(lindex*4)+1] = 'd';
                            break;
                        case '7':
                            output[(lindex*4)+1] = 'c';
                            break;
                        case '8':
                            output[(lindex*4)+1] = '3';
                            break;
                        case '9':
                            output[(lindex*4)+1] = '2';
                            break;
                    }
                }
                else if(islower(temp))
                {
                    switch (temp)
                    {
                        case 'a':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 'b':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 'c':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 'd':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'e':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'f':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'g':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'h':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'i':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'j':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'k':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'l':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '7';
                            break;
                        case 'm':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 'n':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 'o':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 'p':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = 'b';
                            break;
                        case 'q':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 'r':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 's':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 't':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'u':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'v':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'w':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'x':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'y':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'z':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '1';
                            break;
                    }
                }
                else
                {
                    output[(lindex*4)] = 'X';
                    output[(lindex*4)+1] = 'X';
                }
                output[(lindex*4)+2] = 'd';
                output[(lindex*4)+3] = 'd';
                break;
            case 14:
                if(isdigit(temp))
                {
                    output[(lindex*4)] = '3';
                    switch (temp)
                    {
                        case '0':
                            output[(lindex*4)+1] = '7';
                            break;
                        case '1':
                            output[(lindex*4)+1] = '6';
                            break;
                        case '2':
                            output[(lindex*4)+1] = '5';
                            break;
                        case '3':
                            output[(lindex*4)+1] = '4';
                            break;
                        case '4':
                            output[(lindex*4)+1] = '3';
                            break;
                        case '5':
                            output[(lindex*4)+1] = '2';
                            break;
                        case '6':
                            output[(lindex*4)+1] = '1';
                            break;
                        case '7':
                            output[(lindex*4)+1] = '0';
                            break;
                        case '8':
                            output[(lindex*4)+1] = 'f';
                            break;
                        case '9':
                            output[(lindex*4)+1] = 'e';
                            break;
                    }
                }
                else if(islower(temp))
                {
                    switch (temp)
                    {
                        case 'a':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 'b':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 'c':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 'd':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'e':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'f':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'g':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'h':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'i':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'j':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'k':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'l':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = 'b';
                            break;
                        case 'm':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 'n':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 'o':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 'p':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '7';
                            break;
                        case 'q':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 'r':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 's':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 't':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'u':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'v':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'w':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'x':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'y':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'z':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = 'd';
                            break;
                    }
                }
                else
                {
                    output[(lindex*4)] = 'X';
                    output[(lindex*4)+1] = 'X';
                }
                output[(lindex*4)+2] = 'd';
                output[(lindex*4)+3] = 'd';
                break;
            case 15:
                if(isdigit(temp))
                {
                    output[(lindex*4)] = 'f';
                    switch (temp)
                    {
                        case '0':
                            output[(lindex*4)+1] = '6';
                            break;
                        case '1':
                            output[(lindex*4)+1] = '7';
                            break;
                        case '2':
                            output[(lindex*4)+1] = '4';
                            break;
                        case '3':
                            output[(lindex*4)+1] = '5';
                            break;
                        case '4':
                            output[(lindex*4)+1] = '2';
                            break;
                        case '5':
                            output[(lindex*4)+1] = '3';
                            break;
                        case '6':
                            output[(lindex*4)+1] = '0';
                            break;
                        case '7':
                            output[(lindex*4)+1] = '1';
                            break;
                        case '8':
                            output[(lindex*4)+1] = 'e';
                            break;
                        case '9':
                            output[(lindex*4)+1] = 'f';
                            break;
                    }
                }
                else if(islower(temp))
                {
                    switch (temp)
                    {
                        case 'a':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '7';
                            break;
                        case 'b':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 'c':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 'd':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'e':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'f':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'g':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'h':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'i':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'j':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'k':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'l':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 'm':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = 'b';
                            break;
                        case 'n':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 'o':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 'p':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 'q':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '7';
                            break;
                        case 'r':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 's':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 't':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'u':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'v':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'w':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'x':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'y':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'z':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = 'c';
                            break;
                    }
                }
                else
                {
                    output[(lindex*4)] = 'X';
                    output[(lindex*4)+1] = 'X';
                }
                output[(lindex*4)+2] = 'c';
                output[(lindex*4)+3] = 'a';
                break;
            case 16:
                if(isdigit(temp))
                {
                    output[(lindex*4)] = '3';
                    switch (temp)
                    {
                        case '0':
                            output[(lindex*4)+1] = '8';
                            break;
                        case '1':
                            output[(lindex*4)+1] = '9';
                            break;
                        case '2':
                            output[(lindex*4)+1] = 'a';
                            break;
                        case '3':
                            output[(lindex*4)+1] = 'b';
                            break;
                        case '4':
                            output[(lindex*4)+1] = 'c';
                            break;
                        case '5':
                            output[(lindex*4)+1] = 'd';
                            break;
                        case '6':
                            output[(lindex*4)+1] = 'e';
                            break;
                        case '7':
                            output[(lindex*4)+1] = 'f';
                            break;
                        case '8':
                            output[(lindex*4)+1] = '0';
                            break;
                        case '9':
                            output[(lindex*4)+1] = '1';
                            break;
                    }
                }
                else if(islower(temp))
                {
                    switch (temp)
                    {
                        case 'a':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 'b':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 'c':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = 'b';
                            break;
                        case 'd':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'e':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'f':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'g':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'h':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'i':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'j':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'k':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'l':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 'm':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 'n':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 'o':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '7';
                            break;
                        case 'p':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 'q':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 'r':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 's':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = 'b';
                            break;
                        case 't':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'u':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'v':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'w':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'x':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'y':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'z':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '2';
                            break;
                    }
                }
                else
                {
                    output[(lindex*4)] = 'X';
                    output[(lindex*4)+1] = 'X';
                }
                output[(lindex*4)+2] = '4';
                output[(lindex*4)+3] = 'c';
                break;
            case 17:
                if(isdigit(temp))
                {
                    output[(lindex*4)] = '2';
                    switch (temp)
                    {
                        case '0':
                            output[(lindex*4)+1] = '1';
                            break;
                        case '1':
                            output[(lindex*4)+1] = '0';
                            break;
                        case '2':
                            output[(lindex*4)+1] = '3';
                            break;
                        case '3':
                            output[(lindex*4)+1] = '2';
                            break;
                        case '4':
                            output[(lindex*4)+1] = '5';
                            break;
                        case '5':
                            output[(lindex*4)+1] = '4';
                            break;
                        case '6':
                            output[(lindex*4)+1] = '7';
                            break;
                        case '7':
                            output[(lindex*4)+1] = '6';
                            break;
                        case '8':
                            output[(lindex*4)+1] = '9';
                            break;
                        case '9':
                            output[(lindex*4)+1] = '8';
                            break;
                    }
                }
                else if(islower(temp))
                {
                    switch (temp)
                    {
                        case 'a':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'b':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'c':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'd':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 'e':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 'f':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '7';
                            break;
                        case 'g':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 'h':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 'i':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 'j':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = 'b';
                            break;
                        case 'k':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 'l':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'm':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'n':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'o':
                            output[(lindex*4)] = '7';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'p':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'q':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'r':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 's':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 't':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 'u':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 'v':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '7';
                            break;
                        case 'w':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 'x':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 'y':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 'z':
                            output[(lindex*4)] = '6';
                            output[(lindex*4)+1] = 'b';
                            break;
                    }
                }
                else
                {
                    output[(lindex*4)] = 'X';
                    output[(lindex*4)+1] = 'X';
                }
                output[(lindex*4)+2] = '4';
                output[(lindex*4)+3] = '8';
                break;
            case 18:
                if(isdigit(temp))
                {
                    output[(lindex*4)] = '6';
                    switch (temp)
                    {
                        case '0':
                            output[(lindex*4)+1] = '1';
                            break;
                        case '1':
                            output[(lindex*4)+1] = '0';
                            break;
                        case '2':
                            output[(lindex*4)+1] = '3';
                            break;
                        case '3':
                            output[(lindex*4)+1] = '2';
                            break;
                        case '4':
                            output[(lindex*4)+1] = '5';
                            break;
                        case '5':
                            output[(lindex*4)+1] = '4';
                            break;
                        case '6':
                            output[(lindex*4)+1] = '7';
                            break;
                        case '7':
                            output[(lindex*4)+1] = '6';
                            break;
                        case '8':
                            output[(lindex*4)+1] = '9';
                            break;
                        case '9':
                            output[(lindex*4)+1] = '8';
                            break;
                    }
                }
                else if(islower(temp))
                {
                    switch (temp)
                    {
                        case 'a':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'b':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'c':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'd':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 'e':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 'f':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '7';
                            break;
                        case 'g':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 'h':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 'i':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 'j':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = 'b';
                            break;
                        case 'k':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 'l':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'm':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'n':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'o':
                            output[(lindex*4)] = '3';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'p':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'q':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'r':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 's':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 't':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 'u':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 'v':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '7';
                            break;
                        case 'w':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 'x':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 'y':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 'z':
                            output[(lindex*4)] = '2';
                            output[(lindex*4)+1] = 'b';
                            break;
                    }
                }
                else
                {
                    output[(lindex*4)] = 'X';
                    output[(lindex*4)+1] = 'X';
                }
                output[(lindex*4)+2] = '5';
                output[(lindex*4)+3] = '0';
                break;
            case 19:
                if(isdigit(temp))
                {
                    output[(lindex*4)] = 'e';
                    switch (temp)
                    {
                        case '0':
                            output[(lindex*4)+1] = '4';
                            break;
                        case '1':
                            output[(lindex*4)+1] = '5';
                            break;
                        case '2':
                            output[(lindex*4)+1] = '6';
                            break;
                        case '3':
                            output[(lindex*4)+1] = '7';
                            break;
                        case '4':
                            output[(lindex*4)+1] = '0';
                            break;
                        case '5':
                            output[(lindex*4)+1] = '1';
                            break;
                        case '6':
                            output[(lindex*4)+1] = '2';
                            break;
                        case '7':
                            output[(lindex*4)+1] = '3';
                            break;
                        case '8':
                            output[(lindex*4)+1] = 'c';
                            break;
                        case '9':
                            output[(lindex*4)+1] = 'd';
                            break;
                    }
                }
                else if(islower(temp))
                {
                    switch (temp)
                    {
                        case 'a':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 'b':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 'c':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '7';
                            break;
                        case 'd':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'e':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'f':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'g':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'h':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'i':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'j':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'k':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'l':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 'm':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 'n':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 'o':
                            output[(lindex*4)] = 'b';
                            output[(lindex*4)+1] = 'b';
                            break;
                        case 'p':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 'q':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 'r':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 's':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '7';
                            break;
                        case 't':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'u':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'v':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'w':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'x':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'y':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'z':
                            output[(lindex*4)] = 'a';
                            output[(lindex*4)+1] = 'e';
                            break;
                    }
                }
                else
                {
                    output[(lindex*4)] = 'X';
                    output[(lindex*4)+1] = 'X';
                }
                output[(lindex*4)+2] = '6';
                output[(lindex*4)+3] = 'f';
                break;
            case 20:
                if(isdigit(temp))
                {
                    output[(lindex*4)] = '8';
                    switch (temp)
                    {
                        case '0':
                            output[(lindex*4)+1] = '8';
                            break;
                        case '1':
                            output[(lindex*4)+1] = '9';
                            break;
                        case '2':
                            output[(lindex*4)+1] = 'a';
                            break;
                        case '3':
                            output[(lindex*4)+1] = 'b';
                            break;
                        case '4':
                            output[(lindex*4)+1] = 'c';
                            break;
                        case '5':
                            output[(lindex*4)+1] = 'd';
                            break;
                        case '6':
                            output[(lindex*4)+1] = 'e';
                            break;
                        case '7':
                            output[(lindex*4)+1] = 'f';
                            break;
                        case '8':
                            output[(lindex*4)+1] = '0';
                            break;
                        case '9':
                            output[(lindex*4)+1] = '1';
                            break;
                    }
                }
                else if(islower(temp))
                {
                    switch (temp)
                    {
                        case 'a':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 'b':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 'c':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = 'b';
                            break;
                        case 'd':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'e':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'f':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'g':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'h':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'i':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'j':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = '2';
                            break;
                        case 'k':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = '3';
                            break;
                        case 'l':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = '4';
                            break;
                        case 'm':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = '5';
                            break;
                        case 'n':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = '6';
                            break;
                        case 'o':
                            output[(lindex*4)] = 'd';
                            output[(lindex*4)+1] = '7';
                            break;
                        case 'p':
                            output[(lindex*4)] = 'c';
                            output[(lindex*4)+1] = '8';
                            break;
                        case 'q':
                            output[(lindex*4)] = 'c';
                            output[(lindex*4)+1] = '9';
                            break;
                        case 'r':
                            output[(lindex*4)] = 'c';
                            output[(lindex*4)+1] = 'a';
                            break;
                        case 's':
                            output[(lindex*4)] = 'c';
                            output[(lindex*4)+1] = 'b';
                            break;
                        case 't':
                            output[(lindex*4)] = 'c';
                            output[(lindex*4)+1] = 'c';
                            break;
                        case 'u':
                            output[(lindex*4)] = 'c';
                            output[(lindex*4)+1] = 'd';
                            break;
                        case 'v':
                            output[(lindex*4)] = 'c';
                            output[(lindex*4)+1] = 'e';
                            break;
                        case 'w':
                            output[(lindex*4)] = 'c';
                            output[(lindex*4)+1] = 'f';
                            break;
                        case 'x':
                            output[(lindex*4)] = 'c';
                            output[(lindex*4)+1] = '0';
                            break;
                        case 'y':
                            output[(lindex*4)] = 'c';
                            output[(lindex*4)+1] = '1';
                            break;
                        case 'z':
                            output[(lindex*4)] = 'c';
                            output[(lindex*4)+1] = '2';
                            break;
                    }
                }
                else
                {
                    output[(lindex*4)] = 'X';
                    output[(lindex*4)+1] = 'X';
                }
                output[(lindex*4)+2] = '0';
                output[(lindex*4)+3] = 'c';
                break;
            default:
                break;
        }
    }

    /*CLEANUP*/
    output[(input_length*4)] = '\0';
    printf("\n");
    printf("Input : %s\n", input);
    free(input);
    printf("Output: %s\n", output);
    free(output);
    return SUCCESS;
}

