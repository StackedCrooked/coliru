#include <iostream>
#include <memory>

class foo {
public:
    // dit is de destructor
    ~foo() {
        std::cout << "~foo();\n";
    }
};

class bar {
public:
    // dit is de destructor
    ~bar() {
        std::cout << "~bar();\n";
    }
};

class baz {
public:
    // dit is de destructor
    ~baz() {
        std::cout << "~baz();\n";
    }
};

int main() {
    // auto is net als var in C#.
    
    auto a = new foo;
    auto b = new bar;
    std::unique_ptr<baz> c{new baz};
    
    delete a;
    // oops! b wordt nooit gedeleted!
    // c wordt gedeleted want smart pointer gaat out of scope
}
