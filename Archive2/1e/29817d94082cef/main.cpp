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

// operators..
template<typename First, typename Second, typename R = expression_t<First, Second, add>>
symbol<R> operator+(First lhs, Second rhs) {
    return { R{ symbol<First>(lhs), symbol<Second>(rhs) }};
}

template<typename First, typename Second, typename R = expression_t<First, Second, subtract>>
symbol<R> operator-(First lhs, Second rhs) {
    return { R{ symbol<First>(lhs), symbol<Second>(rhs) }};
}

template<typename First, typename Second, typename R = expression_t<First, Second, multiply>>
symbol<R> operator*(First lhs, Second rhs) {
    return { R{ symbol<First>(lhs), symbol<Second>(rhs) }};
}

template<typename First, typename Second, typename R = expression_t<First, Second, divide>>
symbol<R> operator/(First lhs, Second rhs) {
    return { R{ symbol<First>(lhs), symbol<Second>(rhs) }};
}

// constants..
template<typename First, typename R = expression_t<First, constant, add>>
symbol<R> operator+(First lhs, double rhs) {
    return { R{ symbol<First>{lhs}, symbol<constant>{constant{rhs}} }};
}

template<typename First, typename R = expression_t<constant, First, add>>
symbol<R> operator+(double lhs, First rhs) {
    return { R{ symbol<constant>{constant{lhs}}, symbol<First>{rhs} }};
}

template<typename First, typename R = expression_t<First, constant, subtract>>
symbol<R> operator-(First lhs, double rhs) {
    return { R{ symbol<First>{lhs}, symbol<constant>{constant{rhs}} }};
}

template<typename First, typename R = expression_t<constant, First, subtract>>
symbol<R> operator-(double lhs, First rhs) {
    return { R{ symbol<constant>{constant{lhs}}, symbol<First>{rhs} }};
}

template<typename First, typename R = expression_t<First, constant, multiply>>
symbol<R> operator*(First lhs, double rhs) {
    return { R{ symbol<First>{lhs}, symbol<constant>{constant{rhs}} }};
}

template<typename First, typename R = expression_t<constant, First, multiply>>
symbol<R> operator*(double lhs, First rhs) {
    return { R{ symbol<constant>{constant{lhs}}, symbol<First>{rhs} }};
}

template<typename First, typename R = expression_t<First, constant, divide>>
symbol<R> operator/(First lhs, double rhs) {
    return { R{ symbol<First>{lhs}, symbol<constant>{constant{rhs}} }};
}

template<typename First, typename R = expression_t<constant, First, divide>>
symbol<R> operator/(double lhs, First rhs) {
    return { R{ symbol<constant>{constant{lhs}}, symbol<First>{rhs} }};
}

template<typename Expression>
double integrate(Expression& e, double low=0, double high = 1, double epsilon = 0.001) {
     double auc1 = 0, auc2 = 0;
     double running_x = low;
     while ( running_x < high ) {
         auc1 += e(running_x) * epsilon;
         running_x += epsilon;
         auc2 += e(running_x) * epsilon;
     }

     return (auc1 + auc2)/2;
 }

#include <iostream>

int main() {
    variable x;

    // magic begins here :v
    auto f = x*x*x + 10.0;
    auto g = x*x + 3.0*x + 10.0;
    auto h = f * 10.0; // composed :)
    std::cout << f(10) << '\n' << g(5) << '\n' << h(5) << '\n'
              << integrate(f, 0, 1) << '\n';
}
