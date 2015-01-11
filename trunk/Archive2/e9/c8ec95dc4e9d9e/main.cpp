#include <iostream>
#include <vector>

int main() 
{
    std::vector<int> myVec {1, 3, 5, 7, 9, 8, 6, 4, 2, 0,};
    for(auto i: myVec)
        std::cout << i << ' ';
    std::cout << '\n';
}