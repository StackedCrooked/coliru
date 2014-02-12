#include <tuple>
#include <initializer_list>

template<typename T> struct Small_set {
    Small_set(std::initializer_list<T>) { }
};

namespace detail
{
    template<typename T, typename...> static T deduce_head();

    template <typename... T>
    using head_t = decltype(detail::deduce_head<T...>());
}

template<class... T>
    auto small_set(T... values) -> Small_set<detail::head_t<T...> >
    { return { values... }; }

int main()
{
    auto ss = small_set(42, 56, 7);
    (void) ss;
}
