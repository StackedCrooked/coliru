#include <stdio.h>
#include <math.h>

double epsilon = 1e-15;

double myexp(double x) {
    double old_r = 0;
    double r = 1 + x;
    double div = 1;
    double i = 1;
    double m = x;
    while (fabs(1 - r / old_r) > epsilon) {
       div *= ++i;
       m *= x;
       old_r = r;
       r += m / div;
    }

    return r;
}

double mylog(double x) {
    static const double e = 2.718281828459045;
    int n = 0;
    while (fabs(x) >= 1) {
        x /= e;
        ++n;
    }

    x -= 1;
    double r = x;
    double m = x;
    double old_r = 0;
    double div = 1;
    double signal = 1;
    while (fabs(1 - r / old_r) > epsilon) {
       m *= x;
       old_r = r;
       signal *= -1;
       r += signal * m / ++div;
    }   
    return n+r;
}

int main() {
    printf("exp(1) = %.15f\n", exp(1));
    printf("exp(10) = %.15f\n", exp(10));
    printf("log(exp(10)) = %.15f\n", log(exp(10)));
    printf("sqrt(2) = %.15f\n", log(0.5*exp(2)));
    printf("--\n");
    printf("exp(1) = %.15f\n", myexp(1));
    printf("exp(10) = %.15f\n", myexp(10));
    printf("log(exp(10)) = %.15f\n", mylog(myexp(10)));
    printf("sqrt(2) = %.15f\n", mylog(0.5*myexp(2)));
}