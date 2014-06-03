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

#include <string>
#include <iostream>

template<typename T>
typename std::enable_if<typelist<int,char,std::string>::contains<T>(), T>::type
myFunc(T data) {
    std::cout << data << '\n';
    return data;
}

int main() {
    myFunc(1);
    myFunc('1');
    myFunc(std::string("1"));
    // myFunc(1.f); // fail, float
}
