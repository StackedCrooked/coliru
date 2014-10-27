#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix.hpp>

typedef std::pair<std::string, std::string> pair_type;

BOOST_FUSION_ADAPT_STRUCT_NAMED(
    pair_type const, pair_as_vkv,
	(std::string, second)
	(std::string, first)
	(std::string, second)
)

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
	karma::rule<OutputIterator, boost::fusion::adapted::pair_as_vkv()> pair;
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