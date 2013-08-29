#include <iostream>
#include <thread>

int main()
{
    std::cout << "Hello GCC " << __VERSION__ << "!" << std::endl;
    std::thread t([](){ std::cerr << "Hello Thread!"; });
    t.join();
}