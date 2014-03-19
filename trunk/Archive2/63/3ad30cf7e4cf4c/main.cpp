#include <type_traits>

template<class Source>
struct any_t
{
    template<class Dest, class = typename std::enable_if< std::is_same<typename std::decay<Source>::type, Dest>::value >::type>
    operator Dest&();
};

// dummy to allow the syntax func<T>
template<class T>
void func();

template<class T, class U, class V>
auto test(int) -> decltype( func<T>( any_t<U>{}, any_t<V>{} ), std::true_type{} );

template<class, class, class>
std::false_type test(...);

namespace foo
{
    struct tag {};
    
    template<class T>
    void func(tag&, double const&);
};

namespace bar
{
    struct tag {};
    
    template<class T>
    void func(tag&, int);
};

int main()
{
    static_assert( decltype(test<int, foo::tag, double const&>(0))::value, "first test failed (false negative)");
    static_assert( not decltype(test<int, bar::tag, double const&>(0))::value, "second test succeeded (false positive)");
}
