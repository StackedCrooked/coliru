#include <iostream>
#include <thread>

int main()
{
    std::cout << "Hello GCC " << __VERSION__ << "!" << std::endl;
    std::thread t([](){ std::cout << "Hello Thread!"; });
    std::cout<<"hello world"<<std::endl;
    t.join();
}