#include <iostream>
#include <vector>

namespace detail
{
    template<class T, class = decltype(T::check())>
    std::true_type has_check_impl(void*);

    template<class T>
    std::false_type has_check_impl(...);
}

template<class T>
struct has_check : decltype(detail::has_check_impl<T>(nullptr)) { };

template<class T, class...>
using first = T;

template<class... Mixins>
struct Checker
{
private:
    template<class T = void, class =
             first<T,
                   typename std::enable_if<has_check<Mixins>::value, T>::type...>>
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
    
public:
    static void go() {
        foo(0);
    }
};

struct A { static void handle() { std::cout << "handle() "; } };
struct B { static void handle() { std::cout << "handle() "; } };

int main()
{
    Checker<A, B>::go();
}