#include <algorithm>
#include <functional>
#include <iostream>
#include <string> 

struct S {
    std::string s{"abcdef"};
    
    char foo(char) {return 'A';}
    void bar() {
        std::transform(std::begin(s), std::end(s), std::begin(s), std::bind(&S::foo, this, std::placeholders::_1));
        std::cout << s;
    }
};

int main() {
    S s;
    s.bar();
}