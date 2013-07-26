#include <iostream>
#include <vector>

int main()
{
    std::vector<bool> bools(10, true);
    
    for(auto b : bools)  std::cout << std::boolalpha << b << " ";
    
    std::cout << "\n";
    
    for(auto b : bools)  b = false;
    
    for(auto b : bools)  std::cout << std::boolalpha << b << " ";
}
