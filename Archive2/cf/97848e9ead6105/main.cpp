#include <type_traits>
#include <limits>
#include <cstdint>


template < typename T, typename U >
constexpr auto cmin(T t, U u) -> typename std::remove_reference<decltype( t<u?t:u )>::type
{ return t<u?t:u; }

template < typename T, typename U >
constexpr auto cmax(T t, U u) -> typename std::remove_reference<decltype( t>u?t:u )>::type
{ return t>u?t:u; }


#include <iostream>
template<typename T, T min, T max>
struct basic_ranged_integer{ void print() { std::cout << min << " : " << max; } };

template<std::intmax_t min, std::intmax_t max>
using ranged_integer = basic_ranged_integer<std::intmax_t, min, max>;


template<typename... T>
struct common_type;

template<typename T, typename U, typename... V>
struct common_type<T, U, V...> :
        common_type<typename common_type<T, U>::type, V...> //left recursion
{};


template<typename T>
struct common_type<T> :
        std::common_type<T>
{};

template<typename T, typename U>
struct common_type<T, U>
{
private:
    static constexpr bool signed_xor  = std::is_signed<T>{} xor std::is_signed<U>{};
    
    template < bool b = signed_xor, typename dummy = void >
    struct helper
    {
        using type = typename std::common_type<T, U>::type;
    };
    template < typename dummy >
    struct helper<true, dummy>
    {
        static constexpr std::intmax_t minT = std::numeric_limits<T>::min();
        static constexpr std::intmax_t minU = std::numeric_limits<U>::min();
        static constexpr std::uintmax_t maxT = std::numeric_limits<T>::max();
        static constexpr std::uintmax_t maxU = std::numeric_limits<U>::max();
        
        // note: +1 might overflow.. maybe not a good idea!
        // also: second argument should be of type uintmax_t
        using type = ranged_integer< cmin(minT, minU), (std::intmax_t)cmax(maxT, maxU) +1 >;
    };

public:
    using type = typename helper<>::type;
};


#include <climits>

template < typename Result, typename... Args >
using check_result = std::is_same < Result, typename common_type<Args...>::type >;

int main()
{
    static_assert(check_result<int, int, short>{}, "int <- int, short");
    static_assert(check_result<ranged_integer<SHRT_MIN, USHRT_MAX+1>, signed short, unsigned short>{}, "r_i<..> <- signed, unsigned");
}

