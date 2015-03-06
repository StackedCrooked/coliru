#include <iostream>
#include <vector>
#include <unordered_map>
#include <boost/functional/hash.hpp>
#include <chrono>

namespace std
{
    template<typename Container>
    struct hash {
            std::size_t operator()(Container const& v) const
            {
                return boost::hash_range(v.begin(), v.end());
            }
    };
}

int main()
{

    std::unordered_map<std::vector<double>, double> test;

    unsigned long t = (unsigned long) std::chrono::system_clock::now().time_since_epoch().count();
    std::srand(t);
    for (uint i = 0; i < 100 ; ++i)
    {
        double d1 = i/200.0;
        double d2 = i/200.0;
        std::vector<double> v({d1, d2});
        test[v] = d1;
    }

    std::cout << "Size:" << test.size() << std::endl;
    for (const auto& it : test )
    {
        std::cout << it.first[0] << ":" << it.second << std::endl;
    }

    return 0;
}