#include <stdio.h>
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

void test()
{
    char s[1000];
    while (scanf("%s\n", s) != -1) {
        std::cout << s << " bah" << std::endl;
    }
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    test();
    std::cout << words << std::endl;
}
