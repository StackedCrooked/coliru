#include <vector>

int main() {
    struct foo {
        foo() = default;
        ~foo() = default;
        foo(const foo&) = delete;
        foo(foo&&) = delete;
        foo& operator = (const foo&) = delete;
        foo& operator = (foo&) = delete;
    };
    std::vector<foo> x;
}
