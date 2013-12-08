#include <stdio.h>

#include <stdlib.h>
void main()
{
float base,height,wide,length,r,longtop,longlower,area;
int choice;
//clrscr();
printf("%30c:" "--------------------\n");
printf("%29c | Calculate The Area |\n");
printf("%30c --------------------\n");
printf("%25c Please Choice Calculate Area\n\n");
printf("\n");
printf("%10c 1 : Triangle 2 : Square 3 : Circle 4 : Trapezoid 5 : Exit\n");
printf("\n");
do{
printf("Please Input Choice : ");
scanf("%d",&choice);
switch(choice)
{
    case 1: printf("%25c1 : Triangle\n");
    	printf("%25cPlease Input Base : ");
		scanf("%f",&base);
		printf("%25cPlease Input Height : ");
		scanf("%f",&height);
		area=base*height*0.5;
		printf("Area of a triangle is = %.2f\n",area);
	break;
	case 2: printf("%25c2 : Square\n");
		printf("%25cPlease Input Wide : ");
		scanf("%f",&wide);
		printf("%25cPlease Input length : ");
		scanf("%f",&length);
		area=wide*length;
		printf("Area of a Square is = %.2f\n",area);
	break;
	case 3:printf("%25c3 : Circle\n");
		printf("%25cPlease Input R : ");
		scanf("%f",&r);
	       //	printf("%25cPlease Input Height : ");
	       //	scanf("%f",&height);
		area=r*r*3.14;
		printf("Area of a Circle is = %.2f\n",area);
	break;
	case 4:printf("%25c4 : Trapezoid\n");
		printf("%25cPlease Input longtop : ");
		scanf("%f",&longtop);
		printf("%25cPlease Input longlower : ");
		scanf("%f",&longlower);
		printf("%25cPlease Input Height : ");
		scanf("%f",&height);
		area=(longtop+longlower)*height*0.5;
		printf("Area of a Trapezoid is = %.2f\n",area);
	break;
	case 5: printf("%25c THANK");
	break;
       default: printf("Please Input choice 1 or 2 or 3 or 4 or 5 :");
       //break;
}
}while(choice !=5);
//getch();
}
