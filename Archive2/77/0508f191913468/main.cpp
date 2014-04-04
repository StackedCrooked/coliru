#include <string>
#include <iostream>

struct A {
    std::string s;
    
    A() {}
    
    A(A const& other) : s(other.s) {
        std::cout << "copy construct" << std::endl;
    }
    
    A(A&& other) : s(std::move(other.s)) {
        std::cout << "move construct" << std::endl;
    }
};

struct B {
    A a;
    
    explicit B(A a) : a(std::move(a)) {}
};
 
int main()
{
    A a;
    B b1{ a };
    A b2{ A() };
}