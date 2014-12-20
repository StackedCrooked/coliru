#include <sstream>
#include <string>
#include <thread>
#include <iostream>

int main()
{
    std::istringstream ss("lol");
    std::string out;
    
    std::thread t([&]() {
        ss >> out;
    });
    t.join();
    std::cout << out << '\n';
}