#include <iostream>

int main () {
    auto lambda = [] () { int x; x = 2; x *= 3; std::cout << "x"; };
    auto copylambda = lambda;
    lambda();
    copylambda();
}