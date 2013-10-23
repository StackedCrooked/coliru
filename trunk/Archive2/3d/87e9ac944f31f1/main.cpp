#include <iostream>
#include <thread>

int main()
{
    std::thread th([] { std::cout << "Hello, World\n"; });
    th.join();
}