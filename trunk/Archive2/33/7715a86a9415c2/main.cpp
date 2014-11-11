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

template <class... Ts>
struct Foo
{
    static constexpr auto I = 2;
    virtual void bar()
    {
        auto x = std::get<I>(std::make_tuple(Ts()...));
        x.baz();
    }
};

template struct Foo<A<1>, A<2>, A<3>>;

int main()
{
}