#include <iostream>
#include <thread>
#include <chrono>

struct A {
    std::thread t; 
    A()
    {
            t = std::thread{[](){ std::this_thread::sleep_for(std::chrono::seconds(5)); std::cout << "hi there"; }};
    }
    
    A(A&&) = default;
    
    ~A() { t.join(); }
};

A make_me_an_A() { 
    A a; 
    return a; 
}


int main() { 
    auto a = make_me_an_A(); 
    std::cout << "waiting..\n";
}