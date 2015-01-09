#include <algorithm>
#include <iostream>
#include <string>

// Quiz: we sorted PI ...but how come it compiles without "using namespace std;"?

int main()
{
    std::string pi = "3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679";
    sort(begin(pi), end(pi));
    std::cout << pi;
}