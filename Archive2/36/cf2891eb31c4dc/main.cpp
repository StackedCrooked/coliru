#include <utility>

#define AUTO_RETURN( ... ) -> decltype(__VA_ARGS__) { return (__VA_ARGS__); }

struct base_tag {};
struct derived_tag : base_tag {};

template< typename F,
          typename T1,
          typename...
           Args >
auto invoke( derived_tag, F f, T1&& t1, Args&&... args )
AUTO_RETURN(  (std::forward<T1>(t1).*f)(std::forward<Args>(args)...)  )

template< typename F,
          typename T1,
          typename... Args >
auto invoke( base_tag, F f, T1 t1, Args&&... args )
AUTO_RETURN(  ((*t1).*f)(std::forward<Args>(args)...)  )

template< typename F,
          typename T1 >
auto invoke( base_tag, F f, T1&& t1 )
AUTO_RETURN(  std::forward<T1>(t1).*f  )

template< typename F,
          typename T1 >
auto invoke( base_tag, F f, T1 t1 )
AUTO_RETURN(  (*t1).*f  )

template< typename F, typename... Args >
auto invoke( base_tag, F&& f, Args&&... args )
{
    return std::forward<F>(f)(std::forward<Args>(args)...);
}

template< typename... Args >
auto INVOKE( Args&&... args )
{
    return invoke( derived_tag{}, std::forward<Args>(args)... );
}

struct wat { wat& operator*() { return *this; } void foo(){} };;

int main()
{
    INVOKE(&wat::foo, wat{});
}
