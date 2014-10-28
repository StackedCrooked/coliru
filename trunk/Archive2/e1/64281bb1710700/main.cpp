#include <boost/phoenix.hpp>

namespace p = boost::phoenix;
using namespace p::arg_names;

int main()
{
    auto p = p::val(42);
    return p() + p(/*ignored:*/77);
}