#include <iostream>
#include <thread>

int main()
{
    std::cout << "Hello GCC " << __VERSION__ << "!" << std::endl;
    std::thread t([](){ std::cout << "Hello Thread 1"; });
    std::thread t2([](){ std::cout << "Hello Thread 2"; });
    std::thread t3([](){ std::cout << "Hello Thread 3"; });
    t.join();
    t2.join();
    t3.join();
}