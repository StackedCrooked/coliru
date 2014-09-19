#include <iostream>

template<typename>
void f() {
    std::cout << "hey!" << std::endl;   
}

struct A {
    friend void f<int>() { 
        std::cout << "fun!" << std::endl;    
    }
};

int main() {
    f<int>();   
}