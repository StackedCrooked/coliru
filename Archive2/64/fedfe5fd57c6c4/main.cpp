#include <type_traits>

struct test {};

test get() { return {}; }
void set(test&&) { }

int main() {
    auto&& t = get();
    set(t); // why
    test&& x = get();
    set(x); // why
}
