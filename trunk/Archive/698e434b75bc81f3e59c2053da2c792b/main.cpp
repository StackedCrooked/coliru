#include <algorithm>
#include <iostream>
#include <vector>


template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> & c)
{
    for (auto i : c)
    {
        os << i << " ";
    }
    return os;
}


int main()
{
    {
        std::vector<int> vec = { 1, 2, 1 };
        std::cout << vec << std::endl;
        
        vec.erase(remove(begin(vec), end(vec), 1), end(vec));
        std::cout << vec << std::endl;
    }
    
    std::cout << std::endl;
    
    {
        std::vector<int> vec = { 1, 2, 1 };
        std::cout << vec << std::endl;
        
        vec.erase(remove_if(begin(vec), end(vec), [](int n){ return n == 1; }), end(vec));
        std::cout << vec << std::endl;
    }
}