#include <iostream>
#include <set>

int main() 
{
    std::set<double> myVec {1, 3, 5, 7, 9, 8, 6, 4, 2, 0,};
    for(auto i: myVec)
        std::cout << i << ' ';
    std::cout << '\n';
}