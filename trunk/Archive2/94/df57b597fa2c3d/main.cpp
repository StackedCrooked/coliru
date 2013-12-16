#define BOOST_SPIRIT_USE_PHOENIX_V3
#define BOOST_SPIRIT_UNICODE
#include <boost/regex/pending/unicode_iterator.hpp>
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/phoenix/function/adapt_function.hpp>

namespace phx = boost::phoenix;

#include <boost/spirit/include/qi.hpp>

namespace qi       = boost::spirit::qi;
namespace encoding = boost::spirit::unicode;

#include <boost/spirit/repository/include/qi_iter_pos.hpp>
#include <boost/spirit/include/support_line_pos_iterator.hpp>

#include <iostream>
#include <string>

//==============================================================================
std::string to_utf8(const std::u32string& input) {
  return std::string(
      boost::u32_to_u8_iterator<std::u32string::const_iterator>(input.begin()),
      boost::u32_to_u8_iterator<std::u32string::const_iterator>(input.end()));
}

BOOST_PHOENIX_ADAPT_FUNCTION(std::string, to_utf8_, to_utf8, 1)

//==============================================================================
int main() {
    std::string input(u8"Hallo äöüß\n¡Bye! ✿➂➿♫");

    typedef boost::spirit::line_pos_iterator<std::string::const_iterator> source_iterator;

    typedef boost::u8_to_u32_iterator<source_iterator> iterator_type;

    source_iterator soi(input.begin()), 
                    eoi(input.end());
    iterator_type   first(soi), 
                    last(eoi);

    qi::rule<iterator_type, std::u32string()> string_u32 = +encoding::graph;
    qi::rule<iterator_type, std::string()>    string     = string_u32 [qi::_val = to_utf8_(qi::_1)];

    std::vector<boost::iterator_range<iterator_type> > ast;
    // note the trick with `raw` to expose the iterators
    bool result = qi::phrase_parse(first, last, *qi::raw[ string ], encoding::space, ast);

    if (result) {
        for (auto const& range : ast)
        {
            source_iterator 
                base_b(range.begin().base()), 
                base_e(range.end().base());
            auto lbound = get_line_start(soi, base_b);

            // RAW access to the base iterators:
            std::cout << "Fragment: '" << std::string(base_b, base_e) << "'\t" 
                << "raw: L" << get_line(base_b) << ":" << get_column(lbound, base_b, /*tabs:*/4)
                <<     "-L" << get_line(base_e) << ":" << get_column(lbound, base_e, /*tabs:*/4);

            // "cooked" access:
            auto line = get_current_line(lbound, base_b, eoi);
            // std::cout << "Line: '" << line << "'\n";

            // iterator_type is an alias for u8_to_u32_iterator<...>
            size_t cur_pos = 0, start_pos = 0, end_pos = 0;
            for(iterator_type it = line.begin(), _eol = line.end(); ; ++it, ++cur_pos)
            {
                if (it.base() == base_b) start_pos = cur_pos;
                if (it.base() == base_e) end_pos   = cur_pos;

                if (it == _eol)
                    break;
            }
            std::cout << "\t// in u32 code _units_: positions " << start_pos << "-" << end_pos << "\n";
        }
        std::cout << "\n";
    } else {
        std::cout << "Failure" << std::endl;
    }

    if (first!=last)
    {
        std::cout << "Remaining: '" << std::string(first, last) << "'\n";
    }
}
