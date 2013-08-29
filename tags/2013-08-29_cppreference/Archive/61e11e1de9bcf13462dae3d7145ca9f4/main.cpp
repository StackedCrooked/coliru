#include <iostream>
#include <thread>

t() { 
    std::cout << "Hello Thread!"; 
}

int main()
{
    std::cout << "Hello GCC " << __VERSION__ << "!" << std::endl;
    std::thread t();
    t.join();
}