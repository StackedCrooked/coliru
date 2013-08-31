#include <iostream>
#include <functional>
#include <type_traits>

/* specialization for zero argument functions */
template<typename R>
std::function<R()> curry(std::function<R()> f) {
    return f;
}

/* specialization for single argument functions */
template<typename R, typename A>
std::function<R(A)> curry(std::function<R(A)> f) {
    return f;
}

namespace
{
    template<typename T> struct curry_t {};

    template<typename R, typename A>
    struct curry_t<R(A)>
    {
        using type = std::function<R(A)>;
    };

    template<typename R, typename Head, typename Tail>
    struct curry_t<R(Head, Tail)>
    {
        using type = std::function<std::function<R(Tail)>(Head)>;
    };

    template<typename R, typename Head, typename Body, typename... Tail>
    struct curry_t<R(Head, Body, Tail...)>
    {
        using type = std::function<
            std::function<typename curry_t<R(Tail...)>::type (Body)>(Head)
            >;
    };
}

template<typename R, typename Head, typename Tail>
auto curry(std::function<R(Head, Tail)> f)
-> std::function<std::function<R(Tail)>(Head)> {
    return [f](Head&& h) {
        return [f, h](Tail&& t) {
            return f(h, t);
        };
    };
}

namespace
{
    /* SFNIAE helper struct for type extraction of lambdas */
    template<typename T> struct remove_class {};
    template<typename R, typename C, typename... A>
        struct remove_class<R(C::*)(A...)> { using type = R(A...); };
    template<typename R, typename C, typename... A>
        struct remove_class<R(C::*)(A...) const> { using type = R(A...); };
}

/* forward declaration of where the magic happens */
template<typename R, typename Head, typename Body, typename... Tail>
auto curry(std::function<R(Head, Body, Tail...)> f)
-> typename curry_t<R(Head, Body, Tail...)>::type;

/* specialization for lambda functions and other functors */
template<typename F>
auto curry(F f) 
-> decltype(curry(std::function<typename remove_class<
    decltype(&std::remove_reference<F>::type::operator())
    >::type>(f))) {
    return curry(std::function<typename remove_class<
            decltype(&std::remove_reference<F>::type::operator())
            >::type>(f));
}

template<typename R, typename Head, typename Body, typename... Tail>
auto curry(std::function<R(Head, Body, Tail...)> f)
-> typename curry_t<R(Head, Body, Tail...)>::type {
    return [f](Head&& h) {
        return curry([f, h](Body b, Tail... t) {
            return f(h, b, t...);
        });
    };
}

/* specialization for function pointers */
template<typename R, typename... A>
auto curry(R(*f)(A...))
-> decltype(curry(std::function<R(A...)>(f))) {
    return curry(std::function<R(A...)>(f));
}

int add(int a, int b) {
    return a+b;
}

int add4(int a, int b, int c, int d) {
    return a + b + c + d;
}

int main() {
    auto mult3 = curry([](int x, int y, int z) { return x*y*z; });
    auto something = [](int a, int b, int c, int d, int e, int f)
                     { return a*b*c+d*e*f; };

    std::cout << "               14 + 1 = "
              << curry(add)(14)(1) << std::endl
              << "            1 * 3 * 5 = "
              << mult3(1)(3)(5) << std::endl
              << "        1 + 2 + 4 + 8 = "
              << curry(add4)(1)(2)(4)(8) << std::endl
              << "    1 + 2 + 3 + 4 + 5 = "
              << curry(
                       [](int a, int b, int c, int d, int e)
                       { return a+b+c+d+e; }
                      )(1)(2)(3)(4)(5) << std::endl
              << "1 * 2 * 3 + 1 * 3 * 3 = "
              << curry(something)(1)(2)(3)(1)(3)(3)
              << std::endl;

    return 0;
}