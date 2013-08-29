#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>


template<typename T>
std::ostream& operator<<(std::ostream & os, const std::vector<T> & vec)
{
    os << "[ ";
    for (const auto & v : vec)
    {
        os << v << " ";
    }
    return os << "]";
}

int main()
{
    std::vector<unsigned> numbers(100);
    std::iota(numbers.begin(), numbers.end(), 1);    
    std::cout << numbers << std::endl;
}
