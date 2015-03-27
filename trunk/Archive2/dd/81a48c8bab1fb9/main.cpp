#include <algorithm>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/spirit/include/karma.hpp>
#include <iostream>

typedef boost::numeric::ublas::matrix<float> matrix;
namespace karma = boost::spirit::karma;

int main() {
    matrix m1(4, 5);
    std::fill(m1.data().begin(), m1.data().end(), 1);

    using namespace karma;
    std::cout << format(columns(m1.size2()*2) [ auto_ % '\t' ], m1.data()) << "\n";
}
