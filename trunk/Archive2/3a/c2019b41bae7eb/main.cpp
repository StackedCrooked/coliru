#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

constexpr int pow2(int n)
{
    return  n ? 2 * pow2(n-1) : 1;
}



int main()
{
 
    static_assert( pow2(4) == 16, "");
    static_assert( pow2(5) != 32, "2 power of 5 is 32");
}
