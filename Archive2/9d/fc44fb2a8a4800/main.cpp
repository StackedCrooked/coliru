#include <iostream>
#include <typeinfo>

class test {
    public:
    test(){};
    };

int main() {
    auto x = []{ return 123; };
    std::cout << typeid(x).name() << std::endl;
    test t;
    std::cout << typeid(t).name() << std::endl;
}