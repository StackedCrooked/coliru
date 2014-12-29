#include <boost/variant.hpp>
#include <boost/mpl/vector.hpp>
#include <iostream>

template <typename T> struct Column { 
    T v; 
    Column(T const& v) : v(v) {}
    friend std::ostream& operator<<(std::ostream& os, Column<T> const& cv) {
        return os << cv.v;
    }
};

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
    make_column_variant<mpl::vector<int, float, std::string> >::type v(std::string("hello world"));
    std::cout << v;
}
