#include <boost/iostreams/device/mapped_file.hpp>
#include <fstream>
#include <iostream>

namespace io = boost::iostreams;

int main() {
    // of course, prefer `stat(1)` or `boost::filesystem::file_size()`, but for exposition:
    std::streamsize const length = std::distance(std::istreambuf_iterator<char>(std::ifstream("main.cpp").rdbuf()), {});
    
    io::mapped_file mf("main.cpp", io::mapped_file_base::mapmode::priv, length+1);

    *(mf.end()-1) = '\0'; // voilà, null termination done, safely, quickly and reliably

    std::cout << length << "\n";
    std::cout << mf.size() << "\n";
}
