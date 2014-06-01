#include <boost/filesystem.hpp>
#include <iostream>

namespace fs = boost::filesystem;

int main() {
    fs::path one("/usr/");
    fs::path two("/bin/");
    std::cout << (one / two).string() << '\n';
}