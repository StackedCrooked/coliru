#include <functional>
#include <iostream>

template<typename F>
struct first_argument {
    template<typename Ret, typename A, typename... Rest>
    static A  helper(Ret (F::*)(A, Rest...));
    template<typename Ret, typename A, typename... Rest>
    static A helper(Ret (F::*)(A, Rest...) const);
    typedef decltype(helper(&F::operator())) type;
};

template<typename T>
void foo(T f) {
    typedef typename first_argument<T>::type type;
    std::cout << typeid(type).name() << ':';
    f(type());
}

template<typename T>
void foo(void (*f)(T)) {
    typedef T type;
    std::cout << typeid(type).name() << ':';
    f(type());
}

struct test {
    void operator ()(bool value) {
        std::cout << value << std::endl;
    }
};

static void funptr(bool value) {
    std::cout << value << std::endl;
}

static void extra(bool value, int extra) {
    std::cout << value << ':' << extra << std::endl;
}

int main()
{
    foo([](bool value) {
        std::cout << value << std::endl;
    });
    foo([](int value) {
        std::cout << value << std::endl;
    });
    const int i = 15;
    foo([&i](int value) {
        std::cout << value << ':' << i << std::endl;
    });
    foo(test());
    foo(funptr);
#if 0
    foo(std::bind(extra, std::placeholders::_1, 15));
#endif
}