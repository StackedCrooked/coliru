#include <iostream>
#include <iterator>
#include <sstream>

int main() {
    std::basic_stringbuf<unsigned char> buf;
    std::basic_istream<unsigned char> stream(&buf);
    // Woo bad cast!
    std::istream_iterator<unsigned char, unsigned char> it(stream);
}