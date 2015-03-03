#include <type_traits>

template<typename T, typename... Args>
using get_apply = typename T::template apply<Args...>;


template<typename...>
using void_t = void;

template<typename T, typename = void>
struct has_type : std::false_type {};

template<typename T>
struct has_type<T, void_t<typename T::type>> : std::true_type {};

template<typename MetafunctionClass, typename... Args>
struct run_assert_on_type
{
    static_assert(has_type<get_apply<MetafunctionClass, Args...>>::value, "MetafunctionClass::apply<Args...> has no member ::type");  
};

struct X {}; //Just a placeholder

template<typename... Ts>
struct MetafunctionClass1
{
    template<typename... Args>
    struct apply
    {
        using type = int;
    };
};

template<typename... Ts>
struct MetafunctionClass2
{
    template<typename... Args>
    struct apply
    {
        using result = int;
    };
};

using assert1 = run_assert_on_type<MetafunctionClass1<X,X,X>,int,int,int>;
using assert2 = run_assert_on_type<MetafunctionClass2<X,X,X>,int,int,int>;

int main()
{
    assert1 a;
    assert2 b;
}
