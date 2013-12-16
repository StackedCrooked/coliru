#include <iostream>

// The initial code here fails to compile.
// Theory (IANASL): the compiler is only looking up
// typenames in the immediate namespace (N).
// I don't know why.

// Move these two definitions into N to compile
struct Inner { int value; };
struct Outer { Inner inner; };

namespace N {

template<typename R, typename T>
R get_value (T& x) {
    return get_value<R>(x.inner);
}

template<typename R>
R get_value(Inner& x) {
    return x.value;
}

} // namespace N

int main() {
    // Also uncomment this:
    //using N::Outer;
    Outer x = {{ 42 }};
    std::cout << N::get_value<int>(x);
}
