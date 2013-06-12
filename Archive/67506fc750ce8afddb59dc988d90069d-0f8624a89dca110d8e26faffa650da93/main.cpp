#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v1;
    std::vector<int> v2(100);
    
    std::cout << sizeof(v1) << std::endl;
    std::cout << sizeof(v2) << std::endl;
}
