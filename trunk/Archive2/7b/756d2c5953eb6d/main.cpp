#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    srand(time(nullptr));
    int counter = 0;
    
    for (int i = 0; i < 100; ++i)
    {
        int num = rand() % 100 + 1;
        if (num <= 25) { std::cout << "*"; ++counter; }
        else std::cout << " ";
    }
    
    std::cout << "\n" << counter;
}