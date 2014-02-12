#include <iostream>
#include <thread>

void f() { int j = 0; for(int i = 0; i < 10; ++i) j++; std::cout << "Hello " << j << '\n'; }
struct F {
    void operator()() { int j = 0; for(int i = 0; i < 1000000; ++i) j++; std::cout << "Parallel World! " << j << '\n'; }
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