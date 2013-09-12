#include <iostream>
#include <string>
#include <vector>
#include <iterator>

namespace ext {

    template <class T>
    auto size(const T &container) 
    -> typename std::iterator_traits<decltype(std::begin(container))>::difference_type {
        return std::distance(std::begin(container), std::end(container));
    }
    
    template <class T>
    bool is_empty(const T &container) {
        return size(container) == 0;   
    }
    
}

int main()
{
    std::vector<int> a(101, 1);
    std::cout << ext::size(a) << std::endl;
}
