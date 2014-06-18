#include <iostream>
#include <typeinfo>

class D {
    virtual ~D() {}
};
D &d;

int main()
{
    std::cout << typeid(d).name() << std::endl;
    std::cout << sizeof(d) << std::endl;
}