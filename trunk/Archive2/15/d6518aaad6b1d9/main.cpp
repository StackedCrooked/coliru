#include <boost/spirit/include/qi.hpp>
#include <fstream>

namespace qi = boost::spirit::qi;

int main()
{
    std::ifstream ifs("one.txt");
    ifs >> std::noskipws;

    std::vector< std::string > people;
    boost::spirit::istream_iterator first(ifs), last;

    /*
     * 1. match list of items separated by newlines 
     * 2. '-' makes the item optional (ignoring blank lines)
     * 3. `lexeme` includes whitespace inside the subexpression (but it does still pre-skip, so lines with only whitespace count as empty lines; use `no_skip` if you don't want preskip to happen)
     * 4. `+` requires at least 1 match, so empty names are not considered a name
     * 5. the `blank` skipper skips whitespaces, but not newlines; this is because newlines are significant to your grammar. Also note that the `lexeme` still keeps the internal whitespace
     */
    if (qi::phrase_parse(
    //      ^ ----- use a skipper to parse phrases whith a skipper (`qi::blank` here)
                first, last,
                -qi::as_string[qi::lexeme[+(qi::char_ - qi::eol)]] % qi::eol,
    //          |                  |      |                          ^---- 1.
    //          +---- 2.           |      +---- 4.
    //       5. ----v       3. ----+      
                qi::blank,
                people))
    {
        std::cout << "Size = " << people.size() << std::endl;

        for (auto person : people)
        {
            std::cout << person << std::endl;
        }
    }
}
