#include <iostream>
#include <thread>

void func1(int&&) { std::cout << "func1\n"; }
void func2(int&) { std::cout << "func1\n"; }



int main() {
    int x = 3;
    std::thread t1(func1, x); // compiles
    t1.join();
    // std::thread t2(func2, x); // fails to compile
    // t2.join();
}