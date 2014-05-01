#include <type_traits>
#include <utility>
#include <iostream>

template <typename C, typename... Args>
struct is_call_possible {
private:
    template<typename T>
    static auto check(int)
        -> decltype( std::declval<T>().operator()(std::declval<Args>()...),
                     // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
                     // overload is removed if this expression is ill-formed
           std::true_type() );

    template<typename>
    static std::false_type check(...);
public:
    static constexpr bool value = decltype(check<C>(0))::value;
};

struct Foo {
    void operator()(int, char);
    int operator()(float&, const float&);
};

int main()
{
    std::cout
        << is_call_possible<Foo, int, char>::value
        << is_call_possible<Foo, float&, const float&>::value
        << is_call_possible<Foo, std::ostream&, int>::value;
}