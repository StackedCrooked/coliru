#include <iostream>
#include <thread>
#include <string>

int main()
{
    std::string c = "C++11" ; 
    std::thread t([&](){ std::cout << "Inside a lambda within a thread!!!\nYeah, its " << c; });
    t.join();
    return 0;
}
