// kapitel016/userliterals03.cpp
#include <iostream>

void function(std::string& str) {
    str={"Referenz"};
    std::cout << &str << std::endl;
}

void function(std::string&& str) {
    str={"Verschieben"};
    std::cout << &str << std::endl;
}

int main() {
    std::string test("test");
    function(std::move(test));
    std::cout << &test << std::endl;
    std::cout << test << std::endl;
    function(test);
    std::cout << test << std::endl;    
}