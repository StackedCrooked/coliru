#include <iostream>
#include <string>

#define show(variable) std::cout << #variable << " = " << variable << std::endl;

template <typename...> struct NumTypes;

template <typename T>
struct NumTypes<T> {
    static const int value = 1;
};

template <template <typename...> class P>
struct NumTypes<P<>> { static const int value = 0; };

template <template <typename...> class P, typename First, typename... Rest>
struct NumTypes<P<First, Rest...>> {
    static const int numInFirst = NumTypes<First>::value;
    static const int value = numInFirst + NumTypes<std::tuple<Rest...>>::value;
};

template <typename...> struct Pack;
template <typename...> struct Group;
template <typename...> struct Wrap;
struct Object {};

int main() {
    using A = Pack<int, Object, long>;
    show (NumTypes<A>::value)  // 3

    using B = Pack<int, bool, Pack<char, double>, long>;
    show (NumTypes<B>::value)  // 5

    using C = Group<int, bool, Wrap<char, Pack<char, long, Group<char, Object, short>, short>, double>, long>;
    show (NumTypes<C>::value)  // 11

    using D = Group<Pack<int, Object, double>, bool, Wrap<char, Pack<char, double, Group<char, Pack<char, long, short>, int, Object>, short>, double>, long>;
    show (NumTypes<D>::value)  // 16
    
    using E = Pack<std::string>;
    show (NumTypes<E>::value)  // 3
}