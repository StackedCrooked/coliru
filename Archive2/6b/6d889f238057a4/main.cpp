#include <sstream>
#include <iostream>
#include <string>

int main () {
    std::stringstream in;
    in << "   abc";
    
    std::stringstream out(in.str());
    std::string str;
    
    out >> std::ws >> str;
    
    std::cout << str;
}