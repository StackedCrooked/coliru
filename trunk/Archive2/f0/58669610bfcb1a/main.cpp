#include <boost/function_output_iterator.hpp>
#include <boost/range.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/phoenix.hpp>

namespace phx = boost::phoenix;
using namespace phx::arg_names;

struct TIPAddressDescription {
    int i;
    bool operator<(TIPAddressDescription const& other) const { return i < other.i; }
};

struct THNNetIface { 
    THNNetIface(TIPAddressDescription const& other) : i(other.i) {}
    int i;
};

struct HNInfoComparator {
    template <typename T, typename U> bool operator()(T const&, U const& u) const { return false; /*TODO*/ }
};

int main() {
    std::set<TIPAddressDescription> iface, ip;

    std::vector<THNNetIface> delIfaces;

    boost::set_difference(
            iface, ip,
            boost::make_function_output_iterator(
                phx::push_back(phx::ref(delIfaces), phx::construct<THNNetIface>(arg1))),
            HNInfoComparator()
        );
}
