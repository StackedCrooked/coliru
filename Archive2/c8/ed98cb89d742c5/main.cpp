#include <iostream>

struct X {
    ~X() noexcept(false) { throw std::exception{}; }
};

void foo()
{
    X x;
}

int main()
{
    try {
        foo();
    }
    catch (std::exception& e)
    {
        std::cout << "Huehue!" << std::endl;
    }
}