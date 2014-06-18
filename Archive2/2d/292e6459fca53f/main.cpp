#include <stdio.h>
#define PI 3.14159265

int main(int argc, const char * argv[])
{

    // insert code here...
   // printf("Hello, World!\n");

    float radius, diameter, area, circumference;

    printf("\n Enter the diameter of the circle\n");
    scanf("%f",&diameter);

    radius=diameter/2.0;

    circumference= 2.0*PI*radius;
    area=PI*(radius)*(radius);

    printf("\n The area of the circle is: %.2f\n", area);
    printf("\n The circumference of the circle is: %.2f\n", circumference);



    return 0;
}