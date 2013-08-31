#include <iostream>
#include <iterator>
#include <sstream>

int main() {
    std::basic_stringbuf<unsigned char> buf;
    std::basic_istream<unsigned char> stream(&buf);
    // Uncomment to make work:
    //stream.unsetf(std::ios::skipws);
    std::istream_iterator<unsigned char, unsigned char> it(stream);
    
    std::cout << "Hello World!\n";
}