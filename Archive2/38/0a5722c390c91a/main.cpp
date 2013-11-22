#include <iostream>
#include <algorithm>
#include <cctype>

int main() {
    std::cout<<"Trial word: ";
    std::string input;
    const int max_length = 20;
    std::getline(std::cin, input);
    if (input.size() > max_length)
        std::cout << "error" << std::endl;

    // for demonstration purposes
    input = "hi";

    if (std::any_of(input.begin(), input.end(), [](char c) {
        return !islower(c) && !isalpha(c);
    }))
        std::cout << "invalid format" << input <<  std::endl;

    input = "hi%"; // contains symbol

    if (std::any_of(input.begin(), input.end(), [](char c) {
        return !islower(c) && !isalpha(c);
    }))
        std::cout << "invalid format" << input <<  std::endl;
    // output: invalid formathi%
    return 0;
}