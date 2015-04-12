#include<stdio.h>
#include<conio.h>
main()
{
int i , m , x , a, s=0;
printf(" Vvedite chislo a: ");
scanf( "%d%d " , &a);
for(i=1;i<=a;i++)
{
scanf("%d" , &x);
if(x%a==0)s=s+x;
}
printf("s=%d" , s);
getch();
}