#include <iostream>
#include <thread>


struct S
{
    S operator"" _s;
};
    

int main()
{
    std::cout << "Hello GCC " << __VERSION__ << "!!!!!" << std::endl;
    std::thread t([](){ std::cout << "Hello Thread!"; });
    t.join();
}