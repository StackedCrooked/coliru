#include <type_traits>

struct A {
    static int foo(bool){ return 5;}    
};

int main() {
    std::result_of_t<decltype(A::foo)> a = 3;
    static_assert(std::is_same<decltype(a), int>, "ACK");
}
