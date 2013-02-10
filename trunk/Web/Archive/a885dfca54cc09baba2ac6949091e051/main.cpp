#include <iostream>
#include <memory>
#include <utility>
#include <type_traits>

template <typename T>
struct remove_type {
    using type = void;
};

template <typename T>
using RemoveType = typename remove_type<T>::type;

template <typename T>
struct remove_type<T*> {
    using type = RemoveType<T>*;
};

static_assert(std::is_same<RemoveType<int*>, void*>(), "It works for T*");
static_assert(std::is_same<RemoveType<int**>, void**>(), "It works for T**");
static_assert(std::is_same<RemoveType<int***>, void***>(), "It works for T***");
static_assert(std::is_same<RemoveType<int******>, void******>(), "It works for T******");
    
int main () {
}