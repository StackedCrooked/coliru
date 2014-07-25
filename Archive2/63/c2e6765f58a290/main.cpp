#include <iostream>
#include <string>
#include <map>
#include <random>
 
int main()
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 1);
    
    auto restos = { "Latina", "Piri piri" };
    std::cout << restos[dist(rd)] << std::endl;
    
    return 0;
}