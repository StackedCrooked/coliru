#include <type_traits>

struct C { // Does not assert as POD class
    int value;

    C() = default;

    C(int v) : value(v) {
    }
};

static_assert(std::is_trivial<C>::value, ""); // Assert OK
static_assert(std::is_trivially_copyable<C>::value, ""); // Assert OK
static_assert(std::is_standard_layout<C>::value, ""); // Assert OK
static_assert(std::is_pod<C>::value, "");  // Assert fails. Why?

int main() {}