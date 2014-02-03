#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include <climits>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}



template<typename T>
constexpr T roundup(T value, unsigned maxb = sizeof(T)*CHAR_BIT, unsigned curb = 1)
{
    return maxb<=curb ? value : roundup( ((value-1)|((value-1)>>curb))+1, maxb, curb << 1 );
}

template<typename T>
constexpr T Log2(T n, T p = 0)
{
    return (n <= 1) ? p : Log2(n / 2, p + 1);
}



int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    for (int i = 0; i < 17; i++)
        std::cout << i << " -> " << Log2(i) << "\n";
}
