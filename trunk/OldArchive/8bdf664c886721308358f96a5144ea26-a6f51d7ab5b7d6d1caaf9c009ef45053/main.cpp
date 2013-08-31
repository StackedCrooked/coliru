#include <iostream>

struct A{};
struct B : public A{};

int main()
{
    B * ptr= nullptr;
    if(dynamic_cast<A*>(ptr) == nullptr)
        std::cout << "yes" << std::endl; 
}