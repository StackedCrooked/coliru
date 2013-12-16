#include <stdio.h>
#include <conio.h>
int main()
{
   char sn[101],sm;int i;
   for(i=0;i<100;i++)
   {
       sm=getche()
       if(sm>='A'&&sm<='Z')sn[i]=(sm-64)%26+65;
       else if(sm>='a'&&sm<='z')sn[i]=(sm-96)%26+97;
       else if(sm=='\r')break;
   }
   sn[i]='\0';
   printf("Hasil: %s",sn);
}
