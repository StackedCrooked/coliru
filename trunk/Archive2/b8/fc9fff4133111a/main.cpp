#include <iostream>

namespace detail
{
    template <typename> struct op {};
    using smooth_op = op<struct smooth>;

    template <typename T, typename> struct oper {
        T const& v; oper(T const& v):v(v){}
    };

    template <typename T> static oper<T, smooth_op> operator<(T const& v, smooth_op) { return v; }
    template <typename U> static void operator>(oper<int, smooth_op> const& l, U const& r) { 
        std::cout << l.v << " <love for sale> " << r << "\n";
    }
    template <typename U> static void operator>(oper<double, smooth_op> const& l, U const& r) { 
        std::cout << l.v << " <coast to coast> " << r << "\n";
    }
}

constexpr detail::smooth_op smooth;

int main()
{
    42   <smooth> "overloading";
    3.14 <smooth> "sade story";
}
