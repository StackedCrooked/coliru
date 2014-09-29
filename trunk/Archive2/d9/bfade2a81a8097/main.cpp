#include <type_traits>

struct test {};

test get() { return {}; }

template<typename T>
void set(T&&) { }

int main() {
    auto&& t = get();
    set(t); // why
    test&& x = get();
    set(x); // why
}
