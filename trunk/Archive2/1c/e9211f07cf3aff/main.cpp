#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int value = 34; 
    std::vector<int> ivec{ 3, 3, 43, 456, 34, 435,7 }; 
    
    auto result = std::find(ivec.begin(), ivec.end(), value); 
    std::cout << "The Value " << value << (result == ivec.end() ? " is not present" : " is present") << std::endl;
}
