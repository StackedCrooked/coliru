#include <string>
#include <iostream>
#include <utility>

struct A {
    std::string s;
    
    A() {}
    
    A(A const& other) {
        s = other.s;
        std::cout << "copy construct" << std::endl;  
    }
    
    A(A&& other) {
        std::swap(s, other.s);
        std::cout << "move construct" << std::endl;   
    }
    
    A& operator=(A const& other) {
        s = other.s;
        std::cout << "copy assign" << std::endl;
        
        return *this;
    }
    
    A& operator=(A&& other) {
        std::swap(s, other.s);
        std::cout << "move assign" << std::endl;
        
        return *this;
    }
};

struct B {
    A a;
    
    explicit B(A& a) : a(a) {}
    explicit B(A&& a) : a(std::move(a)) {};
    
    template<typename T>
    void someMethod(T && t) { a = std::forward<T>(t); };
};
 
int main()
{
    A a;
    B b1{ a };
    B b2{ A() };
    
    b1.someMethod(a);
    b1.someMethod(A());
}