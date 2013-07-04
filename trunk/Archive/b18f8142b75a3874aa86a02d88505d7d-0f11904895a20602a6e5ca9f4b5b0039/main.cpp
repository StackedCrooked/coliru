#include <iostream>

bool i = false;

bool fuck() {
    bool done = true;
    return (done && (i = true));
}

int main() {
    bool x = fuck();
    
    std::string s = "x: ";
    s += (x) ? "true" : "false";
    
    std::string s2 = "i: ";
    s2 += (i) ? "true" : "false";
    
    std::cout << s << std::endl;
    std::cout << s2 << std::endl;
}