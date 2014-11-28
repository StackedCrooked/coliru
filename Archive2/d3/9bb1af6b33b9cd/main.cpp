#include <boost/spirit/include/karma.hpp>
#include <boost/range.hpp>

int main() {
    using namespace boost::spirit::karma;
    std::cout << format_delimited(columns(3) [ *auto_ ], ' ', boost::make_iterator_range(std::istream_iterator<std::string>(std::cin), {}));
}
