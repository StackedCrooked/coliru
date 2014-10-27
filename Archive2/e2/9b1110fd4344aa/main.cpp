#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/fusion/include/std_pair.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace karma = boost::spirit::karma;
typedef std::pair<std::string, std::string> pair_type;

template <typename OutputIterator> struct keys_and_values : karma::grammar<OutputIterator, std::vector<pair_type>()> {
    keys_and_values() : keys_and_values::base_type(query) {
        query = *pair;
        pair %= karma::string [ karma::_a = karma::_1 ] << ' ' << karma::string << ' ' << karma::string(karma::_a) << karma::eol;
    }
    karma::rule<OutputIterator, std::vector<pair_type>() > query;
    karma::rule<OutputIterator, pair_type(), karma::locals<std::string>> pair;
};

int main() {
    typedef std::back_insert_iterator<std::string> sink_type;

    std::vector<pair_type> v;
    v.push_back(pair_type("key1", "value1"));
    v.push_back(pair_type("key2", "value2"));
    v.push_back(pair_type("key3", "value3"));

    std::string generated;
    sink_type sink(generated);
    keys_and_values<sink_type> g;

    bool result = karma::generate(sink, g, v);
    if (result)
        std::cout << generated << std::endl;
}
