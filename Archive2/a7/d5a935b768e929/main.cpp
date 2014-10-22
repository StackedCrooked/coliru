#include <type_traits>
#include <initializer_list>
#include <utility>
#include <tuple>

namespace detail
{
    constexpr auto all(std::initializer_list<bool> v)
    {
        for (auto b : v) { if (!b) { return false; } }
        
        return true;
    }

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
    
    template<typename ThunkR, 
             typename TargetR, 
             typename T,
             typename U,
             typename... ThunkParams,
             typename... TargetParams>
    struct make_forwarding_thunk<ThunkR(U*, ThunkParams...), 
                                 TargetR(T::*)(TargetParams...)>
    {
        template<TargetR(T::*F)(TargetParams...)>
        struct lambda
        {
            static ThunkR invoke(U* self, ThunkParams... args)
            {
                return (self->*F)(std::forward<ThunkParams>(args)...);
            }
        };
    };
}

#define THUNK(S, fxn) \
        detail::make_forwarding_thunk<S, decltype(fxn)> \
        ::template lambda<fxn>::invoke

#define CALL(itable, index, ...) \
        (std::get<index>(itable))(__VA_ARGS__);

//======================================================================
// EXAMPLE

#include <iostream>

struct X
{
    X(int val) : _val{val} 
    { }
    
    void bar(int x, double y) 
    { std::cout << x << " " << y << " " << _val << std::endl; }
    
    int _val;
};

void foo(X const& x, int& y, bool z) 
{
    std::cout << x._val << " " << y << " " << z << std::endl;
} 

int main()
{    
    int i = 42;
    X obj{1337};

    auto thunk1 = THUNK(void(X&, int&, bool&&), &foo);
    thunk1(obj, i, true);
    
    auto thunk2 = THUNK(void(X*, int&, double&&), &X::bar);
    thunk2(&obj, i, 1729);
    
    auto itable = std::make_tuple(THUNK(void(X const&, int&, bool&&), &foo),
                                  THUNK(void(X*, int&, double&&), &X::bar));
                                 
    std::cout << sizeof(itable) << std::endl;
    
    (std::get<1>(itable))(&obj, i, 321);
    
    CALL(itable, 1, &obj, i, 123);
}

//======================================================================



