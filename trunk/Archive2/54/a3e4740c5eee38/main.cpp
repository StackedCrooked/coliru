#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_real.hpp>
#include <boost/tuple/tuple_io.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

int main()
{
    using qi::double_;
	using qi::int_;
	using qi::lit;

	std::string const path = "42,43";
	{
		boost::tuple<double, double> result;

		std::string::const_iterator iter = path.begin();
		std::string::const_iterator end = path.end();
		bool r = boost::spirit::qi::parse(iter, end, double_ >> lit(',') >> double_, result);
        std::cout << "r = " << r << std::endl;
        std::cout << "iter == end = " << (iter == end) << std::endl;
		std::cout << "Result: " << result.get<0>() << " , " << result.get<1>() << std::endl;
	}
}
