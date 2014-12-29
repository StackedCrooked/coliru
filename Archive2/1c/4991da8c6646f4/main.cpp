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

template <typename... Ts>
using column_variant = typename boost::make_variant_over<
    typename boost::mpl::transform<
            boost::mpl::vector<Ts...>, 
            Column<boost::mpl::_1>,
            boost::mpl::back_inserter<boost::mpl::vector<> > 
        >::type
    >::type;

int main() {
    column_variant<int, float, std::string> v(std::string("hello world"));
    std::cout << v;
}
