#include <type_traits>

constexpr int dummy = 0;
template<typename Cond> using EnableIf = typename std::enable_if<Cond::value, int>::type;

template<typename T> struct void_ { using type = void; };
template<typename T> using Void = typename void_<T>::type;

template<typename F, typename Sig, typename Sfinae = void>
struct is_callable;

template<typename F, typename R>
struct is_callable<F, R(), Void<decltype( std::declval<F>()() )>>
: std::is_convertible<typename std::result_of<F()>::type, R> {};

template<typename F, EnableIf<is_callable<F&, int()>> = dummy>
int foo(F f)
{
    return f();
}

template<typename F, EnableIf<is_callable<F&, void()>> = dummy>
void foo(F f)
{
    return f();
}

#include <cassert>

int main()
{
    int i = foo([] { return 4; });
    assert( i == 4 );
    
    foo([] {});
}