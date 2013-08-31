#include <iostream>
#include <string>
#include <vector>


void centerify_output(std::string str, int num_cols) {
    // Calculate left padding
    int padding_left = (num_cols / 2) - (str.size() / 2);
    
    // Put padding spaces
    for(int i = 0; i < padding_left; ++i) std::cout << ' ';
    
    // Print the message
    std::cout << str;
}


int main() {
    std::vector<std::string> lines = {
        "---------------------------------",
        "|                               |",
        "|                               |",
        "|         User : xyz            |",
        "|         Pass : ****           |",
        "|                               |",
        "|                               |",
        "---------------------------------",
    };
    
    int num_cols = 100;
    
    // VIRTUAL BORDER
    std::cout << std::endl;
    for(int i = 0; i < num_cols; ++i) std::cout << ' ';
    std::cout << '|' << std::endl;
    
    // OUTPUT
    for(int i = 0; i < lines.size(); ++i) {
        centerify_output(lines[i], num_cols);
        std::cout << std::endl;
    }
    
    // VIRTUAL BORDER
    std::cout << std::endl;
    for(int i = 0; i < num_cols; ++i) std::cout << ' ';
    std::cout << '|' << std::endl;
}