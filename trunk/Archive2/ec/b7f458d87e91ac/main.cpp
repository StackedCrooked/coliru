#include <iostream>
#include <string>
#include <map>
#include <random>
#include <vector>
 
int main()
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 1);
    
    std::vector<std::string> restos = { "Latina", "Piri piri" };
    std::cout << restos[dist(rd)] << std::endl;
    
    return 0;
}