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
constexpr T RuntimeLog2(T n)
{
	return 31 - __builtin_clz(n | 1);
}


template<typename T>
constexpr T ConstLog2(T n, T p = 0)
{
    return (n <= 1) ? p : ConstLog2(n / 2, p + 1);
}



int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    for (int i = 0; i < 17; i++)
        std::cout << i << " -> Log2Runtime = " << RuntimeLog2(i) << ",  ConstLog2 = " << ConstLog2(i) << "\n";
}
