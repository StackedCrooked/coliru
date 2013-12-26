#include <stdio.h>

#include <math.h>
int main()
{
const float b=1.5;
float Q, x;
printf("Introduceti valoarea lui x = ");
scanf("%f", &x);
if (b*x<1.2)
Q = b*x-log(b*x);
else
if (b*x == 1)
Q = 1;
 else
Q = b*x+log(b*x);
printf("Q(%.2f) = %.2f\n", Q);
}
