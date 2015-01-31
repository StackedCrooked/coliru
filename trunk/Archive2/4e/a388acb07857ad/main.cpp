#include <random>
#include <iostream>
 
int main()
{
    std::mt19937 gen (std::random_device{}());
    std::uniform_int_distribution<> dis(1, 6);
 
    for (int n=0; n<10; ++n)
        std::cout << dis(gen) << ' ';
    std::cout << '\n';
}