#include <tuple>

template <int n>
struct A
{   
    void baz() {}
};

template <>
struct A<3>
{
    // no baz!
};

template<class...> struct make_void { using type = void; };
template<class... Ts> using void_t = typename make_void<Ts...>::type;


template <class, class = void>
struct Foo;

template <class... Ts, class T>
struct Foo<std::tuple<Ts...>, T> {
    // no bar
};

template <class... Ts>
struct Foo<std::tuple<Ts...>, void_t<decltype(std::declval<Ts&>().baz())...>>
{
    static constexpr auto I = 2;
    virtual void bar()
    {
        auto x = std::get<I>(std::make_tuple(Ts()...));
        x.baz();
    }
};

template struct Foo<std::tuple<A<1>, A<2>, A<3>>>;
template struct Foo<std::tuple<A<1>, A<2>, A<2>>>;

int main()
{
}