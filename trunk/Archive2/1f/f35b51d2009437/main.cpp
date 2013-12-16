#include <memory>

struct with_copy {
    with_copy() = default;
    with_copy(with_copy const&) {}
    with_copy(with_copy&&) = delete;
};

int main() {
    with_copy x = with_copy();
}