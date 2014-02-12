#include <tuple>
#include <initializer_list>

template<typename T> struct Small_set {
    Small_set(std::initializer_list<T>) { }
};

template< class... Values >
    auto small_set( Values const... values )
        -> Small_set< typename std::tuple_element<0, std::tuple< Values... > >::type >
    { return { values... }; }

int main()
{
    auto ss = small_set(42, 56, 7);
    (void) ss;
}
