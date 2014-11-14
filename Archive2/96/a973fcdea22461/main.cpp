#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
   int rad1;
   int rad2;
   if(argc==5)

          if(strcmp(argv[2], "rows")==0)
          {
          sscanf(argv[3], "%d", &rad1);
          sscanf(argv[4], "%d", &rad2);
          }

        char prom1[1024];
        int count2=1;
        while(fgets(prom1, 1024, stdin)!=NULL)
        {
           do
           {
                  if(count2==rad1) //jestli pocitadlo radku rovna se hodnote ul$
                   {
                   puts(prom1);  //vytisknout radek s cislem uloz. na adr. &rad1
                   }
               count2++;   // inkrementace pocitadla -> cisla radku
             }
                 while(count2==rad2);

        }
return 0;
}