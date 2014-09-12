#include <memory>
#include <type_traits>

template<typename T>
struct S {
      
};

namespace std {
    template<typename T>
    struct is_copy_constructible<S<T>> : is_copy_constructible<T> {};
}

int main() {
    static_assert(std::is_copy_constructible<S<int>>::value, "");   
    static_assert(!std::is_copy_constructible<S<std::unique_ptr<int>>>::value, "");
}