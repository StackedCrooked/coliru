
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    std::vector<int> v;
    
    std::back_insert_iterator<std::vector<int>>  it(v);

    *it = 10; // it is equivalent to v.push_back(10);
    
    std::cout << v[0] << std::endl; //10
}