#include <iostream>
#include <vector>
#include <string>
#include <boost/tokenizer.hpp>

int main()
{
    std::cout << "Enter: ";
    std::string x;
    // getline(std::cin, x);
    x = "#include <stdio.h>"; // since coliru doesn't take input

    // keep <, >, and ", drop whitespace
    boost::char_separator<char> sep(" \t", "#<>\"");
    boost::tokenizer<boost::char_separator<char>> tokens(x, sep);
    std::vector<std::string> v(tokens.begin(), tokens.end());
    if(v.size() == 5)
        std::cout << "directive: " << v[0] << v[1] << '\n'
                  << "header file name: " << v[3] << '\n'
                  << "delimiters: " << v[2] << v[4] << '\n';
}
