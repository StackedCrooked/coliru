#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <typeinfo>
#include <functional>
#include <algorithm>

using namespace std;

struct NullType { };

template <typename H, typename T> struct TypeList {
    using Head = H;
    using Tail = T;
};

#define TYPELIST_1(T) TypeList<T, NullType>
#define TYPELIST_2(T, U) TypeList<T, TYPELIST_1(U)>
#define TYPELIST_3(T, U, V) TypeList<T, TYPELIST_2(U, V)>

template<typename TL> struct Length;
template<> struct Length<NullType> {
    static const int value = 0;
};
template<typename H, typename T> struct Length<TypeList<H, T>> {
    static const int value = Length<T>::value + 1;
};

template<typename TL, unsigned int index> struct TypeAt;
template<typename H, typename T> struct TypeAt<TypeList<H, T>, 0> {
    using type = H;
};
template<typename H, typename T, unsigned int index> struct TypeAt<TypeList<H, T>, index> {
    using type = typename TypeAt<T, index-1>::type;
};

int main() {
    using mylist = TYPELIST_3(int, float, double);
    static_assert(Length<mylist>::value == 3, "wrong!");
    static_assert(is_same<TypeAt<mylist, 1>::type, float>::value, "wrong 2!");
}
