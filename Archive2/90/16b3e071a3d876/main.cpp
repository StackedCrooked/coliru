#include <type_traits>

template <typename...>
struct typelist {
    template <typename U>
    static constexpr bool contains() {
        return false;
    }
};

template <typename Head, typename...Tail>
struct typelist<Head, Tail...> {
    template <typename U>
    static constexpr bool contains() {
        return std::is_same<Head, U>::value || typelist<Tail...>::template contains<U>();
    }
};

template<typename T>
typename std::enable_if<typelist<int,double,float>::contains<T>(), T>::type
myFunc(T data) {
    return data + 2;
}

int main() {
    myFunc(1);   // okay, int
    myFunc(1.0); // okay, double
    myFunc(1.f); // fail, float
}
