#include <iostream>
#include <thread>

void f() { std::cout << "Hello "; }
struct F {
    void operator()() { std::cout << "Parallel World!\n"; }
};

void user()
{
    std::thread t1 {f}; // f() executes in separate thread
    std::thread t2 {F()}; // F()() executes in separate thread
    t1.join(); // wait for t1
    t2.join(); // wait for t2
}

int main()
{
    user();
}