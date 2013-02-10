#include <iostream>
#include <memory>
#include <utility>
#include <type_traits>

template <typename T>
struct remove_type {
    using type = void;
};

template <typename T>
struct remove_type<T*> {
    using type = typename remove_type<T>::type*;
};

static_assert(std::is_same<typename remove_type<int*>::type, void*>(), "It works for T*");
static_assert(std::is_same<typename remove_type<int**>::type, void**>(), "It works for T**");
static_assert(std::is_same<typename remove_type<int***>::type, void***>(), "It works for T***");
static_assert(std::is_same<typename remove_type<int******>::type, void******>(), "It works for T******");
    
int main () {
}