#include <iostream>

template<typename T>
struct X : T
{
    void foo()
    {
        std::cout << this->x;
    }
};

struct Y
{
    int x = 42;
};

int main()
{
    X<Y> x;
    x.foo();
}