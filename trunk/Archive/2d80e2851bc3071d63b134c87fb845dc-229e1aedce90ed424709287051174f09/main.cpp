#include <iostream>
#include <thread>

int main()
{
    std::cout << "Hello aaa " << __VERSION__ << "!" << std::endl;
    std::thread t([](){ std::cout << "Hello Thread!"; });
    t.join();
}