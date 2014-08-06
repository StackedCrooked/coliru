#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_statement.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/repository/include/qi_iter_pos.hpp>

#include <iostream>
#include <string>
#include <vector>

namespace client
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    namespace phoenix = boost::phoenix;

    struct double_w_pos
    {
        double_w_pos(double d, size_t p) : d(d), pos(p) {}
        double d;
        size_t pos;
    };

    
    template <typename Iterator>
    bool parse_numbers(Iterator first, Iterator last, std::vector<double_w_pos>& v)
    {
        using qi::double_;
        using qi::phrase_parse;
        using qi::_1;
        using ascii::space;
        using phoenix::at_c;
        using phoenix::push_back;
        using phoenix::begin;
        using boost::spirit::repository::qi::iter_pos;
        
        bool r = phrase_parse(first, last,
            (
                qi::lexeme[(iter_pos >> double_ % ',')[push_back(phoenix::ref(v), 
                                                         phoenix::construct<double_w_pos>(qi::_2, 
                                                                                          (size_t)(qi::_1 - first)))] ]
            )
            ,
            space);

        if (first != last)
            return false;
        return r;
    }
}

int main()
{
    std::vector<client::double_w_pos> v;
    std::string str = "2.0, 3.45, 5.67, 2.08";

    client::parse_numbers(str.begin(), str.end(), v);
    
    for(auto i : v)
        std::cout << i.d << " at " << i.pos << ", ";
    std::cout << std::endl;
    
    return 0;
}