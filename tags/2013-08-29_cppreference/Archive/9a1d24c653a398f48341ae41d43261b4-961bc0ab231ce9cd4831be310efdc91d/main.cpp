#include <boost/dynamic_bitset.hpp>
#include <numeric>
#include <iostream>

using bs = boost::dynamic_bitset<>;

int main()
{
    std::cout << std::accumulate(
            std::istream_iterator<bs>(std::cin), {}, 
            std::string{}, [](std::string& accum, bs bits) {
                do accum.insert(accum.begin(), (bits & bs(bits.size(), 0xFF)).to_ulong());
                while ((bits>>=8).count());
                return accum;
            });
}
