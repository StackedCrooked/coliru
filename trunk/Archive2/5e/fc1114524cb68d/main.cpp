#include <iostream>

struct Blah
{
    Blah() = delete;
    int i;
    float j;
};

int main()
{
    auto b = Blah{1,2.0};
    std::cout << b.i << '\n';
}