#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    std::vector<int> a { 4,9,4};
    std::vector<int> b { 1,2,3};
    
    std::transform( begin(a), end(a), begin(b), begin(b), []( int a, int b ) { return (a+b)%42; } );
    
    std::cout << b << std::endl;
}
