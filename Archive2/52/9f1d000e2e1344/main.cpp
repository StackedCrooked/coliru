#include <boost/numeric/ublas/matrix.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/multi_array.hpp>
#include <iostream>

typedef boost::numeric::ublas::matrix<float> matrix;
namespace karma = boost::spirit::karma;

template <typename T> boost::const_multi_array_ref<T, 2> make_view(boost::numeric::ublas::matrix<T> const& m) {
    return  boost::const_multi_array_ref<T,2> (
            &*m.data().begin(),
            boost::extents[m.size1()][m.size2()]
        );
}

int main()
{
    matrix m1(4, 5);
    std::fill(m1.data().begin(), m1.data().end(), 1);

    using namespace karma;
    std::cout << format(auto_ % '\t' % eol, make_view(m1)) << "\n";
}
