#include <iostream>
#include <typeinfo>

#include <boost/spirit/include/qi.hpp>

namespace qi=boost::spirit::qi;

template <typename Expr, typename Iterator = boost::spirit::unused_type>
struct attribute_of_qi_component
{
    typedef typename boost::spirit::result_of::compile<
		qi::domain, Expr
	>::type parser_expression_type;

	typedef typename boost::spirit::traits::attribute_of<
		parser_expression_type, 
		boost::spirit::unused_type, Iterator
	>::type type;
};

template <typename Expr>
void display_attr( const Expr& )
{
	std::cout << typeid(typename attribute_of_qi_component<Expr>::type).name() << std::endl;
}

int main()
{
	display_attr(qi::int_ ^ qi::int_ ^ qi::int_ ^ qi::int_ ^ qi::eps(false));
	display_attr(boost::spirit::compile<qi::domain>(qi::int_ ^ boost::spirit::compile<qi::domain>(qi::int_ ^ boost::spirit::compile<qi::domain>(qi::int_ ^ boost::spirit::compile<qi::domain>(qi::int_ ^ qi::eps(false))))));
}

