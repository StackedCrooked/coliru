#include <iostream>
#include <thread>

int main()
{
    std::cout << "Hello GCC " << __VERSION__ << "!" << std::endl;
    std::thread t([](){ std::cout << "Hello Thread!"; });
    
    std::cout << "Consegue enxergar isso? Manda no skype se conseguir" << std::endl;
    t.join();
}