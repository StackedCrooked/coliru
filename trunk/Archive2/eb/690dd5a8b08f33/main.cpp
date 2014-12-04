#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <functional>
#include <exception>


class foo {
public:

    foo() : x_(0) { std::cout << "foo constructor\n"; }
    foo(foo& c) : x_(c.x_) { std::cout << "foo copy- constructor\n"; }
    
    foo& operator=(foo const& c) {
        std::cout << "foo operator=\n";
        x_ = c.x_;
        return *this;
    }
    
protected:
    int x_;
};

class bar : public foo {
public:
    
    bar(int x) { foo::x_=x; std::cout << "bar constructor\n"; }
    bar(bar& c) { std::cout << "bar copy- constructor\n"; }
    
    bar& operator=(bar const& c) {
        foo::operator=(c);
        std::cout << "bar operator=\n";
        return *this;
    }
};

int main() {    
    
    foo f;
    bar b(123);
    
    std::cout << "f = *static_cast<foo*>(&b);\n";
    f = *static_cast<foo*>(&b); // no copy constructor is called
    std::cout << "f = static_cast<foo>(b);\n";
    f = static_cast<foo>(b); // copy constructor and assignment is called
}