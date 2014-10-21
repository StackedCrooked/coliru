#include <iostream>
#include <boost/bind.hpp>

template <typename FooType> struct Foo {
    const FooType tmp_value;

    Foo(const FooType &tmp_) : tmp_value(tmp_) {}

    typedef void result_type;
    template <typename Object> result_type operator()(Object &operand) {
        std::cout << operand << std::endl;
        operand += tmp_value;
    }
};

int main() {

    double t = 4.0;
    Foo<double> e(1.0);
    std::cout << t << std::endl;
    e(t); // Works
    std::cout << t << std::endl;

    double d = 5.0;
    Foo<double> p(1.0);
    auto f1 = boost::bind(p, _1); // Blows up at compile

    std::cout << d << std::endl;
    f1(d);
    std::cout << d << std::endl;
}
