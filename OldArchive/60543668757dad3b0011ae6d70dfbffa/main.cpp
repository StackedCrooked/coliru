#include <iostream>
#include <thread>

int main()
{
    std::cout << "Hello GCC " << __VERSION__ << "!" << std::endl;
    std::thread t([](){ std::cout << "Hello Thread!"; });
    t.join();
    
    for(int i = 0; i < 10;++i ) {
        std::cout << i << std::endl;
    }
}