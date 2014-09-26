#include <iostream>
#include <string>

struct proxy {
    proxy(std::string* arg) : inner{arg} { }
    
    proxy& operator=(char c) {
        (*inner)[2] = c;
        return *this;
    }
    
    std::string* inner;
};

proxy magic(std::string& arg) {
    return {&arg};
}

int main() {
    std::string test = "abcdef";
    magic(test) = 'x';
    std::cout << test << "\n";
}