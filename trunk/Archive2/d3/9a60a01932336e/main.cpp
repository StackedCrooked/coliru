#include <iostream>
#include <vector>

namespace detail
{
    template<class T, class = decltype(T::check())>
    std::true_type has_check_impl(void*);

    template<class T>
    std::false_type has_check_impl(...);

    template <bool...B> struct all_ {
        static const bool value = true;
    };
    template <bool...B>
    struct all_<false, B...> {
        static const bool value = false;
    };
    template <bool...B>
    struct all_<true, B...> : all_<B...> {};
}

template<class T>
struct has_check : decltype(detail::has_check_impl<T>(nullptr)) { };

template <bool...B>
using all = std::integral_constant<bool, detail::all_<B...>::value>;

template<class... Mixins>
struct Checker
{
private:
    template<bool B = true, class=typename std::enable_if<all<B && has_check<Mixins>::value...>::value>::type>
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

struct A { static void handle() { std::cout << "A::handle() "; } };
struct B { static void handle() { std::cout << "B::handle() "; } };

int main()
{
    Checker<A, B>::go();
}
