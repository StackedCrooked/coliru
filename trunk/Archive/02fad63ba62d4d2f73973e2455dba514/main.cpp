#include <iostream>
#include <typeinfo>
#include <type_traits>

template <typename Out, typename In>
Out f_impl(In x) {
    std::cout << "f<" << typeid(Out).name() <<
                 ", " << typeid(In).name() <<
                 ">(" << x << ")\n";
    return x;
}

template <
    typename Out,
    typename In,
    typename = typename std::enable_if<not std::is_same<Out, In>::value>::type
>
Out f(In x) {
    std::cout << "f<Out, In>(x):\t ";
    return f_impl<Out, In>(x);
}

template <typename T>
T f(T x) {
    std::cout << "f<T>(x):\t ";
    return f_impl<T, T>(x);
}


int main() {
    f(42);
    f<float>(42);
    f<int>(42);
}