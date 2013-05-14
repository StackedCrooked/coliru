#include <utility>
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

template<typename F>
struct is_callable<F, void(), Void<decltype( std::declval<F>()() )>>
: std::true_type {};

template<int I> struct choice: choice<I + 1> {};
template<> struct choice<9> {};
struct select_overload: choice<0> {};

template<typename F, EnableIf<is_callable<F&, int()>> = dummy>
int foo(F f, choice<0>)
{
    return f();
}

template<typename F, EnableIf<is_callable<F&, void()>> = dummy>
void foo(F f, choice<1>)
{
    return static_cast<void>(f());
}

template<typename F, EnableIf<is_callable<F&, void()>> = dummy>
auto foo(F f) -> decltype( foo(std::forward<F>(f), select_overload {}) )
{ return foo(std::forward<F>(f), select_overload {}); }

#include <cassert>

int main()
{
    int i = foo([] { return 4; });
    assert( i == 4 );
    
    foo([] {});
}