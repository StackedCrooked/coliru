#include <boost/filesystem.hpp>
#include <iostream>

namespace fs = boost::filesystem;

int main() {
    auto p = fs::current_path();
    fs::recursive_directory_iterator it(p);
    auto end = decltype(it)();

    for(; it != end; ++it) {
        std::cout << it->path().string() << '\n';
    }
}