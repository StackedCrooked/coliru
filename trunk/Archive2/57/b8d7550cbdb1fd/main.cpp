#include <iostream>
#include <unordered_map>
#include <utility>
#include <boost/range/irange.hpp>

int main()
{
    auto print = [](auto const& m) {
        std::cout << "size: " << m.size() << '\n';
        std::cout << "load_factor: " << m.load_factor() << '\n';
        std::cout << "max_load_factor: " << m.max_load_factor() << '\n';
        std::cout << "bucket_count: " << m.bucket_count() << '\n';
    };
    
    std::unordered_multimap<int, int> m;
    print(m);
    
    m.max_load_factor(8);
    print(m);
    
    for(auto i : boost::irange(0,100)) {
        m.insert(std::make_pair(0, i));
    }
    
    print(m);
}
