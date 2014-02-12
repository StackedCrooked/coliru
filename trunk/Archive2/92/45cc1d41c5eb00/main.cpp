#include <iostream>
#include <boost/math/distributions/binomial.hpp>
#include <boost/math/tools/roots.hpp>


class MyBinom {
public:
    MyBinom(int B, int N, int ans);

    double operator()(const double x) const;

private:
    int B;
    int N;
    double ans;
};

MyBinom::MyBinom(int B, int N, int ans) : B(B), N(N), ans(ans) {}

double MyBinom::operator()(const double x) const {
    boost::math::binomial dist(N, x);
    double distans = boost::math::cdf(dist, B) - ans;
    return distans;
}


int main()
{
    typedef std::pair<double, double> Result;

    MyBinom myBinom95(75, 4167, 0.95); // Create the Class with the unary operator.

    boost::uintmax_t max_iter=500; // Set max iterations.

    boost::math::tools::eps_tolerance<double> tol(30); //Set the eps tolerance.

    Result r1 = boost::math::tools::toms748_solve(myBinom95, 0., 1., tol, max_iter); // use the toms solve algorithm.

    std::cout << "Let's take a look at the root" << std::endl;
    std::cout << "root bracketed: [ " << r1.first  << " , " << r1.second            << " ]" << std::endl;
    std::cout << "f("                 << r1.first  << ")="  << myBinom95(r1.first)  << std::endl;
    std::cout << "f("                 << r1.second << ")="  << myBinom95(r1.second) << std::endl;
    std::cout << "max_iter="          << max_iter  << std::endl;
    return 0;
}
