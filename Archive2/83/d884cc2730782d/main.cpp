#include <iostream>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <cctype>

int main() {
    std::istringstream input("Alpha Beta Gamma");
    std::ostringstream output;

    bool do_toupper{};
    std::for_each(std::istreambuf_iterator<char>{input}, std::istreambuf_iterator<char>{}, [&](char c) {
        if(do_toupper) {
            output.put(std::toupper(c));
        } else {
            output.put(c);
        }

        if(c == ' ') {
            do_toupper = false;
        } else if(c == 'A') {
            do_toupper = true;
        }
    });

    std::cout << output.str() << std::endl;
}