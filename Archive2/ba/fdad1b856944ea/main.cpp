#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;

template<typename T>
void wtfdump(const std::string &title, T&& value)
{
    union {
        T wtf;
        char c[sizeof(T)];
    } wtf;
    
    wtf.wtf = value;
    
    std::cout << title << " size: " << dec << sizeof(T) << " 0x";
    
    std::vector<char> wtfrev;
    std::copy(std::begin(wtf.c), std::end(wtf.c), std::back_inserter(wtfrev));
    std::reverse(wtfrev.begin(), wtfrev.end());
    for (auto i : wtfrev) {
        std::cout << hex << setfill('0') << setw(2) << (unsigned int)(unsigned char)i;
    }
    std::cout << std::endl;
}

int main()
{
 
    enum A{a=9223372036854775808,b=~9223372036854775808 + 1, c=65536};

    wtfdump("a", a);
    wtfdump("b", b);
    wtfdump("c", c);
    
    wtfdump("int", 10);
 
}