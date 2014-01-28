#include <iostream>
#include <random>
 
int main()
{
    std::random_device rd;
    std::cout << rd.entropy() << '\n';
}