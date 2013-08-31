#include <iostream>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <string>
#include <thread>


void print(const std::string & s)
{    
    // Thread safe?
    // I'm confused by this question: http://stackoverflow.com/questions/2955921/thread-safe-initialization-of-function-local-static-const-objects
    static std::mutex mtx;
    std::unique_lock<std::mutex> lock(mtx);
    std::cout <<s << std::endl;
}


int main()
{
    std::thread([&](){ for (int i = 0; i < 10; ++i) print("a" + std::to_string(i)); }).detach();
    std::thread([&](){ for (int i = 0; i < 10; ++i) print("b" + std::to_string(i)); }).detach();
    std::thread([&](){ for (int i = 0; i < 10; ++i) print("c" + std::to_string(i)); }).detach();
    std::thread([&](){ for (int i = 0; i < 10; ++i) print("d" + std::to_string(i)); }).detach();
    std::thread([&](){ for (int i = 0; i < 10; ++i) print("e" + std::to_string(i)); }).detach();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}