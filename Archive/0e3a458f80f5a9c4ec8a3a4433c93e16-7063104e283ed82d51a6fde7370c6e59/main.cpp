#include <type_traits>

template<typename F, typename Sig>
struct is_callable_test;

template<typename F, typename R>
struct is_callable_test<F, R()> {
    template<typename G>
    static decltype( std::declval<G>()(), void(), std::true_type {} ) test(int);
    
    template<typename>
    static std::false_type test(long);
    
    typedef decltype( test<F>(0) ) type;
    static const bool value = type::value;
};

template<typename F, typename Sig, bool = is_callable_test<F, Sig>::value>
struct is_callable;

template<typename F, typename R>
struct is_callable<F, R(), false>: std::false_type {};

template<typename F, typename R>
struct is_callable<F, R(), true>
: std::is_convertible<typename std::result_of<F()>::type, R> {};

int main()
{
    static_assert( !is_callable<int, void()>(), "" );
    static_assert( is_callable<int(*)(), double()>(), "" );
}