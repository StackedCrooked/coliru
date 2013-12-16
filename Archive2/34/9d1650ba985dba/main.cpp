#include <memory>

struct with_copy {
    with_copy() = default;
    with_copy(with_copy const&) {}
};

struct foo {
    with_copy c;
    std::unique_ptr<int> p;
};

int main() {
    foo a;
    foo b = std::move(a);
}