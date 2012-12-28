#include <iostream>
#include <vector>
#include <algorithm>

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

int main() {
    std::vector<int> v(100);
    std::iota(v.begin(),v.end(),1);
    std::cout << v;
}