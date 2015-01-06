#include <iostream>
#include <functional>
#include <tuple>
#include <utility>


template <typename T> struct caller;

template <typename... Ts> struct caller<std::tuple<Ts...>>
{
    template <typename F>
    void operator() (F f, std::tuple<Ts...>& t, int n)
    {
        (*this)(f, t, n, std::index_sequence_for<Ts...>());
    }
private:
    template <typename F, std::size_t ... Is>
    void operator() (F f, std::tuple<Ts...>& t, int n, std::index_sequence<Is...>)
    {
        std::function<void(F, std::tuple<Ts...>&)> fs[] = { &helper<F, Is>... };
        fs[n](f, t);
    }

    template <typename F, std::size_t I>
    static void helper(F f, std::tuple<Ts...>& t)
    {
        f(std::get<I>(t));
    }

};

struct F
{
    template <typename T>
    void operator() (const T& t) const
    {
        std::cout << t << std::endl;
    }
};

template <typename F, typename T>
void call(F f, T& t, int n)
{
    caller<T>()(f, t, n);
}

int main() {
    std::tuple<const char*, int> t("test", 42);

    call(F(), t, 0);
    call(F(), t, 1);
}

