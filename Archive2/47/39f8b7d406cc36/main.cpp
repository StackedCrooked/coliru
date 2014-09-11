#include <utility>
#include <functional>

template<typename Symbol>
struct symbol {
    Symbol s;
    symbol(Symbol s): s(std::move(s)) {}
    double operator()(double x) const noexcept {
        return s(x);
    }
};

struct constant {
private:
    double d;
public:
    constant(double d): d(d) {}
    double operator()(double) const noexcept {
        return d;
    }
};

struct variable {
    double operator()(double x) const noexcept {
        return x;
    }
};

template<typename First, typename Second, typename Operator>
struct expression {
private:
    symbol<First> lhs;
    symbol<Second> rhs;
public:
    expression(symbol<First> lhs, symbol<Second> rhs): lhs(std::move(lhs)), rhs(std::move(rhs)) {}

    double operator()(double x) const noexcept {
        Operator op;
        return op(lhs(x), rhs(x));
    }
};

using add      = std::plus<double>;
using subtract = std::minus<double>;
using multiply = std::multiplies<double>;
using divide   = std::divides<double>;

template<typename First, typename Second, typename Operator>
using expression_t = expression<symbol<First>, symbol<Second>, Operator>;

template<typename Trait>
using Enable = typename std::enable_if<Trait::value, int>::type;

template<typename Trait>
using Disable = typename std::enable_if<!Trait::value, int>::type;

template<typename Lhs, typename Rhs>
using Or = std::integral_constant<bool, Lhs::value || Rhs::value>;

template<typename Lhs, typename Rhs>
using And = std::integral_constant<bool, Lhs::value && Rhs::value>;

struct is_symbol_impl {
    template<typename T, typename U = decltype(std::declval<T>()(1.0))>
    static std::is_same<U, double> test(int);
    template<typename...>
    static std::false_type test(...);
};

template<typename T>
struct is_symbol : decltype(is_symbol_impl::test<T>(0)) {};

// operators..
template<typename First, typename Second,
         typename R = expression_t<First, Second, add>,
         Enable<And<is_symbol<First>, is_symbol<Second>>> = 0>
symbol<R> operator+(First lhs, Second rhs) {
    return { R{ symbol<First>(lhs), symbol<Second>(rhs) }};
}

template<typename First, typename Second,
         typename R = expression_t<First, Second, subtract>,
         Enable<And<is_symbol<First>, is_symbol<Second>>> = 0>
symbol<R> operator-(First lhs, Second rhs) {
    return { R{ symbol<First>(lhs), symbol<Second>(rhs) }};
}

template<typename First, typename Second,
         typename R = expression_t<First, Second, multiply>,
         Enable<And<is_symbol<First>, is_symbol<Second>>> = 0>
symbol<R> operator*(First lhs, Second rhs) {
    return { R{ symbol<First>(lhs), symbol<Second>(rhs) }};
}

template<typename First, typename Second,
         typename R = expression_t<First, Second, divide>,
         Enable<And<is_symbol<First>, is_symbol<Second>>> = 0>
symbol<R> operator/(First lhs, Second rhs) {
    return { R{ symbol<First>(lhs), symbol<Second>(rhs) }};
}

// constants..
template<typename First, typename Second, typename R = expression_t<First, constant, add>,
         Enable<And<is_symbol<First>, std::is_arithmetic<Second>>> = 0>
symbol<R> operator+(First lhs, Second rhs) {
    return { R{ symbol<First>{lhs}, symbol<constant>{constant(rhs)} }};
}

template<typename First, typename Second, typename R = expression_t<constant, First, add>,
         Enable<And<is_symbol<First>, std::is_arithmetic<Second>>> = 0>
symbol<R> operator+(Second lhs, First rhs) {
    return { R{ symbol<constant>{constant(lhs)}, symbol<First>{rhs} }};
}

template<typename First, typename Second, typename R = expression_t<First, constant, subtract>,
         Enable<And<is_symbol<First>, std::is_arithmetic<Second>>> = 0>
symbol<R> operator-(First lhs, Second rhs) {
    return { R{ symbol<First>{lhs}, symbol<constant>{constant(rhs)} }};
}

template<typename First, typename Second, typename R = expression_t<constant, First, subtract>,
         Enable<And<is_symbol<First>, std::is_arithmetic<Second>>> = 0>
symbol<R> operator-(Second lhs, First rhs) {
    return { R{ symbol<constant>{constant(lhs)}, symbol<First>{rhs} }};
}

template<typename First, typename Second, typename R = expression_t<First, constant, multiply>,
         Enable<And<is_symbol<First>, std::is_arithmetic<Second>>> = 0>
symbol<R> operator*(First lhs, Second rhs) {
    return { R{ symbol<First>{lhs}, symbol<constant>{constant(rhs)} }};
}

template<typename First, typename Second, typename R = expression_t<constant, First, multiply>,
         Enable<And<is_symbol<First>, std::is_arithmetic<Second>>> = 0>
symbol<R> operator*(Second lhs, First rhs) {
    return { R{ symbol<constant>{constant(lhs)}, symbol<First>{rhs} }};
}

template<typename First, typename Second, typename R = expression_t<First, constant, divide>,
         Enable<And<is_symbol<First>, std::is_arithmetic<Second>>> = 0>
symbol<R> operator/(First lhs, Second rhs) {
    return { R{ symbol<First>{lhs}, symbol<constant>{constant(rhs)} }};
}

template<typename First, typename Second, typename R = expression_t<constant, First, divide>,
         Enable<And<is_symbol<First>, std::is_arithmetic<Second>>> = 0>
symbol<R> operator/(Second lhs, First rhs) {
    return { R{ symbol<constant>{constant(lhs)}, symbol<First>{rhs} }};
}

template<typename Expression>
double integrate(Expression& e, double low, double high) {
     double area_one = 0;
     double area_two = 0;
     double x = low;
     const double epsilon = 0.001;
     while(x < high) {
         area_one += e(x) * epsilon;
         x += epsilon;
         area_two += e(x) * epsilon;
     }

     return (area_one + area_two)/2.0;
 }

#include <iostream>

int main() {
    variable x;

    auto f = x*x*x + 10;
    auto g = x*x + 3*x + 10;
    auto h = f * 10;
    std::cout << f(10) << '\n'
              << g(5) << '\n'
              << h(10) << '\n'
              << integrate(g, 0, 1) << '\n';
}
