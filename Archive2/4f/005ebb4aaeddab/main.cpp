#include <boost/any.hpp>
#include <boost/spirit/include/qi.hpp>

#include <iostream>
#include <string>

template <typename Iterator>
struct parser : boost::spirit::qi::grammar<Iterator, boost::any(), boost::spirit::qi::ascii::space_type>
{
    parser() : parser::base_type(start)
    {
        using namespace boost::spirit::qi;
        start %= int_ | as_string [ lexeme['"' >> +(char_ - '"') >> '"'] ]; // example: 0 or "str"
    }

    boost::spirit::qi::rule<Iterator, boost::any(), boost::spirit::qi::ascii::space_type> start;
};

int main()
{
    for (std::string const& input_data : { "\"str\"", "123" })
    {
        boost::any var = boost::none;
        auto itr = input_data.begin();
        auto end = input_data.end();
        parser<decltype(itr)> g;
        bool res = boost::spirit::qi::phrase_parse(itr, end, g, boost::spirit::ascii::space, var);
        if (res && itr == end)
        {
            std::cout << "Parsing succeeded \n";
            try { std::cout << boost::any_cast<int>        (var) << '\n'; } catch (const boost::bad_any_cast& ex) { std::cerr << ex.what() << '\n'; }
            try { std::cout << boost::any_cast<std::string>(var) << '\n'; } catch (const boost::bad_any_cast& ex) { std::cerr << ex.what() << '\n'; }
        }
        else
        {
            std::cout << "Parsing failed \n";
        }
    }
}
