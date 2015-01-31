#include <iostream>
#include <string>
#include <vector>

#pragma STDC FENV_ACCESS 

#define FUNCTION(name, a) \
    int fun_##name() \
    { return a;} /* foobar */
#define ABC 1

#ifdef ABC // comment
#endif

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
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << 0xfa0e0bcll << std::endl;
}
