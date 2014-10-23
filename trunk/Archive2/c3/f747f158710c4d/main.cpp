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

auto increment = [](auto first1, auto last1, auto d_first, auto x, auto binary_op)
{
    while (first1 != last1) {
        *d_first++ = binary_op(*first1++,x);
    }
    return d_first;
};

auto concat = [] (auto i, auto j) {return i + j;};


int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    
    increment(words.begin(), words.end(), words.begin(), "!!!", concat);
    std::cout << words << std::endl;
}
