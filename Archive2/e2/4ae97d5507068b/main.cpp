#include <iostream>
#include <type_traits>

#if DEFINE_A
class A;
#endif

namespace {
    struct local_tag;
    using A = local_tag;
}

namespace foo {
    template <typename T = void>
    ::A is_a_defined();
}

constexpr bool A_is_defined = !std::is_same<local_tag, decltype(foo::is_a_defined())>::value;

int main() {
    std::cout << "A is " << (A_is_defined ? "" : "not ") << "defined.\n";
}
