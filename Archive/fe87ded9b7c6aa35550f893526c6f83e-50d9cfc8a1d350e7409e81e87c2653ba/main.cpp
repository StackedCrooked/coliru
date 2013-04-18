#include <stdio.h>
#include <math.h>
double inputValues();
double quadratic();

int main()
{
        inputValues();
        inputValues();
        inputValues();
        return 0;
}

double inputValues()
{
        double a, b, c,derp;

        printf("Enter a value a: ");
        scanf("%lf", &a);

        printf("Enter a value b: ");
        scanf("%lf", &b);

        printf("Enter a value c: ");
        scanf("%lf", &c);

        derp = quadratic(a, b, c);

        printf("One x-value for this equation is %0.3f: \n", derp);
        return 0;
}

double quadratic(double a, double b, double c)
{
        double quad;

        quad = (-b + sqrt(b*b-4*a*c))/(2*a);
        return quad;
}