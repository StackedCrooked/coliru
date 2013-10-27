#include <type_traits>
int main() {
    static_assert(std::is_assignable<int*, std::nullptr_t>(), "...");
}