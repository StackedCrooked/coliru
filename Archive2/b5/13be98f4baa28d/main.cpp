#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>

int main() {
    // added consecutive tokens for illustration
    std::string text = "ls -a && echo test && pwd";    
    boost::char_separator<char> sep(" ", "&"); // specify only the kept separators
    boost::tokenizer<boost::char_separator<char>> tokens(text, sep);
    for (std::string t : tokens) { std::cout << "[" << t << "]" << std::endl; }
}
