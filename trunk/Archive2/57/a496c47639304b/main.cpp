#include <type_traits>

int main() {
    int i;
    int &r = i;
    
    static_assert(std::is_reference<decltype(i)>::value, "i");
    static_assert(std::is_reference<decltype(r)>::value, "r");
}