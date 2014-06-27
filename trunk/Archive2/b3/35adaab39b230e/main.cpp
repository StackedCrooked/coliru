#include <iostream>
#include <sstream>

int main() {
    std::stringstream ss;
    std::string sFilename;
    ss << "/tmp/abc";
    ss >> sFilename;
    std::cout << sFilename << std::endl;          // outputs "/tmp/abc"
    std::cout << sFilename.c_str() << std::endl;  // doesn't work??
}