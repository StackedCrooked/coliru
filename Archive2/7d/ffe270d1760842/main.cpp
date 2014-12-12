#include <sstream>
#include <iostream>
#include <string>

int main()
{
    std::stringstream ss;
    ss << "lol\nyes\npartial";
    
    std::string line;
    while (std::getline(ss, line)) {
        if (ss.eof()) {
            std::cerr << "Got partial line: " << line << '\n';
        }
        else {
            std::cerr << "Got full line: " << line << '\n';
        }
    }
    
    const bool has_more = ss.eof();
    
    ss.clear();
    if (has_more)
        ss << line;
    
    std::cerr << "---\n";
    
    ss << "more\n";
    
    std::string line2;
    while (std::getline(ss, line2)) {
        if (ss.eof()) {
            std::cerr << "Got partial line: " << line2 << '\n';
        }
        else {
            std::cerr << "Got full line: " << line2 << '\n';
        }
    }
}