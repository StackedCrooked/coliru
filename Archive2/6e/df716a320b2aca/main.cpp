#include <iostream>
#include <utility>
#include <tuple>

#if 0 // Not in C++11 // make_index_sequence
#include <cstdint>

template <std::size_t...> struct index_sequence {};

template <std::size_t N, std::size_t... Is>
struct make_index_sequence : make_index_sequence<N - 1, N - 1, Is...> {};

template <std::size_t... Is>
struct make_index_sequence<0u, Is...> : index_sequence<Is...> {};

#endif // make_index_sequence

template <typename... T> void f(T... a) {
    (void)std::initializer_list<int>{(void(std::cout << a << std::endl), 0)...};
}

template <typename... Ts> class B
{
public:
    std::tuple<Ts...> t;
    B(Ts... args)
        : t(args...)
    {
    }
    void m() { call_f(std::index_sequence_for<Ts...>()); }

private:
    template <std::size_t ... Is>
    void call_f(std::index_sequence<Is...>)
    {
        f(std::get<Is>(t)...);
    }
};

int main()
{
    B<int, double> b(1, 1.1);
    b.m();
}
