#include <cstddef>

int main() {
    const volatile std::nullptr_t&& x = []()->std::nullptr_t{ return{}; }();
}