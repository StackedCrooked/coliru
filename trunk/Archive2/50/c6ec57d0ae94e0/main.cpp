#include <iostream>

struct X {
    ~X() noexcept(false) { throw std::exception{}; }
};

int main()
{
    try {
        X x;
    }
    catch (std::exception& e)
    {
        std::cout << "Huehue!" << std::endl;
    }
}