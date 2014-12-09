#include <vector>
#include <iostream>

template<class T>
using List = std::vector<T>;


int main()
{
    List<int> oi = { 1, 4, 8, 16 } ;
    std::cout << oi[2] << std::endl;
}