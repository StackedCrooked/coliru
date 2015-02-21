#include <iostream>

union T{
    int y;
    struct A{ int i; A():i{1} {} } a;
};

int main()
{
    T t;
    std::cout << t.a.i << '\n';
}
