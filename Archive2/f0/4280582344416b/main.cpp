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
    int w;
    int index;    
   // printf("init: %d %d %d ", first, increment, last);
    
    while ((option = getopt (argc, argv, "w")) != -1)
    {
       // printf(" option: %d",option);
     switch (option)
      {
      case 'w':
            w = 1; //do pending
        break;
      default:
            w = 0; //no pending
        printf("default");
        break;
        }
    }
    
    if(argc-optind == 0); //no input, do nothing
    if(argc-optind == 1) 
        last=atoi(argv[optind]);
    if(argc-optind == 2) 
    {
        first=atoi(argv[optind]);
        last=atoi(argv[optind+1]);
    }
    if(argc-optind == 3)
    {
        first=atoi(argv[optind]);
        increment=atoi(argv[optind+1]);
        last=atoi(argv[optind+2]);
    }
    
    //printf("\nRead: %d %d %d\n", first, increment, last);

    if(w == 1){
                while(first<=last)
            {
                n=(int)log10(last)-(int)log10(first);
                while(n>0)
                {
                    printf("0");
                    n--;
                }

                printf("%d\n",first);
                first+=increment;
            }
    }else{
            while(first<=last)
            {
                printf("%d\n",first);
                first+=increment;
            }
    }
    
    return 0;
}





