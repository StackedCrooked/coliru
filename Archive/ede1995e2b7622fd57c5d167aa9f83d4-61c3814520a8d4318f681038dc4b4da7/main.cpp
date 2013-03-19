#include <iostream>
#include <functional>


class Test {
public:
    Test() { std::cout << "Test()" << std::endl; }
    Test(const Test& rhs) {
        std::cout << "Test(const Test&)" << std::endl;
        std::cout << "   this: " << this << std::endl;
        std::cout << "   &rhs: " << &rhs << std::endl;
    }
    Test(Test&&) { std::cout << "Test(Test&&)" << std::endl; }
    
    Test& operator = (const Test&) {
        std::cout << "Test::operator=(const Test&)" << std::endl;
        return *this;
    }
    
    Test& operator = (Test&&) {
        std::cout << "Test::operator=(Test&&)" << std::endl; 
        return *this;
    }
    
    Test& operator()() {
        std::cout << "Test::operator()" << std::endl << std::endl;
        return *this;
    }
};


Test& DoSomething(std::function<Test&()> func) {
    return func();
}


int main() {
    Test& foo = DoSomething([&foo]() -> Test& {
        std::cout << "In lamba: " << &foo << std::endl;
        return foo;
    });
    
    std::cout << "In main: " << &foo << std::endl;
}