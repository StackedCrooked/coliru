#include <tuple>
#include <initializer_list>

template<typename T> struct Small_set {
    Small_set(std::initializer_list<T>) { }
};

template<typename T, typename...> static T deduce_head();
template<class... T>
    auto small_set(T... values) -> Small_set<decltype(deduce_head<T...>())>
    { return { values... }; }

int main()
{
    auto ss = small_set(42);
    (void) ss;
}
