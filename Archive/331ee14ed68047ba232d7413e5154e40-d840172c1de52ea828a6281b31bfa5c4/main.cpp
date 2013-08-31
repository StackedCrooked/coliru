#include <string>
#include <iostream>

std::string f(std::string&& a, std::string&& b) {
    std::string result;
    for(auto&& ch : a) {
        if(b.find(ch) != std::string::npos)
            result += ch;
    }
    return result;
}

int main() {
    std::cout << f("abcdef","foobar");
}