#include <vector>
#include <iostream>
int main()
{
    std::vector<unsigned> vu{1,2,3};
    
    for(auto n : vu)
        std::cout << n << ' ';
}