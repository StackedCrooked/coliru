#include<iostream>
#include<string>
#include <regex>

int main() {
    const std::string str = "1.0.0.0029.443";
    if ( std::regex_match( str, std::regex( "\\.0\\d+" ) ) )
        std::cout << "regex_match() matched." << std::endl;
    if ( std::regex_search( str, std::regex( "\\.0\\d+" ) ) )
        std::cout << "regex_search() matched." << std::endl;
}