#include <stdio.h>

double exp(double x) {
    double r = 1 + x;
    r += (x*x)/2;
    r += (x*x*x)/6;
    r += (x*x*x*x)/24;
    r += (x*x*x*x*x)/120;
    r += (x*x*x*x*x*x)/720;
    r += (x*x*x*x*x*x*x)/5040;
    r += (x*x*x*x*x*x*x*x)/40320;
    r += (x*x*x*x*x*x*x*x*x)/3628800;
    return r;
}

double log(double x) {
    static const double e = exp(1);
    int n = 0;
    while (x > 1) {
        x /= e;
        ++n;
    }
    x -= 1;
    double r = x;
    r -= (x*x)/2;
    r += (x*x*x)/3;
    r -= (x*x*x*x)/4;
    r += (x*x*x*x*x)/5;
    r -= (x*x*x*x*x*x)/6;
    r += (x*x*x*x*x*x*x)/7;
    r -= (x*x*x*x*x*x*x*x)/8;
    r += (x*x*x*x*x*x*x*x*x)/9;
    r -= (x*x*x*x*x*x*x*x*x*x)/10;
    r += (x*x*x*x*x*x*x*x*x*x*x)/11;
    return n+r;
}

int main() {
    printf("exp(1) = %f\n", exp(1));
    printf("log(exp(10)) = %f\n", log(exp(10)));
    printf("sqrt(2) = %f\n", log(0.5*exp(2)));
}