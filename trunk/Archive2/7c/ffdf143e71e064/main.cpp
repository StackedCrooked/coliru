#include <iostream>
#include <memory>

struct X
{
    ~X() { std::cout << "~X()" << std::endl; }
};

struct Y : X
{
    ~Y() { std::cout << "~Y()" << std::endl; }
};

int main()
{
    X* xp = new Y{};
    std::cout << "Deleting through raw pointer to base..." << std::endl;
    delete xp;

    std::shared_ptr<X> x{new Y{}};
    std::cout << "Deleting through shared pointer to base..." << std::endl;
}
