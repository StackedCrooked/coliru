#include <iostream>
#include <thread>

class X {};

void F(X i) {
    std::cout << "test" << std::endl;    
}

int main() {
    X x;
    std::thread t1(F, x);
    t1.join();
}