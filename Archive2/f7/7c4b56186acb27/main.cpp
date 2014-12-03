#include <atomic>
#include <iostream>
#include <cassert>

template <typename T>
using shared_ref = std::atomic<T const*>;

struct Base       { virtual void f() const = 0; };
struct Foo : Base { virtual void f() const { std::cout << __PRETTY_FUNCTION__ << "\n"; } };
struct Bar : Base { virtual void f() const { std::cout << __PRETTY_FUNCTION__ << "\n"; } };

static constexpr Foo foo = {};
static constexpr Bar bar = {};

int main() {

    shared_ref<Base> vinterface(&foo);

    auto const& itf1 = vinterface;
    auto const& itf2 = vinterface;

    itf1.load()->f();
    itf2.load()->f();

    vinterface.store(&bar);

    itf1.load()->f();
    itf2.load()->f();
}