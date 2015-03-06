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

constexpr int validate()
{   
    return 1;
}

constexpr int pow2(int num)
{   
    return num == 0 ? 1 : 2*pow2(num -1) & validate();
}


int main()
{ 
    static_assert(pow2(5) != 32, " 2 pow of 5 is 32");      
}
