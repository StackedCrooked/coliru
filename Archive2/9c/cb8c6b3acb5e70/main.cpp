#include <iostream>

struct X
{
    ~X() { };
};

int main()
{
    X x;

    // This will not fire even in GCC 4.7.2 if the destructor is
    // explicitly marked as noexcept(true)
    static_assert(noexcept(x.~X()), "Ouch!");
    
    std::cout << "I'm still ok!";
}
