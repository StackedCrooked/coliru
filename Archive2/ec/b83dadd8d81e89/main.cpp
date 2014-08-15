#include <cmath>
#include <complex>
#include <cstdlib>
#include <iostream>

namespace detail
{
    // generic abs algorithm
    template<typename T>
    constexpr auto abs(const T& value)
        -> T
    {
        return (T{} < value) ? value: -value;
    }
}

namespace epyc
{
    template<typename T>
    constexpr auto abs(const T& value)
        -> T
    {
        using std::abs;
        using detail::abs;
        return abs(value);
    }
}

namespace eggs
{
    struct Foo
    {
        Foo(int val):
            val(val)
        {}

        int val;
    };

    Foo abs(Foo foo)
    {
        return { std::abs(foo.val) };
    }
}

struct Bar
{
    Bar(int val=0):
        val(val)
    {}

    Bar operator-() const
    {
        return { -val };
    }

    int val;
};

bool operator<(const Bar& lhs, const Bar& rhs)
{
    return lhs.val < rhs.val;
}

int main()
{
    using namespace std::literals;

    std::cout << epyc::abs(-5) << '\n';
    std::cout << epyc::abs(-5.3f) << '\n';
    std::cout << epyc::abs(-5i+2.0) << '\n';

    eggs::Foo foo = { -8 };
    std::cout << epyc::abs(foo).val << '\n';

    Bar bar = { -9 };
    std::cout << epyc::abs(bar).val << '\n';
}
