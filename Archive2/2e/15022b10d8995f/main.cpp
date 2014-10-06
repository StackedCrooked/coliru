#include <type_traits>
#include <initializer_list>
#include <tuple>

constexpr auto all(std::initializer_list<bool> v)
{
    for (auto b : v) { if (!b) { return false; } }
    
    return true;
}

namespace detail
{
    template<typename T, typename U, typename = void>
    struct erases_parameter : std::false_type { };
    
    template<typename T, typename U>
    struct erases_parameter<T, U, decltype(U{std::declval<T>()}, void())> 
        : std::true_type
    { };
    
    //======================================================================
    // A FEW TESTS...
    static_assert(erases_parameter<int&, int>{}, "!");
    static_assert(erases_parameter<int&, int const>{}, "!");
    static_assert(erases_parameter<int&, int const&>{}, "!");
    static_assert(!erases_parameter<int&, int&&>{}, "!");
    static_assert(erases_parameter<int&&, int>{}, "!");
    static_assert(erases_parameter<int&&, int const>{}, "!");
    static_assert(erases_parameter<int&&, int const&>{}, "!");
    static_assert(!erases_parameter<int&&, int&>{}, "!");
    //======================================================================

    template<typename... Ts>
    struct erases_all_parameters;

    template<typename... Ts, typename... Us>
    struct erases_all_parameters<std::tuple<Ts...>, std::tuple<Us...>>
        :  std::integral_constant<bool, all({erases_parameter<Ts, Us>{}...})> 
    { };

    //======================================================================
    // A FEW TESTS...
    static_assert(erases_all_parameters<std::tuple<int&&, int&>, 
                                        std::tuple<int, int const&>>{}, "!");
    //======================================================================
    
    template<typename T, typename U>
    using erases_return_type = 
          std::integral_constant<bool, 
                                 std::is_same<T, void>{} || 
                                 erases_parameter<U, T>{}>;

    //======================================================================
    // A FEW TESTS...
    static_assert(erases_return_type<int&&, int>{}, "!");
    //======================================================================
}

template<typename S1, typename S2>
struct erases_signature;

template<typename R1, typename R2, typename... Params1, typename... Params2>
struct erases_signature<R1(Params1...), R2(Params2...)>
    : std::integral_constant<
          bool, 
          detail::erases_all_parameters<std::tuple<Params1...>, 
                                        std::tuple<Params2...>>{} &&
          detail::erases_return_type<R1, R2>{}>
{ };

//======================================================================
// A FEW TESTS...
static_assert(erases_signature<void(int&), int*(const int)>{}, "!");
static_assert(erases_signature<void(int&&), int*(int const&)>{}, "!");
static_assert(erases_signature<int&&(int&), int(int const)>{}, "!");
static_assert(!erases_signature<int&(int&), int(int)>{}, "!");
//======================================================================
    
namespace detail
{
    
    template<typename ThunkSig, typename TargetSig>
    struct make_forwarding_thunk;
    
    template<typename ThunkR, 
             typename TargetR, 
             typename... ThunkParams,
             typename... TargetParams>
    struct make_forwarding_thunk<ThunkR(ThunkParams...), 
                                 TargetR(*)(TargetParams...)>
    {
        template<TargetR(*F)(TargetParams...)>
        struct lambda
        {
            static ThunkR invoke(ThunkParams... args)
            {
                return F(std::forward<ThunkParams>(args)...);
            }
        };
    };
}

#define FORWARDING_THUNK(S, fxn) \
        detail::make_forwarding_thunk<S, decltype(fxn)>::template lambda<fxn>::invoke

#include <iostream>

void foo(int& x, bool b) 
{
    std::cout << x << " " << b << std::endl;
} 

int main()
{    
    using SIG = void(int&, bool&&);
    auto thunk = FORWARDING_THUNK(SIG, &foo);
    
    int x = 42;
    thunk(x, true);
    



}





