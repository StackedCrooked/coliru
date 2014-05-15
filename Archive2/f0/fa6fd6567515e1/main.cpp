#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v = { 1, 2, 3 };
    v.resize(v.size());
    std::cout << *(v.end()) << std::endl;
    
    return 0;
}