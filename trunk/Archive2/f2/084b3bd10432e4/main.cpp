#include <cstdio>
#include <iostream>
#include <unordered_set>
#include <memory>

namespace ns
{
    
struct my_int
{
    int d;
};

inline bool operator==(const my_int& a, const my_int& b)
{
   std::cout << "Koenig Lookup!" << std::endl;
    return a.d == b.d;
}

}

namespace std
{
    template <>
    struct hash<ns::my_int>
    {
        std::size_t operator()(const ns::my_int& m) const { return inthash(m.d); }
        
        std::hash<int> inthash;
    };
}

inline bool operator==(const ns::my_int& a, const ns::my_int& b)
{
    std::cout << "Hmm" << std::endl;
    return a.d == b.d;
}

int main(int argc, char* argv[])
{    
    int a = 2;
    a = ++a + a++;
    std::cout << a << std::endl;
    return 0;
}