#include <iostream>
#include <typeinfo>
#include <string>
#include <cxxabi.h>

#include <boost/spirit/include/karma.hpp>

namespace karma=boost::spirit::karma;

template <typename Expr, typename Iterator = boost::spirit::unused_type>
struct attribute_of_karma_component
{
    typedef typename boost::spirit::result_of::compile<karma::domain, Expr>::type parser_expression_type;
    typedef typename boost::spirit::traits::attribute_of<parser_expression_type, boost::spirit::unused_type, Iterator>::type type;
};

template <typename T>
void display(T const &)
{
    typedef typename attribute_of_karma_component<T>::type type;
    std::cout << typeid(type).name() << std::endl;
}


int main ()
{
   using namespace karma;
   rule<std::back_insert_iterator<std::string>,boost::fusion::vector2<long,boost::optional<long>>()> range_part, range_part2;
   range_part  %= no_delimit[ulong_ << -(lit(":") << ulong_)];
   range_part2 %= ulong_ << -(lit(":") << ulong_);
   
   display(no_delimit[range_part << -(lit("-") << range_part)] << -(lit("<<") << ulong_));
   display(no_delimit[range_part << -(lit("-") << range_part) << -(lit("<<") << ulong_)]);
   display(range_part2 << -(lit("-") << range_part2) << -(lit("<<") << ulong_));
}
