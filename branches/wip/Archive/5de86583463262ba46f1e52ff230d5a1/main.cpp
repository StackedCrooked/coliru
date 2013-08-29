#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/phoenix/function.hpp>
#include <cassert>
#include <cmath>
#include <iostream>
#include <utility>


namespace {


// a, b and c represent the equation arguments: ax2 + bx + c
boost::phoenix::expression::argument<1>::type a;
boost::phoenix::expression::argument<2>::type b;
boost::phoenix::expression::argument<3>::type c;


auto D = b * b - 4 * a * c;


struct sqrt_impl
{
    template<typename Arg>
    struct result { typedef double type; };

    template<typename Arg>
    typename result<Arg>::type operator()(Arg n)
    {
        return std::sqrt(static_cast<typename result<Arg>::type>(n));
    }
};


boost::phoenix::function<sqrt_impl> sq;


/**
 * @brief get_x1 generates the first result of the equation.
 * @return lazy return value.
 * @example
 *     auto value = get_x1(-1, 2, -1); // get the lazy result
 *     double x1 = value(); // get the actual result
 */
auto get_x1 = (-b + sq(D)) / (2 * a);

/**
 * @brief get_x1 generates the second result of the equation.
 * @return lazy return value.
 */
auto get_x2 = (-b - sq(D)) / (2 * a);


struct solve_impl
{
    typedef std::pair<double, double> result_type;

    struct result { typedef result_type type; };

    result_type operator()(double a, double b, double c) const
    {
        return std::make_pair(get_x1(a, b, c), get_x2(a, b, c));
    }
};


boost::phoenix::function<solve_impl> solve_quadratic_equation;


} // anonymous namespace


int main()
{
    auto p = solve_quadratic_equation(1, -1, -2)();
    std::cout << p.first << ", " << p.second << std::endl;
}