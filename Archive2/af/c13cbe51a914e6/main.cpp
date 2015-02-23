#include <iostream>
#include <thread>

struct A {
    std::thread t; 
    A() 
    {
            t = std::thread{[](){ std::cout << "hi there"; }};
    }
    
    ~A() { t.join(); }
};


int main() { 
    A a; 
}