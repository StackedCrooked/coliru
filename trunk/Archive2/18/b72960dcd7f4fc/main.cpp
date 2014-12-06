#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    std::srand(std::time(nullptr));
    for(int i = 0; i < 10; ++i)
        std::cout << rand() % 100 << ' '; 
}