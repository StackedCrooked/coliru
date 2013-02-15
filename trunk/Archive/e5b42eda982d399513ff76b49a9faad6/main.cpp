#include <iostream>
#include <thread>

int main()
{
    crap
    std::cout << "Hello GCC2 " << __VERSION__ << "!" << std::endl;
    std::thread t([](){ std::cout << "Hello Thread!"; });
    t.join();
}