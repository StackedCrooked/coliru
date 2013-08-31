#include<stdio.h>
int main(void)
{
char letra;
printf(“ingrese una letra entre a-d”);
scanf(“%c”,&letra);
switch(letra)
{
case ‘a’: printf(“Escogiste la letra a”);
break;
case ‘b’: printf(“Escogiste la letra b”);
break;
case ‘c’: printf(“Escogiste la letra c”);
break;
default:printf(“Solo las opciones son a,b,c, y d);
break;
}
return 0;
}