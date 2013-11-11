
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    std::vector<int> ints;
    
    std::back_insert_iterator<std::vector<int>>  it(ints);

    *it = 10; // it is equivalent to ints.push_back(10);
    
    std::cout << ints[0] << std::endl; //10
}