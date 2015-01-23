#include <iostream>
#include <string>
#include <vector>

using fptr_t = int (*)(int);

std::vector<fptr_t> vec;

int foo(int x)
{
    vec.push_back(&foo);
    return x;
}

int main()
{
    std::cout << (unsigned long)(&foo) << ' ';
    foo(5);
    std::cout << (unsigned long)(vec.front());
}
