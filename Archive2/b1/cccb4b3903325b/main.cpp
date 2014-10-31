#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/struct.hpp>
#include <boost/fusion/algorithm/auxiliary/copy.hpp>
#include <boost/fusion/include/io.hpp>
#include <iostream>

namespace fus = boost::fusion;

struct X {
    int i;
    double d;
    std::string s;
    std::string extra;
};

BOOST_FUSION_ADAPT_STRUCT(X, (int,i)(double,d)(std::string,s)(std::string,extra))

int main()
{
    fus::vector<int, double, std::string> src(42, 3.14, "hello");

    X dst { -1, -1, "filler", "filler" };

    fus::copy(src, dst);

    std::cout << fus::as_vector(dst);
}
