#include <tuple>
#include <type_traits>

template <template<class> class, class>
struct update_tuple;

template <template <class> class T, class... Args>
struct update_tuple<T, std::tuple<Args...>>
{
    using type = std::tuple<T<Args>...>;
};

template <class>
class Foo
{

};

int main()
{
    static_assert
    (
        std::is_same
        <
                std::tuple<Foo<int>, Foo<char>, Foo<double>>,
            update_tuple<Foo, std::tuple<int, char, double>>::type
        >::value,
        "They are not same"
    );
    return 0;
}
