#include <iostream>

int main()
{
    auto genLambda = [](auto param) {std::cout << __VERSION__;};
    genLambda(2);
}