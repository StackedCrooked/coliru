#include <iostream>
#include <type_traits>

namespace lib {
#if DEFINE_A
class A;
#endif
}

namespace {
    struct local_tag;
    using A = local_tag;
}

namespace lib {
    template <typename T = void>
    A is_a_defined();
}

constexpr bool A_is_defined = !std::is_same<local_tag, decltype(lib::is_a_defined())>::value;

int main() {
    std::cout << "A is " << (A_is_defined ? "" : "not ") << "defined.\n";
}
