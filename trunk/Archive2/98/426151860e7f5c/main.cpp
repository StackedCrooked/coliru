#include <type_traits>

enum class Color {Red, Green, Blue};
enum class ShowAxes {False, True};
enum class ShowLabels {False, True};

    template<class Result, class...>
    struct extract;
    
    template<class Result, Result Value, class... Tail>
    struct extract<Result, std::integral_constant<Result, Value>, Tail...> : std::integral_constant<Result, Value> {};
    
    template<class Result, class Head, class... Tail>
    struct extract<Result, Head, Tail...> : extract<Result, Tail...> {};

template< Color c, ShowAxes a, ShowLabels l >
class A_impl
{
public:
    static constexpr Color col = c;
    static constexpr ShowAxes axes = a;
    static constexpr ShowLabels labels = l;
};

template<class X, class Y, class Z>
using A = A_impl<extract<Color, X, Y, Z>::value, extract<ShowAxes, X, Y, Z>::value, extract<ShowLabels, X, Y, Z>::value>;

#define AS_IC(Value) std::integral_constant<decltype(Value), Value>

int main(){

    A<AS_IC(Color::Red), AS_IC(ShowAxes::True), AS_IC(ShowLabels::True)> a;
    A<AS_IC(Color::Red), AS_IC(ShowLabels::True), AS_IC(ShowAxes::True)> b;
    static_assert(a.col == Color::Red, "Oops");
    static_assert(a.axes == ShowAxes::True, "Oops");
    static_assert(a.labels == ShowLabels::True, "Oops");
    static_assert(b.col == Color::Red, "Oops");
    static_assert(b.axes == ShowAxes::True, "Oops");
    static_assert(b.labels == ShowLabels::True, "Oops");
    
    return 0;
 }