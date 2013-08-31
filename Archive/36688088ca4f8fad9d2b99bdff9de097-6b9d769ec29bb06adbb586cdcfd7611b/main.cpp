// Options:
//#define WRONG

#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

#include <boost/fusion/adapted/struct/define_struct_inline.hpp>
#include <boost/fusion/include/define_struct_inline.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;


    namespace example
    {
        struct identifier_result
        {
            std::string name;
        };
    }
    
#ifdef WRONG

BOOST_FUSION_ADAPT_STRUCT(
        example::identifier_result,
        (std::string, name)
        )
#else

namespace boost{ namespace spirit{ namespace traits
{
    template <>
	struct is_container<example::identifier_result> : boost::mpl::true_
	{};
	
	template <>
	struct container_value<example::identifier_result>
	{
		typedef char type;
	};
	
	template <>
	struct push_back_container<example::identifier_result,char>
	{
		static bool call(example::identifier_result& cont, char val)
		{
			cont.name.push_back(val);
			return true;
		}
	};
}}}

#endif






int main()
{
    using namespace example;
    
    std::string input=" validId1 ";
    auto&& first = input.cbegin();
    auto&& last = input.cend();

    qi::rule<std::string::const_iterator,identifier_result()> parser = qi::alpha >> *qi::alnum;
    auto&& skipper = qi::space;

    identifier_result result;
    qi::phrase_parse(first, last, parser, skipper, result);

    std::cout << "Result of the parse is: \'"
              << result.name << "\'" << std::endl;

}