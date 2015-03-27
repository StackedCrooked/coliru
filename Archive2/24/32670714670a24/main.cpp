#include <boost/numeric/ublas/matrix.hpp>
#include <boost/spirit/include/karma.hpp>
#include <iostream>
#include <algorithm>

typedef boost::numeric::ublas::matrix<float> matrix;
namespace karma = boost::spirit::karma;

int main() {
    matrix m1(4, 5);
    std::fill(m1.data().begin(), m1.data().end(), 1);

    using namespace karma;
    std::ofstream("file.txt") << format_delimited(columns(m1.size2()) [auto_], '\t', m1.data()) << "\n";
}
