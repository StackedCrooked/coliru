#include <type_traits>
#include <utility> 

struct S {
    private: void member();
};

template<typename T>
auto foo() -> decltype(std::declval<T>().member(), void()) {}

int main() {
    foo<S>();   
}