#include <iostream>
#include <string>
struct X {
    std::string x;
    std::string y;
    ~X() { std::cout << "~X()" << std::endl; }
};

X f() { return {"foo", "bar"}; }

int main() {
    const std::string & x = f().x;
    std::cout << x << std::endl;
}

