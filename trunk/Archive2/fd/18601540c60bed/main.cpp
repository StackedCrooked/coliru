#include <boost/spirit/include/qi.hpp>

template <typename Int>
void do_test() {
    for (Int const testcase : { std::numeric_limits<Int>::min(), Int(), std::numeric_limits<Int>::max() }) {
        auto const input = std::to_string(testcase);
        auto f(input.begin()), l(input.end()); 

        Int parsed = 0;
        bool ok = boost::spirit::qi::parse(f, l, boost::spirit::qi::auto_, parsed);

        if (!ok || f!=l)
            throw std::runtime_error("parse error");

        std::cout << std::boolalpha << (testcase==parsed) << "\t" << testcase << " -> " << parsed << "\n";
    }
}

int main() {
    do_test<int16_t>();  do_test<uint16_t>();
    do_test<int32_t>();  do_test<uint32_t>();
    do_test<int64_t>();  do_test<uint64_t>();
    do_test<intmax_t>(); do_test<uintmax_t>();
}