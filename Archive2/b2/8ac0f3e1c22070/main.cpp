#include <iostream>
#include <boost/signals2.hpp>

int foo(double) {
    return 1;
}

struct Queer {
    int operator()(double) {
        return 3;
    }
};

int main() {
    boost::signals2::signal<int(double)> sig;
    sig.connect(foo);
    sig.connect([](double) {
        return 2;
    });
    sig.connect(Queer());
    std::cout << *sig(40.0) << "\n";
}