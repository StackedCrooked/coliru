#include <iostream>

template <class> struct delay;

struct Base {
    Base() = delete;
    
    Base(int) { std::cout << __PRETTY_FUNCTION__ << '\n'; }
};

struct D1 : virtual Base {
#ifdef WORK
    D1(int x) : Base(x) {} // should be exactly the same as synthesized constructor below
#else
    using Base::Base;
#endif
};

int main() {
    D1 d(5);
}