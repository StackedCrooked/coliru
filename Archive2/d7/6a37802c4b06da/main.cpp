#include <boost/filesystem.hpp>
#include <iostream>

int main() {
    using namespace boost::filesystem;
    
    path fname("main.cpp");
    std::cout << "main.cpp" << "\n";
    std::cout << fname << "\n";
    std::cout << fname.c_str() << "\n";
}