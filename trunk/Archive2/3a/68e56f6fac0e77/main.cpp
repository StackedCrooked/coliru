#include <boost/fusion/include/std_pair.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace karma = boost::spirit::karma;
namespace phx = boost::phoenix;
typedef std::pair<std::string, std::string > pair_type;

template <typename OutputIterator>    
struct keys_and_values : karma::grammar<OutputIterator, std::vector<pair_type>()>
{
    keys_and_values() : keys_and_values::base_type(query)
    {
        query =  *pair;
        // here is the scarily horrible part
        pair  =  karma::string[karma::_1=phx::at_c<1>(karma::_val)] << ' ' << karma::string[karma::_1=phx::at_c<0>(karma::_val)] << ' ' << karma::string[karma::_1=phx::at_c<1>(karma::_val)] << karma::eol;
    }
karma::rule<OutputIterator, std::vector<pair_type>()> query;
karma::rule<OutputIterator, pair_type()> pair;
};

int main(int argc, char *argv[])
{
    typedef std::back_insert_iterator<std::string> sink_type;

    std::vector<pair_type> v;
    v.push_back(pair_type("key1", "value1"));
    v.push_back(pair_type("key2", "value2"));
    v.push_back(pair_type("key3", "value3"));

    std::string generated;
    sink_type sink(generated);
    keys_and_values<sink_type> g;

    karma::generate(sink, g, v);

    std::cout << generated << std::endl;

    return 0;
}
