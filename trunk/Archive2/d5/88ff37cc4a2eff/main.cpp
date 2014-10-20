#include <stdio.h>
#include <math.h>
#define PI 3.14

int main (void)
{
double area, base, width, radius, apathem, side, length;
char shape;

printf ("Please enter the value of base of the triangle:\n");
printf("a)cirvle \n b)triangle");
scanf ("%c", &shape);

switch (shape)
{
case 'a':
printf("Please enter value for radius\n"); /*commets*/ 
if (scanf("%lf", &radius) ! = 1)
{
printf("invalid input");
return 0;
}
if (radius < 0.5)
{ printf("the input cannot be neg or less that 0.5");
return 0;
}

area = (PI * radius * radius);
printf("The area of the circle for radius r %lf is = %lf\n", radius, area);
break;
case'A':
printf("Please enter value for radius\n"); /*commets*/ 
if (scanf("%lf", &radius) ! = 1)
{
printf("invalid input");
return 0;
}
if (radius < 0.5)
{ printf("the input cannot be neg or less that 0.5");
return 0;
}

area = (PI * radius * radius);
printf("The area of the circle for radius r %lf is = %lf\n", radius, area);
break;
case 'b':
printf("Enter the value for base and hieght\n")
if (scanf("lf%", &base) !=1 || scanf("%lf", height) !=1);
{
printf("invalid input")
return 0;
if (base < 0.5 || height < 0.5)
{print("the inputs cannot be negative numberer less than 0.5");
return; 
}
area = ( base * height )/2 
printf("The area of a triangle for base %lf and height %lf is = %lf\n", base, height, area);
break;
case 'B':
printf("Enter the value for base and hieght\n")
if (scanf("lf%", &base) !=1 || scanf("%lf", height) !=1);
{
printf("invalid input")
return 0;
if (base < 0.5 || height < 0.5)
{print("the inputs cannot be negative numberer less than 0.5");
return; 
}
area = ( base * height )/2 
printf("The area of a triangle for base %lf and height %lf is = %lf\n", base, height, area);
break;
case 'd':
printf("Enter the value for side \n";
if (scanf("%lf", &side) !=1) getting user input and cheek if side is number 
if (side < 0.5)
printf("the input cannot be negative or less than 0.5\n");
return; 
}
area = (side * 5 * apothem/2);

printf(" The are of the pentagon for side %lf is = %lf\n", side, area);
break;
case 'D':
printf("Enter the value for side \n";
if (scanf("%lf", &side) !=1) getting user input and cheek if side is number 
if (side < 0.5)
printf("the input cannot be negative or less than 0.5\n");
return; 
}
area = (side * 5 * apothem/2);

printf(" The are of the pentagon for side %lf is = %lf\n", side, area);
break;
case 'e';
break;
case 'E';
break;
default;
printf("Invalid input\n");
break;

}
}
return 0;

}




​
