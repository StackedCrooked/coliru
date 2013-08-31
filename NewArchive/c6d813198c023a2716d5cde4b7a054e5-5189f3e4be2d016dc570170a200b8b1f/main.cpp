 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

typedef struct
{
    float height;
    float width;
    float length;
}Box;

void usage(void)
{

    printf("\nUsage: [command] [parameter] [amount]\n");
    printf("commands:\n\tSet\n\tGet\n");
    printf("parameters:\n\theight\n\twidth\n\tlength\n");
}


int main()
{
    usage();
    Box box1 = {0,0,0};
    int loop = 1;
    float num;
    char cp[65];
    char const *delims =  " !@#$%^&*():;/><.,\\?\"";
    char *tok1, *tok2, *tok3, *temp;

beginning:
    while(loop)
    {

        //Read the command from standard input
        char str[65];
        fgets(str, 64, stdin);
        str[64] = 0;

        //Tokenize the string
        strncpy(cp, str, 64);
        tok1 = strtok(cp, delims);
        tok2 = strtok(NULL, delims);
        tok3 = strtok(NULL, delims);

        //Check if tok3 is float
        num = strtof(tok3, &temp);
        
        if(num != 0)
        {

        }
        else
        {
            usage();
            goto beginning;
        }



    if(strcmp(tok1,"Get")==0 && strcmp(tok2,"height")==0)
    {
        printf("%f", box1.height);
    }
    else if(strcmp(tok1,"Get")==0 && strcmp(tok2,"width")==0)
    {
        printf("%f", box1.width);
    }
    else if(strcmp(tok1,"Get")==0 && strcmp(tok2,"length")==0)
    {
        printf("%f", box1.length);
    }
    else if(strcmp(tok1, "Get")==0)
    {
        usage();
        goto beginning;
    }

    if(strcmp(tok1,"Set")==0 && strcmp(tok2, "height")==0)
    {
        box1.height = num;
        printf("%f", box1.height);
    }
    else if(strcmp(tok1,"Set")==0 && strcmp(tok2,"width")==0)
    {
        box1.width = num;
    }
    else if(strcmp(tok1,"Set")==0 && strcmp(tok2,"length")==0)
    {
        box1.length = num;
    }
    else if(strcmp(tok1,"Set")==0)
    {
        usage();
        goto beginning;
    }
    
    loop = 0;

    }

return 0;
}
