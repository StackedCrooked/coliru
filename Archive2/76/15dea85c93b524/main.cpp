#include <iostream>
long double operator"" _N(long double a) { return a; }

int main(int argc, char** argv) {
    long double t = 4.0_N;
}
