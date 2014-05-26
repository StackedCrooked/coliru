#include <utility>

#define AUTO_RETURN( ... ) -> decltype(__VA_ARGS__) { return (__VA_ARGS__); }

template< typename F,
          typename T1,
          typename...
           Args >
auto invoke( F f, T1&& t1, Args&&... args )
AUTO_RETURN(  (std::forward<T1>(t1).*f)(std::forward<Args>(args)...)  )

template< typename F,
          typename T1,
          typename... Args >
auto invoke( F f, T1 t1, Args&&... args )
AUTO_RETURN(  (t1->*f)(std::forward<Args>(args)...)  )

template< typename F,
          typename T1 >
auto invoke( F f, T1&& t1 )
AUTO_RETURN(  std::forward<T1>(t1).*f  )

template< typename F,
          typename T1 >
auto invoke( F f, T1 t1 )
AUTO_RETURN(  t1->*f  )

template< typename F, typename... Args >
auto invoke( F&& f, Args&&... args )
{
    return std::forward<F>(f)(std::forward<Args>(args)...);
}

int main()
{
}
