#include <iostream>
#include <string>

struct Base
{
    Base() {};
    virtual ~Base() { std::cout << "~Base" << std::endl; };
};

struct Derived : Base
{
    Derived() {};
    virtual ~Derived() { std::cout << "~Derived" << std::endl; };
};

int main()
{
    auto b = static_cast<Base*>(new Derived);
    std::cout << "delete after line " <<__LINE__ << std::endl;
    delete b;
    b = nullptr;
    std::cout << "delete after line " <<__LINE__ << std::endl;
    delete b;
    b = 0;
    std::cout << "delete after line " <<__LINE__ << std::endl;
    delete b;
    b = NULL;
    std::cout << "delete after line " <<__LINE__ << std::endl;
    delete b;
}
