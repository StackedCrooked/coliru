#include <iostream>
#include <functional>


void capture(const std::function<void(int)> & f)
{
    f(3);
}


void foo(int n)
{
    std::cout << "foo called with " << n << std::endl;
}


int main()
{
    capture(&foo);
}