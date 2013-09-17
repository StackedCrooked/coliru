#include <type_traits>

void F1(int) {    
}

template <typename T = float>
void F2(int) {
    static_assert(std::is_integral<T>::value, "Don't call F2!");
}

int main() {
 F1(1);  
 F2(2); // Remove this call to compile
}