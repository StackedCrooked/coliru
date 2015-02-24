#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <sstream>

using namespace boost::archive;

static bool equal_or_nan(double a, double b) {
    return (std::isnan(a) && std::isnan(b)) || a==b;
}

template <typename IA, typename OA, 
         bool withNan   = true,
         bool withInf   = true,
         bool withRange = true>
bool perform_test() 
{
    std::vector<double> const v {
        withRange? std::numeric_limits<double>::min()       : 0,
        withRange? std::numeric_limits<double>::max()       : 0,
        withRange? std::numeric_limits<double>::epsilon()   : 0,
        withNan?   std::numeric_limits<double>::quiet_NaN() : 0,
        withInf?   std::numeric_limits<double>::infinity()  : 0,
        withInf? - std::numeric_limits<double>::infinity()  : 0,
    };

    std::stringstream ss;
    {
        OA oa(ss);
        oa << boost::serialization::make_nvp("element", v);
    }

    try
    {
        IA ia(ss);
        std::vector<double> w;
        ia >> boost::serialization::make_nvp("element", w);

        return std::equal(v.begin(), v.end(), w.begin(), equal_or_nan);
    } catch(...) {
        return false;
    }
}

static constexpr bool use_inf = true, use_nan = true, use_range = true;
static constexpr bool no_inf  = false, no_nan = false, no_range = false;

using BIA = boost::archive::binary_iarchive;
using BOA = boost::archive::binary_oarchive;
using TIA = boost::archive::text_iarchive;
using TOA = boost::archive::text_oarchive;
using XIA = boost::archive::xml_iarchive;
using XOA = boost::archive::xml_oarchive;

int main() {

    // supported:
    assert((perform_test<BIA,  BOA, use_nan, use_inf, use_range>()));
    assert((perform_test<XIA,  XOA, no_nan,  no_inf,  use_range>()));
    assert((perform_test<TIA,  TOA, no_nan,  no_inf,  use_range>()));

    // not supported:
    assert(!(perform_test<XIA, XOA, no_nan,  use_inf>()));
    assert(!(perform_test<TIA, TOA, no_nan,  use_inf>()));

    assert(!(perform_test<XIA, XOA, use_nan, no_inf>()));
    assert(!(perform_test<TIA, TOA, use_nan, no_inf>()));

}
