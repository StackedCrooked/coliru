#include <cstddef>
#include <iostream>
#include <vector>

namespace xstd {
  inline namespace literals {
    inline namespace support_literals {
      constexpr size_t operator "" _z(unsigned long long u) 
      { return static_cast<std::size_t>(u); }       
      
      constexpr ptrdiff_t operator "" _t(unsigned long long u) 
      { return static_cast<std::ptrdiff_t>(u); }        
    }
  }
}

int main()
{
    using namespace xstd::support_literals;

    auto v = std::vector<int> { 98, 03, 11, 14, 17 };
    for (auto i = 0_z, s = v.size(); i < s; ++i) 
        std::cout << i << ": " << v[i] << '\n';
}
