#include <iostream>
#include <sstream>
#include <iterator>

void read2(std::istream_iterator<char>& it) {
    std::cout << *it++ << *it++ << "\n";
}

int main() {
    std::stringstream sstr;
    sstr << "012";
    std::istream_iterator<char> it(sstr);
    read2(it);
    return 0;
}