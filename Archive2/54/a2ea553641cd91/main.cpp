#include <type_traits>

struct bad {
    bad() noexcept(true) {}
    ~bad() noexcept(false) {}
};

static_assert(std::is_nothrow_constructible<bad>(), "destructor should not matter, should it?");

int main() {}
