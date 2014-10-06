#include <type_traits>
#include <initializer_list>
#include <tuple>

template<typename T, typename U, typename = void>
struct erases_parameter : std::false_type { };

template<typename T, typename U>
struct erases_parameter<T, U, decltype(U{std::declval<T>()}, void())> 
    : std::true_type
{ };

constexpr auto all(std::initializer_list<bool> v)
{
    for (auto b : v) { if (!b) { return false; } }
    
    return true;
}

template<typename... Ts>
struct erases_all_parameters;

template<typename... Ts, typename... Us>
struct erases_all_parameters<std::tuple<Ts...>, std::tuple<Us...>>
    :  std::integral_constant<bool, all({erases_parameter<Ts, Us>{}...})> 
{ };

template<typename T, typename U>
using erases_return = 
      std::integral_constant<bool, 
                             std::is_same<T, void>{} || 
                             erases_parameter<U, T>{}>;

template<typename S1, typename S2>
struct erases;

template<typename R1, typename R2, typename... Params1, typename... Params2>
struct erases<R1(Params1...), R2(Params2...)>
    : std::integral_constant<
          bool, 
          erases_all_parameters<std::tuple<Params1...>, 
                                std::tuple<Params2...>>{} &&
          erases_return<R1, R2>{}>
{ };

int main()
{    
    static_assert(erases_parameter<int&, int>{}, "!");
    static_assert(erases_parameter<int&, int const>{}, "!");
    static_assert(erases_parameter<int&, int const&>{}, "!");
    static_assert(!erases_parameter<int&, int&&>{}, "!");

    static_assert(erases_parameter<int&&, int>{}, "!");
    static_assert(erases_parameter<int&&, int const>{}, "!");
    static_assert(erases_parameter<int&&, int const&>{}, "!");
    static_assert(!erases_parameter<int&&, int&>{}, "!");
    
    static_assert(erases_all_parameters<std::tuple<int&&, int&>, 
                                        std::tuple<int, int const&>>{}, "!");
    
    static_assert(erases_return<int&&, int>{}, "!");
    
    static_assert(erases<void(int&), int*(const int)>{}, "!");
    static_assert(erases<void(int&&), int*(int const&)>{}, "!");
    static_assert(erases<int&&(int&), int(int const)>{}, "!");
    
    static_assert(!erases<int&(int&), int(int)>{}, "!");
}





