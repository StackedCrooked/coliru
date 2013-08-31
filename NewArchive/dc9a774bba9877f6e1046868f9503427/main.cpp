#include <iostream>
#include <thread>
#include <string>

void greeting(const std::string& message)
{
    std::cout << message << std::endl;
}

int main()
{
    std::cout << "Hello GCC " << __VERSION__ << "!" << std::endl;
    //std::thread t([](){ std::cout << "Hello Thread!"; });
    std::thread t(greeting, "Hello guys");
    t.join();
}