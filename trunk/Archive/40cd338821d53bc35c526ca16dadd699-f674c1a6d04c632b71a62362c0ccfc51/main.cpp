#include <iostream>
#include <thread>
struct S {
   int i = 0;
   S() {}
};

thread_local S global;

int main()
{
    std::thread t1([](){global.i = 1; std::cout << global.i << std::endl;});
    t1.join();
    std::cout << global.i << std::endl;
    std::thread t2([](){global.i = 2; std::cout << global.i << std::endl;});
    t2.join();
    std::cout << global.i << std::endl;
    std::thread t3([](){global.i = 3; std::cout << global.i << std::endl;});
    t3.join();
    std::cout << global.i << std::endl;
}