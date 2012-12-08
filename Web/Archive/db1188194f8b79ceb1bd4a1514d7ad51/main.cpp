#include <vector>
#include <array>
#include <iostream>
#include <type_traits>

template<bool b>
struct my_enabler {
  static constexpr std::nullptr_t value = nullptr;  
};
template<>
struct my_enabler<false> {
};

template<typename T, std::nullptr_t = my_enabler<std::is_same<T, int>::value>::value>
void foo(T t) {
}

int main() {
    foo(5);
}