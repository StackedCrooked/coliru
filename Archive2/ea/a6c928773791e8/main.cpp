/**--------------------------
TP21-3
Aero 2-B 26/11/13
Kintrup_Thomas
--------------------------**/

#include<stdio.h>
#include<math.h>
#include<conio.h>

int delta(int a,int b,int c);

int main()
{    	
	int a,b,c,r;
	printf("Programme de resolution d'une equation du second degre.\n\n");
	printf("Entrer a = ");
	scanf("%d", &a);
	printf("Entrer b = ");
	scanf("%d", &b);
	printf("Entrer c = ");
	scanf("%d", &c);
	r = delta(a,b,c);
	printf("La fonction comporte %d racine(s).\n\n",r);
	getch();
}

int delta(int a,int b,int c)
{
	int d;
	d = b*b-4*a*c;
	if(d>2)
		{
			return 2 ;
		}
	else if(d=0)
		{
			return 1 ;
		}
	else
	{
		return 0;
	}
}