#include <string>
#include <iostream>

template<class Type>
void function(const Type& t) {
    std::cout << t;
}

template<>
void function(const std::string&) = delete;

int main() {
    function(1);
    function(std::string("ok"));
}