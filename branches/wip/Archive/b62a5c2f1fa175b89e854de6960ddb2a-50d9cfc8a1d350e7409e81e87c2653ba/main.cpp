#include <iostream>
#include <thread>
#include <mutex>

void print(const std::string& str)
{
    static std::mutex fMutex;
    std::lock_guard<std::mutex> lock(fMutex);
    std::cout << str << std::endl;
}

int main()
{
    print("hi");
}