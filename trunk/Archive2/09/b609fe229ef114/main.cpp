#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v(5, 0);
    
    std::cout << v.size() << std::endl;
    auto x = v.back();
    std::cout << v.size() << " " << x << std::endl;
    
    return 0;
}