#include <type_traits>

template<typename T>
constexpr bool is_pointer{std::is_pointer<T>::value};

template<>
constexpr bool is_pointer<bool> {false};

template<>
constexpr bool is_pointer<bool *> {true};

//WORKS
//template<typename T>
//constexpr bool foo{std::is_pointer<T>::value};

//DOESN'T WORK
template<typename T>
constexpr bool foo{is_pointer<T>};

int main() {
    auto x = foo<bool>;
    auto y = foo<bool*>;
}