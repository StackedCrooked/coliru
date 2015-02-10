#include <cstddef>
#include <iostream>
#include <vector>



namespace std {
inline namespace literals {
inline namespace support_literals {
    constexpr size_t operator "" _z(unsigned long long u) {
        return static_cast<size_t>(u);    
    }
    //constexpr ptrdiff_t operator "" _t(unsigned long long);        
}}}

using namespace std::literals::support_literals;

int main()
{
    auto v = std::vector<int> { 98, 03, 11, 14, 17 };
    for (auto i = 0_z, s = v.size(); i < s; ++i) { 
        std::cout << i << " en ook: " << v[i] << std::endl;
    }
}
