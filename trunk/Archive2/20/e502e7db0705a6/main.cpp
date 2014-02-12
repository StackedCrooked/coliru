#include <initializer_list>

template<typename T> struct Small_set {
    Small_set(std::initializer_list<T>) { }
};

template<typename T, typename...> using head_t = T;

template<class... T>
    auto small_set(T... values) -> Small_set<head_t<T...> >
    { return { values... }; }

int main()
{
    auto ss = small_set(42);
    (void) ss;
}
