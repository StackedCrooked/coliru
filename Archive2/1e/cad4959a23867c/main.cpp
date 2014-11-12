#include <utility>
#include <type_traits>

struct foobar
{
    foobar(int) { } // implicit conversion
    foobar(const foobar&) = delete;
};

namespace bah {
    using std::forward;
    using std::move;
    
    struct Piecewise_construct_t {};

    template <class T1, class T2>
    struct Pair {
        typedef T1 first_type;
        typedef T2 second_type;
        T1 first;
        T2 second;

        //Pair(const Pair&) = default;
        //Pair(Pair&&) = default;

        /*constexpr*/ Pair(): first(), second() {}

        Pair(const T1& x, const T2& y)
            : first( x ), second( y )
        {}
 
        template<class U, class V, class = typename std::enable_if<std::is_convertible<U, T1>{} && std::is_convertible<U, T2>{}>::type>
        Pair(U&& x, V&& y)
            : first( forward<U>( x ) ), second( forward<V>( y ) )
        {}

        template<class U, class V> Pair(const Pair<U, V>& p)
            : first( p.first ), second( p.second )
        {}

        template<class U, class V> Pair(Pair<U, V>&& p)
            : first( move( p.first ) ), second( move( p.second ) )
        {}

        //template <class... Args1, class... Args2>
        //Pair(Piecewise_construct_t,
        //tuple<Args1...> first_args, tuple<Args2...> second_args);
        //
        //Pair& operator=(const Pair& p);
        //template<class U, class V> Pair& operator=(const Pair<U, V>& p);
        //Pair& operator=(Pair&& p) noexcept(see below);
        //template<class U, class V> Pair& operator=(Pair<U, V>&& p);
        //void swap(Pair& p) noexcept(see below);
    };
}

auto main()
    -> int
{
    bah::Pair<int, foobar> p{1, 2};
}
