#include <type_traits>
#include <iostream>
#include <vector>
#include <map>
#include <string>

template<class T, class = void>
struct has_integer_subscript : std::false_type { };

template<class T>
struct has_integer_subscript<T, decltype(void(std::declval<T>()[1]))> : std::true_type { };

template<class T, class = void>
struct has_string_subscript : std::false_type { };

template<class T>
struct has_string_subscript<T, decltype(void(std::declval<T>().operator[]("")))> : std::true_type { };

template<class T>
typename std::enable_if<!has_integer_subscript<T>::value && !has_string_subscript<T>::value, void>::type f(T t) {
    std::cout << "none\n";
}

template<class T>
typename std::enable_if<has_integer_subscript<T>::value && !has_string_subscript<T>::value, void>::type f(T t) {
    std::cout << "integer\n";
}

template<class T>
typename std::enable_if<!has_integer_subscript<T>::value && has_string_subscript<T>::value, void>::type f(T t) {
    std::cout << "string\n";
}

template<class T>
typename std::enable_if<has_integer_subscript<T>::value && has_string_subscript<T>::value, void>::type f(T t) {
    std::cout << "both\n";
}

struct A {
    void operator[](int x) {}
    void operator[](std::string y) {}
};


int main(int argc, char **argv) {
    f(0);
    f(std::vector<int>());
    f(std::map<std::string, int>());
    f(A());
    return 0;
}