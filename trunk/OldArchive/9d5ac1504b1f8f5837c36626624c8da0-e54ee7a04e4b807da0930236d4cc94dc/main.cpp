#include <type_traits>

template <typename T>
struct inherit_one : T {
    using base = T;
};

template <typename T>
std::true_type test_inheritance(typename inherit_one<T>::base*);
template <typename>
std::false_type test_inheritance(...);

struct foo {};
struct bar final {};

static_assert(decltype(test_inheritance<foo>(nullptr))(), "");
static_assert(!decltype(test_inheritance<bar>(nullptr))(), "");

int main() {}
