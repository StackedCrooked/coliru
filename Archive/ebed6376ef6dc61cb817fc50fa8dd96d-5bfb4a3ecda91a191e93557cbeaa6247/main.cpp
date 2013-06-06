#include <iostream>
#include <string>

template<typename Head, typename... Tail> 
struct AllStdString {
    constexpr static bool value = AllStdString<Head>::value && AllStdString<Tail...>::value;
};

template<typename T>
struct AllStdString<T> {
    constexpr static bool value = std::is_convertible<T, std::string>::value;
};

template<typename... Ts>
void foo(Ts...) {
    static_assert(AllStdString<Ts...>::value, "Not all std::string");
}

int main() {
    foo("hi", "bye");   
    foo(5);
}