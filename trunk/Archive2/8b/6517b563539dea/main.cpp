#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <deque>

void reversedString(const std::string& in) {
    std::istringstream iss (in);
    std::deque<std::string> words;
    std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::front_inserter(words));
    std::copy(std::begin(words), std::end(words), std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << std::endl;
}

int main() {
    reversedString("This is a sentence");
    reversedString("Program");
    reversedString("You are great");
    return 0;
}