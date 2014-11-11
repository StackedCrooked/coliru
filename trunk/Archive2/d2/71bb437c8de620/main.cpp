#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values;
    values.insert( values.end(), {1, 2, 3, 4, 5} );
    
    for (auto i : values)
        std::cout << i << ", ";
}
