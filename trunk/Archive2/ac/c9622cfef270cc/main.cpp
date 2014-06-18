#include <type_traits>

struct point { int x; int y; };

int main() {
    static_assert(std::is_class<point>{}, "...");
}