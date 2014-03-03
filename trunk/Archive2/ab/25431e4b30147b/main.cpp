//Title of this code

#include <iostream>
#include <string>
using namespace std;

int& getReference()
{
    int x = 33;
    return x;
}

int main()
{
    auto a = getReference() = 4;
    auto b = getReference();

    std::cout << "a: " << a << " b: " << b;
    return 0;
}