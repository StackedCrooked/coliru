#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main (int argc, char **argv)
{
  int option = 0;
  int index=0;
  int num = 0;
  double res= 0.0;

  while ((option = getopt (argc, argv, "K:M:G:T:P:E:h:")) != -1){
    num = atoi(optarg);
    switch (option) {
             case 'M' : res=num/pow(1024,2);
                 printf("%d = %.1f M",num,res);
                 break;
             case 'G' : res=num/pow(1024,3);
                 printf("%d = %.1f G",num,res);
                 break;
             case 'T' :res=num/pow(1024,4);
                 printf("%d = %.1f T",num,res);
                 break;
             case 'P' : res=num/pow(1024,5);
                 printf("%d = %.1f P",num,res);
                 break;
             case 'E' : res=num/pow(1024,6);
                 printf("%d = %.1f E",num,res);
                 break;
            case 'h' :res=10.7;
                 printf("%d = %.1f G",num,res);
                 break;
             default: res = num/1024;
                 printf("%d = %.1f K",num,res);
        }
    
  }

    for (index = optind; index < argc; index++){
        num = atoi(argv[index]);
        res = (double)num/1024;
        printf("non opt %d = %.1f K",num,res);
    }
  return 0;
}