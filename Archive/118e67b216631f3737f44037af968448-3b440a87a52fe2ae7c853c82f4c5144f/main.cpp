#include <type_traits> 

void foo(int (arr)[3]) {
    static_assert(std::is_same<decltype(arr), int *>::value, "They're not the same.");
}

int main() {
    
}