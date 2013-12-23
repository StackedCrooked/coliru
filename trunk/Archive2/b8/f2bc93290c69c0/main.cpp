#include <iostream>

struct S
{
    int i;
    float x;

    constexpr S(int j) : i{j} {}
};    

int main()
{
    constexpr S a(1);
}