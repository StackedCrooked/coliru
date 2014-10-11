#include <vector>
#include <algorithm>
#include <iostream>
 
int main()
{
    std::vector<int> listInt{0,1,2,3};
    auto it = std::find(listInt.begin(), listInt.end(), 2);
    std::cout << std::distance(listInt.begin(),it) << std::endl;
}