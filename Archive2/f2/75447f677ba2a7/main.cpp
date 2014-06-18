#include <boost/phoenix/phoenix.hpp>
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
    double operator()(double d) const
    {
        return std::sqrt(d);
    }
};


boost::phoenix::function<sqrt_impl> sqrt;


auto get_x1 = (-b + sqrt(D)) / (2 * a);
auto get_x2 = (-b - sqrt(D)) / (2 * a);


struct solve_impl
{
    std::pair<double, double> operator()(double a, double b, double c) const
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