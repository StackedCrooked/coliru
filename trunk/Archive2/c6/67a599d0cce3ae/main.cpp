#include <iostream>
#include <boost/spirit/include/karma_real.hpp>
#include <boost/spirit/include/karma_generate.hpp>

using namespace boost::spirit::karma;

// define a new real number formatting policy
template <typename Num>
struct MyPolicy : real_policies<Num> {
    // we want the numbers always to be in scientific format
    static int floatfield(Num /*n*/) { return std::ios_base::fixed; }
};

// define a new generator type based on the new policy
typedef real_generator<double, MyPolicy<double> > my_policy_type;
my_policy_type const my_policy = my_policy_type();

int main() {
    // use the new generator 
    std::ostreambuf_iterator<char> co(std::cout);
    generate(co, my_policy, 0.1);
}
