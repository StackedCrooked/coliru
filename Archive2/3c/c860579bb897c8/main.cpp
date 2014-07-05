#include <type_traits>

int main() {
    int i;
    const auto p = &i;
    
    static_assert(std::is_same<decltype(p), int * const>::value, "");
}