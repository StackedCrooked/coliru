
# include<stdio.h>
# include<math.h>
int main()
{
char ch;
int val=0;
printf("%d",1);
while(scanf("%c",&ch)==1)
     {
       if(ch=='\n')
         {
            printf("%d\n",val);
            val=0;
            printf("%d!",2);
         }
       else
           {
              printf("%d!",3);
              if(!(ch<0 && ch>127))
                {
                  val=val+1;
                  printf("%d!",4);
                }

           }
        printf("%d!",5);
     }
return 0;
}

