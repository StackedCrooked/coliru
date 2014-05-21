#include <iostream>
#include <unordered_map>
#include <utility>
#include <boost/range/irange.hpp>
#include <boost/range/iterator_range.hpp>

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
    
    m.max_load_factor(2);
    print(m);
    
    for(auto i : boost::irange(0, 100)) {
        m.insert(std::make_pair(0, i));
    }
    
    print(m);
    
    // print all values
    for(auto const& kv : m) {
        std::cout << kv.second << ' ';
    }
    std::cout << '\n';
    
    // print value for bucket with key 0
    auto bucket = m.bucket(0);
    for(auto const& kv : boost::make_iterator_range(m.begin(bucket), m.end(bucket))) {
        std::cout << kv.second << ' ';
    }
    std::cout << '\n';
}
