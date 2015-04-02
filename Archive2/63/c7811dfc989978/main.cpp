#include <boost/spirit/include/karma.hpp>

int main() {
    using namespace boost::spirit::karma;
    std::cout << format_delimited(auto_ << auto_ << auto_, ',', 1, "abc", 3.14f);
}
