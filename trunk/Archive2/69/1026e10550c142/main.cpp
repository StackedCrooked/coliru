#include <iostream>

template<typename T>
struct Foo {
    Foo(T* f) : f_(f) {}
    void operator()(double x) const { *f_ = x; }
    mutable T* f_;
};

template<typename Callable>
Foo<Callable> make_mutable(Callable& c)
{
    return Foo<Callable>(&c);
}

int main() {
    double x = 2.3;
    const Foo<double> m = make_mutable(x);
    m(3.4);
    std::cout << x << "\n";
	return 0;
} 