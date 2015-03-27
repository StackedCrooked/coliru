#include <algorithm>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/multi_array.hpp>
#include <iostream>
#include <fstream>
#include <iterator>

typedef boost::numeric::ublas::matrix<float> matrix;
namespace karma = boost::spirit::karma;

int main()
{
    matrix m1(4, 5);
    std::fill(m1.data().begin(), m1.data().end(), 1);

    using namespace karma;
    std::ofstream("file.txt") << 
        format(auto_ % '\t' % eol, boost::const_multi_array_ref<float, 2>(&*m1.data().begin(), boost::extents[4][5])) << "\n";
}
