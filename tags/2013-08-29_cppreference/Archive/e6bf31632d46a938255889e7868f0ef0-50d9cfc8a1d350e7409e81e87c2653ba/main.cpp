#include <iostream>
#include <boost/range/begin.hpp>

namespace bar {
    struct foo {
        using iterator = int*;
        using const_iterator = const int*;
    };
    
    void begin() {
        std::cout << "hello" << std::endl;
    }
}

int main() {
    bar::foo f;
    boost::begin(f);
}