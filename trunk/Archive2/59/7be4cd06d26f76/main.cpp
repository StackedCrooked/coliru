#include <iostream>

struct parent {
    void fun() const {
        std::cout << "parent::fun()" << std::endl;
    }
};

struct foo : parent {
    void fun() const {
        std::cout << "foo::fun()" << std::endl;
    }
};

auto main() -> int {
    foo f;
    f.fun();
    f.foo::fun();
    f.parent::fun();

    return 0;
}