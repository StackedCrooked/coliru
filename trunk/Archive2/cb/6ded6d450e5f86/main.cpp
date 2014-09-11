#include <type_traits>
#include <utility>

struct returns_convertible_to_int {};
struct returns_void {};

template<typename Func>
int WrapException_dispatch(Func&& f, returns_convertible_to_int)
{
    return f();
}

template<typename Func>
int WrapException_dispatch(Func&& f, returns_void)
{
    return 0;
}

template<typename T, typename dummy = void>
struct dispatch;

template<typename T>
struct dispatch<T, typename std::enable_if< std::is_convertible<T, int>{} >::type>
{
    using type = returns_convertible_to_int;
};

template<typename T>
struct dispatch<T, typename std::enable_if< std::is_same<T, void>{} >::type>
{
    using type = returns_void;
};


template<typename Func>
int WrapException(Func&& f)
{
    return WrapException_dispatch( std::forward<Func>(f), typename dispatch<decltype(f())>::type{} );
}


int foo() { return 42; }
void bar() {}


int main()
{
    WrapException(foo);
    WrapException(bar);
}