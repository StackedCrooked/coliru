#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdint>
 
int main()
{
    // read() is often used for binary I/O
    std::string bin = {'\x12', '\x12', '\x12', '\x12'};
    std::istringstream raw(bin);
    std::uint32_t n;
    raw.read(reinterpret_cast<char*>(&n), sizeof n);
    std::cout << std::hex << std::showbase << n << '\n';
 
    // prepare file for next snippet
    std::ofstream os("test.txt", std::ofstream::binary);
    for (unsigned i = 0; i < 10; i++) { // prepare stream
        os << "abcd" << i << "\n";
    }
    os.close();
 
    // read entire file into string
    std::ifstream is("test.txt", std::ifstream::binary);
    if (is) {
        // get length of file:
        is.seekg(0, is.end);
        int length = is.tellg();
        is.seekg(0, is.beg);
 
        std::string str;
        str.resize(length, ' '); // reserve space
        char* begin = &*str.begin();
 
        is.read(begin, length);
        is.close();
 
        std::cout << str << "\n";
    } else {
        std::cout << "Could not open test.txt\n";
    }
}