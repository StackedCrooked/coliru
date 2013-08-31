#include <iostream>
#include <tuple>
#include <vector>

namespace detail
{
    template <typename... Ts>
    struct tuple_change { };
    
    template <typename... Ts>
    struct tuple_change<std::tuple<Ts...>>
    {
        using type = std::tuple<std::vector<Ts>...>;
    };
    
    template <int... Is>
    struct index { };
    
    template <int N, int... Is>
    struct gen_seq : gen_seq<N - 1, N - 1, Is...> { };
    
    template <int... Is>
    struct gen_seq<0, Is...> : index<Is...> { };
}

template <typename... Args, int... Is>
void fill(std::tuple<Args...>& var, detail::index<Is...>)
{
    auto l = { (std::get<Is>(var).assign(5, 11), 0)... }; // here I just decided to make the size 5
    (void)l;
}

template <typename... Args>
void fill(std::tuple<Args...>& var)
{
    fill(var, detail::gen_seq<sizeof...(Args)>{});
}

template <typename... Ts>
struct tuple_printer
{
    template <int... Is>
    static void print(std::tuple<Ts...>& var, detail::index<Is...>)
    {
        auto l = { (print(std::get<Is>(var)), 0)... };
        (void)l;
    }
    
    static void print(std::tuple<Ts...>& var)
    {
        print(var, detail::gen_seq<sizeof...(Ts)>{});
    }
    
    template <typename T>
    static void print(std::vector<T>& v)
    {
        for (auto a : v)
        {
            std::cout << std::boolalpha << a << std::endl;
        }
        std::cout << std::endl;
    }
};

template <typename... Ts>
void print(std::tuple<Ts...>& var)
{
    tuple_printer<Ts...>::print(var);
}

using result_type = detail::tuple_change<std::tuple<int, bool>>::type;

int main()
{
    result_type r;
    fill(r);

    print(r);
}