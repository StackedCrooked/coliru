#include <iostream>

struct B { void* x; };

struct D : B { };
struct E : B { void* y; };
struct F : B { void* y; private: void* z; };
struct G : B { virtual void f() { } };
struct H : B { void* y; virtual void f() { } };

int main() {
    auto d = new D;
    auto e = new E;
    auto f = new F;
    auto g = new G;
    auto h = new H;
    std::cout << d << '\n' << static_cast<B*>(d) << '\n' << '\n';
    std::cout << e << '\n' << static_cast<B*>(e) << '\n' << '\n';
    std::cout << f << '\n' << static_cast<B*>(f) << '\n' << '\n';
    std::cout << g << '\n' << static_cast<B*>(g) << '\n' << '\n';
    std::cout << h << '\n' << static_cast<B*>(h) << '\n' << '\n';
}