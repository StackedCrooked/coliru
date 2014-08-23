#include <iostream>
#include <string>

class Foo {
public:
    void print_strings() { /* Do Nothing */ }
    
    template <typename... Args>
    void print_strings(std::string str, Args... args) {
        std::cout << str << ", ";
        print_strings(args...);
    }
    template <typename... Args>
    void print_prefix(std::string str, Args... args) {
        print_strings("prefix", str, args...);
    }
};

int main() {
    Foo foo;
    foo.print_prefix("Lel", "Wot", "Lelling");
}
