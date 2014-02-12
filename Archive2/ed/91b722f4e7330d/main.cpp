#include <boost/any.hpp>
#include <boost/spirit/include/qi.hpp>

#include <iostream>
#include <string>

template <typename Iterator>
struct parser : boost::spirit::qi::grammar<Iterator, boost::any, boost::spirit::qi::ascii::space_type>
{
    parser() : parser::base_type(start)
    {
        start %= boost::spirit::qi::int_;
    }

    boost::spirit::qi::rule<Iterator, boost::any, boost::spirit::qi::ascii::space_type> start;
};

int main()
{
    const std::string input_data("1");

    boost::any var = 0;
    auto itr = input_data.begin();
    auto end = input_data.end();
    parser<decltype(itr)> g;
    bool res = boost::spirit::qi::phrase_parse(itr, end, g, boost::spirit::ascii::space, var);
    if (res && itr == end)
    {
        std::cout << "Parsing succeeded \n";
        try
        {
            std::cout << boost::any_cast<int>(var) << '\n';
        }
        catch (const boost::bad_any_cast& ex)
        {
            std::cerr << ex.what() << '\n';
        }
    }
    else
    {
        std::cout << "Parsing failed \n";
    }
}
