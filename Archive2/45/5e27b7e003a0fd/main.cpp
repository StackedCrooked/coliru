#include <cmath>
#include <iostream>
#include <vector>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/stl/cmath.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm_ext/iota.hpp>

int main()
{
    using boost::iota;
	using namespace boost::adaptors;
	using namespace boost::phoenix::arg_names;
	using Vector = std::vector<double>;
	using std::fabs;
	using std::exp;

	Vector xs(10);
	iota(xs, 1.);
    
	auto ys = xs | transformed(exp(fabs(arg1)));
    
	for (auto y : ys) std::cout << y << '\n';
}
