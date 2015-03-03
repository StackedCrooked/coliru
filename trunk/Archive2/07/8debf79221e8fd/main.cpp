#include <iostream>

struct test {
    template<typename T>
    friend T& do_thing(T& out, const test& t, int);
};

template<typename T>
T& do_thing(T& out, const test& t, int x) {
    return out << "test: " << x << '\n';
}

int main() {
    do_thing(std::cout, test{}, 10) << "hello\n";
}