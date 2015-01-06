#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

namespace fs = boost::filesystem; 

#include <iostream>

int main() {
    for (fs::recursive_directory_iterator b("."), e; b!=e; ++b) {
        if (fs::is_regular_file(*b))
            std::cout << b->path() << "\n";
    }
}

