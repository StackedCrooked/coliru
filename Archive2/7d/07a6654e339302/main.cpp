#include <iostream>
#include <string>
#include <vector>

#define FOO [](int n){ return n; }

using fptr_t = int(*)(int);

void foo(fptr_t fptr = FOO)
{
    std::cout << std::uintptr_t(fptr) << '\n';
}


int main()
{
    foo();
    foo();
    foo();
}
