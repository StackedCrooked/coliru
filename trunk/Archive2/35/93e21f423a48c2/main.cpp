#include <type_traits>


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
    static constexpr bool is_signed = std::is_signed<T>{} || std::is_signed<U>{};
    using interm = typename std::common_type<T, U>::type;
    
    template < typename T1, typename = std::false_type >
    struct signed_if_possible
    {
        using type = T1;
    };
    template < typename T1 >
    struct signed_if_possible < T1, typename std::is_same<typename std::make_signed<T1>::type, T1>::type >
    {
        using type = typename std::make_signed<T1>::type;
    };
    
    using interm_signed_if_possible = typename signed_if_possible<interm>::type;

public:
    using type = typename std::conditional<is_signed, interm_signed_if_possible, interm>::type;
};


struct S {}; // no std::make_signed available for this type

template<class T>
struct common_type<S, T>
{
    using type = S;
};

template < typename Result, typename... Args >
using check_result = std::is_same < Result, typename common_type<Args...>::type >;

int main()
{
    static_assert(check_result<int, int, bool>{}, "int <- int, bool");
    static_assert(check_result<int, signed int, unsigned int>{}, "int <- signed, unsigned");
    static_assert(check_result<S, S, int>{}, "S <- S, int");
}

