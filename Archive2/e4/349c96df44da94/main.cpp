// multimap::equal_range
#include <iostream>
#include <map>
#include <boost/shared_ptr.hpp>
#include <vector>

int main ()
{
    std::vector<unsigned int> vec {1, 2, 3, 4, 5};
    boost::shared_ptr<std::vector<unsigned int>> swList (new std::vector<unsigned int>(vec));
    
    char valueStringV[5] = {'a', 'b', 'c', 'd', 'e'};
    
    for(unsigned int i = 0; i < swList->size(); i++)
    {
        snprintf(valueStringV, sizeof(valueStringV) - 1, "%c", swList->at(i));
    }
    
}
