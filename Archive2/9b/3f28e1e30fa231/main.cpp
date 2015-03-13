#include <algorithm> 
#include <cstdlib> 
#include <iostream> 
#include <vector>
 
int main() 
{
    std::vector<int> srcVec; 
    for (int val = 0; val < 10; val++)
    { 
        srcVec.push_back(val); 
    }
 
    std::for_each(srcVec.begin(), srcVec.end(), [](int a){ std::cout << a << std::endl; }); 
}