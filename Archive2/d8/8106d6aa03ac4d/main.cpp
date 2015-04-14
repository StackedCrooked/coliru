#include <iostream>
#include <typeinfo>

typedef const int volatile * const xyz;

int main()
{
    std::cout << typeid(xyz).name();
}
