#include <type_traits>

struct f{};
struct g : f {};

int main() {
    static_assert(std::is_pod<g>(), "..");
}