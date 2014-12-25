#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main (int argc, char **argv)
{
    int option = 0;

    int last=1;
    int first=1;
    int increment=1;
    int n;
    if (argc==2)
        last=atoi(argv[1]);
       // printf("%d\n", last);
        
    if(argc==3)
    {
        first=atoi(argv[1]);
        last=atoi(argv[2]);
    }

    if(argc==4)
    {
        first=atoi(argv[1]);
        increment=atoi(argv[2]);
        last=atoi(argv[3]);
    }
            
while ((option = getopt (argc, argv, "w:")) != -1)
    {

        switch (option)
        {
        case 'w' :
            while(first<=last)
            {
                //int n;
                n=(int)log10(last)-(int)log10(first);
                while(n>0)
                {
                    printf("0");
                    n--;
                }

                printf("%d\n",first);
                first+=increment;
            }
            break;
            
        default:
            while(first<=last)
            {
                printf("%d\n",first);
                first+=increment;
            }
        }
    }
    return 0;
}





