
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    std::vector<int> v;
    
    std::back_insert_iterator<std::vector<int>>  it(v);

    *it = 10; //it is equivalent to v.push_back(10);
     it = 99; //it is ALSO equivalent to v.push_back(99);
    
    for (auto const & i : v)
        std::cout << i << " " ; //10 99
    
}