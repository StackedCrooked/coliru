#include <algorithm>
#include <iostream>
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
    std::vector<unsigned> numbers;
    std::generate_n(std::back_inserter(numbers), 100, [](){ static unsigned n; return ++n; });
    std::cout << numbers << std::endl;
}
