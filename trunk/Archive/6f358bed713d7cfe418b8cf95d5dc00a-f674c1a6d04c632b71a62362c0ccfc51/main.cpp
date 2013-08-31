#include <cstdio>

int main(int argc, char* argv[]) {
    double x = 20;
    double y = 1.0 / (1.0 / x);
    printf("%a and %a", x, y);
}