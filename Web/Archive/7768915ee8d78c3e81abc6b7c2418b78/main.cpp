#include <iostream>
#include <thread>

int main()
{
    std::cout << "Hello GCC " << __VERSION__ << "!" << std::endl;
    std::cout << "Hello GCC " << __VERSION__ << "!" << std::endl;
    std::cout << "Hello GCC " << __VERSION__ << "!" << std::endl;
    std::cout << "Hello GCC " << __VERSION__ << "!" << std::endl;
    std::cout << "Hello GCC " << __VERSION__ << "!aba" << std::endl;
    std::thread t([](){ std::cout << "Hello Thread!"; });
    t.join();//
}