#include <boost/variant.hpp>
#include <boost/mpl/vector.hpp>

template <typename T> struct Column { T v; };

/* c++03 helper */
namespace mpl = boost::mpl;

template <typename Seq>
struct make_column_variant
{
    typedef typename mpl::transform<
        Seq, 
        Column<mpl::_1>,
        mpl::back_inserter<mpl::vector<> > 
            >::type columns;

    typedef typename boost::make_variant_over<columns>::type type;
};

int main() {
    make_column_variant<mpl::vector<int, float, std::string> >::type v("hello world");
}
