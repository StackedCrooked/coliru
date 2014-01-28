#include <type_traits>

int main() {
    int i;
    int &r1 = i, r2 = i;
    
    static_assert(std::is_same<decltype(r1), decltype(r2)>::value, "");
}