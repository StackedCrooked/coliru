#include <iostream>
#include <boost/shared_ptr.hpp>
#include <vector>
#include <typeinfo>

int main ()
{
    std::vector<unsigned int> vec {1, 2, 3, 4, 5};
    boost::shared_ptr<std::vector<unsigned int>> swList (new std::vector<unsigned int>(vec));
    
    char valueStringV[5] = {'a', 'b', 'c', 'd', 'e'};
    
    auto a = 5;
    
    for(unsigned int i = 0; i < swList->size(); i++)
    {
        snprintf(valueStringV, sizeof(valueStringV) - 1, swList->at(i), a);
    }
    std::cout << "type of swList->(o) is: " << typeid(swList->at(0)).name();
}