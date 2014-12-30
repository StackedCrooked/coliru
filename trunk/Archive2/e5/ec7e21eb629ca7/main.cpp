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
using make_column_variant = typename boost::make_variant_over<boost::mpl::vector<Column<Ts>...>>::type;

int main() {
    make_column_variant<int, float, std::string> v(std::string("hello world"));
    std::cout << v;
}
