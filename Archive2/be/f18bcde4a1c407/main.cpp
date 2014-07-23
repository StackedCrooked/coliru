#include <iostream>

struct My
{
   typedef int foo;
};

struct My2
{
};

template <typename T, typename I = typename T::foo>
void Bar(const T&, I z = I())
{
    (void)z; // silence any warnings on unused
    std::cout << "My" << std::endl; 
}

void Bar(...)
{
    std::cout << "..." << std::endl; 
}

int main() 
{
    My my;
    Bar(my); // OK
    My2 my2;
    Bar(my2); // Compile error: no type named ‘foo’ in ‘struct My2’
    return 0;
}