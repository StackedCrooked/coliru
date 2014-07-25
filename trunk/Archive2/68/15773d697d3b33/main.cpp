#include <iostream>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <cctype>

int main() {
    std::istringstream input("Alpha Beta Gamma abAba AbAbA");
    std::ostringstream output;

    enum state { outside_word, in_word, in_word_to_upper };
    state current = outside_word;
    std::for_each(std::istreambuf_iterator<char>{input}, std::istreambuf_iterator<char>{}, [&](char c) {
        output.put(current == in_word_to_upper ? std::toupper(c) : c);

        if (c == ' ')
            current = outside_word;
        else if (current == outside_word)
            current = c == 'A' ? in_word_to_upper : in_word;
    });

    std::cout << output.str() << std::endl;
}