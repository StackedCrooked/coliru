#include <iostream>
#include <type_traits>
#include <tuple>
#include <utility>

template <typename T, typename U, typename... Ts>
struct is_same_all : std::integral_constant<bool, std::is_same<T, U>::value && is_same_all<T, Ts...>::value> {};

template <typename T, typename U>
struct is_same_all<T, U> : std::integral_constant<bool, std::is_same<T, U>::value> {};

template <int dim, class T>
class linear_searchspace
{
public:
    template <typename... Ts,
              typename std::enable_if<sizeof...(Ts) == dim && is_same_all<T, Ts...>::value, int>::type = 0>
    auto operator()(Ts&&... args)
        -> std::tuple<decltype(args, void(), T{})&...>
    {
        return std::tie(some_kinda_structure[std::forward<Ts>(args)]...);
    }

private:
    T some_kinda_structure[dim];
};

int main()
{
    linear_searchspace<6, int> lsp{};
    auto t = lsp(0, 1, 2, 3, 4, 5);
    std::get<0>(t) = 123;

    auto t2 = lsp(5, 4, 3, 2, 1, 0);
    std::cout << std::get<5>(t2) << std::endl;
}
