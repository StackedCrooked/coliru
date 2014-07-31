#include <iostream>
#include <string>
#include <vector>
#include <cstring>

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
    // nan pass thru
    float a;
    float b;
    int i =0x7ffffeed;
    memcpy(&a, &i, sizeof(a));
    b = 0.5f;
    a *= b;
    i=0;
    memcpy(&i, &a, sizeof(i));
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << std::hex << i << std::endl;
    i = 0x00400000;
    memcpy(&a, &i, sizeof(a));
    a*=b;
    memcpy(&i,&a,sizeof(i));
    std::cout << i << std::endl;
}