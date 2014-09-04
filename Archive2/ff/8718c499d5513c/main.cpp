#include <cassert>
#include <utility>
#include <array>

template<typename X, typename Y>
void foo() {}

using foo_type = void(*)();

template<typename... T>
struct list {
    static constexpr auto size = sizeof...(T);
};

template<typename X, typename Y, typename Indices = std::make_index_sequence<X::size * Y::size>>
struct dispatch;

template<
    template<typename...> class XList, typename... Xs
    , template<typename...> class YList, typename... Ys
    , std::size_t... Indices
>
struct dispatch<XList<Xs...>, YList<Ys...>, std::index_sequence<Indices...>> {
private:
    static constexpr auto stride = sizeof...(Ys);
    using inner_type = std::array<foo_type, stride>;
    using multi_type = inner_type[sizeof...(Xs)];

    template<typename X, typename... Yss>
    static constexpr inner_type inner()
    { return {{ &foo<X, Yss>... }}; }

    static constexpr multi_type multi_value = {
        inner<Xs, Ys...>()...
    };

public:
    static constexpr auto size = sizeof...(Xs) * sizeof...(Ys);
    static constexpr foo_type value[size] = {
        multi_value[Indices / stride][Indices % stride]...
    };
};

template<
    template<typename...> class XList, typename... Xs
    , template<typename...> class YList, typename... Ys
    , std::size_t... Indices
>
constexpr foo_type dispatch<XList<Xs...>, YList<Ys...>, std::index_sequence<Indices...>>::value[size];

int main()
{
    using dispatch_t = dispatch<
            list<int,   char, double>,
            list<float, unsigned long>
        >;

    constexpr auto&& table = dispatch_t::value;

    static_assert( dispatch_t::size == 6, "" );
    static_assert( table[0] == &foo<int,    float>, "" );
    static_assert( table[1] == &foo<int,    unsigned long>, "" );
    static_assert( table[2] == &foo<char,   float>, "" );
    static_assert( table[3] == &foo<char,   unsigned long>, "" );
    static_assert( table[4] == &foo<double, float>, "" );
    static_assert( table[5] == &foo<double, unsigned long>, "" );
}