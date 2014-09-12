#include <stdexcept>
#include <type_traits>
#include <utility>

namespace detail
{
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
        f();
        return 0;
    }

    template<typename T, typename dummy = void>
    struct dispatch
    {
        static_assert(std::is_same<T, void>::value,
                      "Incompatible return type");
    };

    template<typename T>
    struct dispatch<T,
        typename std::enable_if< std::is_convertible<T, int>{} >::type>
    {
        using type = returns_convertible_to_int;
    };

    template<typename T>
    struct dispatch<T,
        typename std::enable_if< std::is_same<T, void>{} >::type>
    // alt: template<> struct dispatch<void,void>
    {
        using type = returns_void;
    };
}

template<typename Func>
int WrapException(Func&& f)
{
    try
    {
        return detail::WrapException_dispatch( std::forward<Func>(f),
            typename detail::dispatch<decltype(f())>::type{} );
    }
    catch(std::exception const&) { return -1; }
}


int foo() { return 42; }
void bar() {}


int main()
{
    WrapException(foo);
    WrapException(bar);
}