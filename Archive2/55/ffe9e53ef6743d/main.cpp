#include <type_traits>

template <class Derived>
class base
{
public:
    constexpr auto operator()()
    const noexcept { return static_cast<const Derived&>(*this)(); }
};

class derived : public base<derived>
{
public:
    constexpr auto operator()()
    const noexcept { return 0; }
};

template <class A, class B>
class expr : public base<expr<A, B>>
{
    const A m_a;
    const B m_b;
public:
    constexpr explicit expr(const A a, const B b)
    noexcept : m_a(a), m_b(b) {}

    constexpr auto operator()()
    const noexcept { return m_a() + m_b(); }
};

template <class D1, class D2>
constexpr auto foo(const D1& d1, const D2& d2)
noexcept { return expr<D1, D2>{d1, d2}; }

int main()
{
    constexpr auto d = derived{};
    constexpr auto e = foo(d, d);
    static_assert(e() == 0, "");
}