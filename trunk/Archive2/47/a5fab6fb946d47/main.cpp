#include <type_traits>

int main() {
    int * a0;

    auto a1 = a0;
    auto * a2 = a0;
    static_assert(std::is_same<decltype(a1), decltype(a0)>::value, "ouch");
    static_assert(std::is_same<decltype(a2), decltype(a0)>::value, "ouch");

    auto const a3 = a0;
    static_assert(std::is_same<decltype(a3), std::add_const<decltype(a0)>::type>::value, "ouch");

    auto * const a4 = a0;
    static_assert(std::is_same<decltype(a4), std::add_const<decltype(a0)>::type>::value, "ouch");

    const auto * a5 = a0;
    static_assert(std::is_same<decltype(a5), std::add_pointer<std::add_const<std::remove_pointer<decltype(a0)>::type>::type>::type>::value, "ouch");
}
