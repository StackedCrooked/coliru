#include<type_traits>

template<bool...> struct any_of : std::false_type {};
template<bool...args> struct any_of<true, args...> : std::true_type {};
template<bool...args> struct any_of<false, args...> : any_of<args...> {};

template<class... Args>
using any_of_t = any_of<Args{}()...>;

template<class T, class U>
struct related : std::false_type { };

template<class T>
struct related<T, T> : std::true_type { };

template<class T, class U>
struct related<T, const U> : related<T, U> { };

template<class T, class U>
struct related<T, volatile U> : related<T, U> { };

template<class T, class U>
struct related<T, U &> : related<T, U> { };

template<class T, class U>
struct related<T, U &&> : related<T, U> { };

template<class T, class U>
struct related<T, U*> : related<T, U> { };

template<class T, class U, std::size_t N>
struct related<T, U [N]> : related<T, U> { };
template<class T, class U>
struct related<T, U []> : related<T, U> { };

template<class T, class U, class V>
struct related<T, U V::*> : any_of_t<related<T, U>, related<T,V>> { };

template<class T, template<class...> class U, class... Args>
struct related<T, U<Args...>> : any_of_t<related<T, Args>...> {};

template<class T, class R, class... A>
struct related<T, R (A...)> : any_of_t<related<T, R>, related<T, A>...> {};

template<class T, class R, class... A>
struct related<T, R (A...) const> : any_of_t<related<T, R>, related<T, A>...> {};

    class B; class C;
    
int main() {
    static_assert(related<B, int (C::*)(const C&, B* const * const * volatile * const &)>::value, "Oops");
}