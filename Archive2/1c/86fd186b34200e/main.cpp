#include <iostream>
#include <type_traits>

template<bool C, typename T = void> struct enable_if {};
template<typename T> struct enable_if<true, T> { using type = T; };

template<typename ...T> struct Types;
template<> struct Types<> { };

template<typename HEAD, typename ...TAIL>
struct Types<HEAD, TAIL...> {
    HEAD head;
    Types<TAIL...> tail;
};

template<typename T>
struct Special { };

template<typename T>
struct IsSpecial {
    static constexpr bool val = false;
};

template<typename T>
struct IsSpecial<Special<T>> {
    static constexpr bool val = true;
};

template<typename ...T> bool has_special_type(Types<T...> &t);
template<> bool has_special_type<>(Types<> &t) { return false; }

template<typename HEAD, typename ...TAIL>
typename enable_if<IsSpecial<HEAD>::val, bool>::type
has_special_type(Types<HEAD, TAIL...> &t) {
    return true;
}

template<typename HEAD, typename ...TAIL>
typename enable_if<!IsSpecial<HEAD>::val, bool>::type
has_special_type(Types<HEAD, TAIL...> &t) {
    return has_special_type<TAIL...>(t.tail);
}

int main() {
    Types<int, bool, Special<float>, short> t1;
    Types<int, bool, float, short> t2;
    
    std::cout << "Hi";

    if (has_special_type(t1))
        return 0;
    else
        return 1;
}