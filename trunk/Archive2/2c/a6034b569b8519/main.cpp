#include <iostream>
#include <vector>

namespace detail
{
    template<class T, class = decltype(T::check())>
    std::true_type has_check_impl(void*);

    template<class T>
    std::false_type check_impl(...);
}

template<class T>
struct has_check : decltype(detail::has_check_impl<T>(nullptr)) { };

template<class T, class...>
using first = T;

template<class... Mixins>
struct Checker
{
public:
    template<class =
             first<void,
                   typename std::enable_if<has_check<Mixins>::value>::type...>>
    static void foo(int)
    {
        auto x{ (Mixins::check(), 0)... };
        (void)x;
    }

    static void foo(...)
    {
        auto x{ (Mixins::handle(), 0)... };
        (void)x;
    }
    
    static void go() {
        foo(0);
    }
};

struct A { static void check() { std::cout << "check() "; } };
struct B { static void check() { std::cout << "check() "; } };

int main()
{
    Checker<A, B>::go();
}