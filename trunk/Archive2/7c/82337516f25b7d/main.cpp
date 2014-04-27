#include <boost/spirit/include/karma.hpp>
#include <boost/iterator/function_input_iterator.hpp>
#include <boost/random.hpp>

boost::random::variate_generator<boost::mt19937, boost::uniform_int<int> > rdngen(
        boost::mt19937(), boost::uniform_int<int>(1, 1000));

int main() {
    auto f = boost::make_function_input_iterator(rdngen, 1),
         l = boost::make_function_input_iterator(rdngen, 100);

    auto range = boost::make_iterator_range(f, l);

    using namespace boost::spirit::karma;
    std::cout << format_delimited(columns(5) [ right_align(10) [ *auto_ ] ], " ", range) << "\n";

}
