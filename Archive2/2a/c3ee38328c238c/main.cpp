#include <stdio.h>


double celsius_a_Farenheit (double grados)
{
    return (grados * 1.8 + 32);
}
double celsius_a_Kelvin (double kelvin)
{
	return (kelvin + 273);
}

int main (){
double t;
t=129.69;
printf ("Introduzca los Celsius a transformar\n");
scanf ("%lf", &t);
printf ("%.02lf celsius son %.02lf farh\n",t,celsius_a_Farenheit(t));
printf ("%.02lf celsius son %.02lf kelvin\n",t,celsius_a_Kelvin(t));

return 0;

}