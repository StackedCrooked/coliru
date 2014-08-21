#include <functional>
#include <iostream>

template <typename T>
struct foo {
    std::function<void(T&, int)> f;
    
    template <typename K, void (K::*method)(T&, int)>
    void
    set(K* instance) {
        f = [&] (T& t, int i) { 
            (instance->*method)(t, i); 
        };
    }
};

struct bar {
    void fun(double& d, int i) {
        std::cout << d << ' ' << i << '\n';
    }
};

int
main() {
    foo<double> f;
    bar b;
    f.set<bar, &bar::fun>(&b);
    
    double d{3.14};
    f.f(d, 5);
}
    