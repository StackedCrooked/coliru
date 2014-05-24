#include <iostream>
#include <vector>

#include <boost/range/iterator_range.hpp>
#include <boost/iterator/zip_iterator.hpp>

template<typename... T>
auto zip(T&... containers) {
    return boost::make_iterator_range(
        boost::make_zip_iterator(boost::make_tuple(std::begin(containers)...)),
        boost::make_zip_iterator(boost::make_tuple(std::end(containers)...))
    );
}

int main() {
    std::vector<std::vector<double>> v = {
        { 0.1, 1.1, 2.1, 3.1 },
        { 0.2, 1.2, 2.2, 3.2 },
        { 0.3, 1.3, 2.3, 3.3 }
    };
    
    for (auto t : zip(v[0], v[1], v[2])) {
        std::cout << t.get<0>() + t.get<1>() + t.get<2>() << std::endl;
    }
    
    return 0;
}