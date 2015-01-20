struct target {
    int somevalue;
    target() = default;
    target(float f) : somevalue(static_cast<int>(1024*f)) {}
};

#include <type_traits>
#include <boost/type_traits.hpp>
static_assert(std::is_pod<target>::value,   "expected to be POD");
static_assert(boost::is_pod<target>::value, "expected to be POD");

#include <iostream>

int main() {
    target t = 3.14f;
    std::cout << t.somevalue << "\n";
}
