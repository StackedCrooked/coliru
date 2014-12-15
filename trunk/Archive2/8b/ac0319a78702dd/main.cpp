#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main (int argc, char **argv)
{
  int option = 0;
  double num = 0.0;

  while ((option = getopt (argc, argv, "M:G:T:P:E:h:")) != -1)
    switch (option) {
             case 'M' : num=num/1e6;
                 break;
             case 'G' : num=num/1e9;
                 break;
             case 'T' :num=num/1e12;
                 break;
             case 'P' : num=num/1e15;
                 break;
               case 'E' : num=num/1e18;
                 break;
                 case 'h' :num=10.7;
                 break;

             default:
                 num = num/1e3;
                 exit(EXIT_FAILURE);
        }
    
                
printf("%f",num);
  return 0;
}