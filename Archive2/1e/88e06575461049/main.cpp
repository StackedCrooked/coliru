#include <iostream>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <cctype>

int main() {
    std::istringstream input("Pre-release Alpha Beta Gamma abAb");
    std::ostringstream output;

    bool do_toupper{}, was_space{true};
    std::for_each(std::istreambuf_iterator<char>{input}, std::istreambuf_iterator<char>{}, [&](char c) {
        if(do_toupper) {
            output.put(std::toupper(c));
        } else {
            output.put(c);
        }

        if(was_space && c == 'A') {
            do_toupper = true;
        } else if(was_space) {
            do_toupper = false;
        }
        was_space = c == ' ';
    });

    std::cout << output.str() << std::endl;
}