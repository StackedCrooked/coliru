#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>

int main()
{
    std::stringbuf sb1("aaaaabbbbbccccc");

    for (int i = 0; i < 3; ++i) {
        std::string hello;

        std::copy_n(std::istreambuf_iterator<char>(&sb1),
                    5,
                    std::back_inserter(hello));

        std::cout << hello << std::endl;
    }

    std::stringbuf sb2("aaaaabbbbbccccc");

    for (int i = 0; i < 3; ++i) {
        std::string hello;

        std::istream is(&sb2);
        std::copy_n(std::istream_iterator<char>(is),
                    5,
                    std::back_inserter(hello));

        std::cout << hello << std::endl;
    }
}