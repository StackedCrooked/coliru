#include <iostream>
#include <type_traits>
#include <vector>

template<typename C>
struct IsIterable
{
    typedef char true_type; 
    typedef long false_type; 
    
    template<class T> static true_type  is_beg_iterable(typename T::const_iterator = C().begin()); 
    template<class T> static false_type is_beg_iterable(...); 
    
    enum { value = sizeof(is_beg_iterable<C>()) == sizeof(true_type) }; 
};

int main()
{
    std::cout << IsIterable<std::vector<int>>::value << std::endl;
    //std::cout << IsIterable<std::vector<int>::value << std::endl;
}
