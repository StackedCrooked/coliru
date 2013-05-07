#include <iostream>
#include <thread>

int main()
{
    std::thread t([]{
        std::cout << "Hello Thread!" << std::endl;
    });
    t.join();
}