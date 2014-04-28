#include <iostream>
#include <string>

struct test {
    std::string name;
    
    // lua function I want
    int function(char c) {
        return name.length(); // invalid
    }
};

// function pointer that lua wants
using func_ptr = int(*)(char);

int main() {
    // not allowed
    func_ptr f = &test::function;
}