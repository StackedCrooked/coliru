#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    std::thread([](){
        std::cout << "BEGIN" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "END" << std::endl;
    }).detach();
}