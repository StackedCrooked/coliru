#include <iostream>
#include <thread>

int main()
{
    std::cout << "Hello GCC " << __VERSION__ << "!" << std::endl;
    std::thread t([](){ std::cout << "Hello Thread!"; });
    std::thread u([](){ std::cout << "Hello sa!"; });
    t.join();
}