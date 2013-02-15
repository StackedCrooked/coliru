#include <boost/range/adaptor/sliced.hpp>
#include <iostream>
#include <vector>

int main()
{
    using namespace boost::adaptors;
    
    std::vector<int> input { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    for (auto&& i : input | sliced(2, 5)) {
        std::cout << i << "\n";
    }

    return 0;
}