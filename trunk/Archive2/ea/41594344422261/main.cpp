#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/fusion/include/std_pair.hpp>
#include <boost/fusion/include/nview.hpp>
#include <boost/spirit/include/karma.hpp>

typedef std::pair<std::string, std::string> pair_type;

typedef boost::fusion::result_of::as_nview<pair_type const, 1,0,1 >::type pair_as_vkv;

namespace karma = boost::spirit::karma;
namespace phx = boost::phoenix;

template <typename OutputIterator>
struct keys_and_values : karma::grammar<OutputIterator, std::vector<pair_type>()>
{
	keys_and_values() : keys_and_values::base_type(query)
	{
		query = *pair;
		pair = karma::string << ' ' << karma::string << ' ' << karma::string << karma::eol;
	}
	karma::rule<OutputIterator, std::vector<pair_type>()> query;
	karma::rule<OutputIterator, pair_as_vkv()> pair;
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