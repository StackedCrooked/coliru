#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <iostream>

namespace fs = boost::filesystem;

int main() {
    for (auto de : boost::make_iterator_range(fs::recursive_directory_iterator("."), {}))
        std::cout << de.path().filename() << "\n";
}
