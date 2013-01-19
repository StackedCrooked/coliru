#include <iostream>
#include <thread>
#include <cstdlib>

int main()
{
    srand(0);
    std::cout << rand() << '\n';
    std::cout << rand() << '\n';
    
    std::thread th([]
    {
        srand(0);
        std::cout << rand() << '\n';
    });
    th.join();
    
    std::cout << rand() << '\n';
}