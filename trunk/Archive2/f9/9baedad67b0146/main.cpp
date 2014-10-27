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
        // here is the interesting part
        pair  =  karma::eps[_value=phx::at_c<1>(karma::_val), _key=phx::at_c<0>(karma::_val)] <<
                 karma::string(_value) << ' ' << karma::string(_key) << ' ' << karma::string(_value) << karma::eol;
    }
karma::rule<OutputIterator, std::vector<pair_type>()> query;
karma::rule<OutputIterator, pair_type(), karma::locals<std::string,std::string> > pair;
karma::_a_type _value;
karma::_b_type _key;
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
