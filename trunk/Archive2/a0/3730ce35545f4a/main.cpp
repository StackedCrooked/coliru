#include <iostream>


struct X
{
    X()  { std::cout << "CREATED   : " << this << std::endl; }
    ~X() { std::cout << "DESTROYED : " << this << std::endl; }
    X* operator&() { return this; }
};

int main()
{
    void *address = &X();
    std::cout << "ADDRESS : " << address << "  of temporary (destroyed already) " << std::endl;
}
