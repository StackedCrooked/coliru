#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>

namespace qi    = boost::spirit::qi;

namespace asmast
{
    using label = std::string;
}

template <typename It, typename Skipper = qi::blank_type>
    struct parser : qi::grammar<It, Skipper>
{
    parser() : parser::base_type(start)
    {
        using namespace qi;

        start = lexeme["Func" >> !(alnum | '_')] > function;
        function = gr_identifier
                    >> "{"
                    >> -(
                              gr_instruction
                            | gr_label
                          //| gr_vardecl
                          //| gr_paramdecl
                        ) % eol
                    > "}";

        gr_instruction_names.add("Mov", unused);
        gr_instruction_names.add("Push", unused);
        gr_instruction_names.add("Exit", unused);

        gr_instruction = lexeme [ gr_instruction_names >> !(alnum|"_") ] > gr_operands;
        gr_operands = -(gr_operand % ',');

        gr_identifier = lexeme [ alpha >> *(alnum | '_') ];
        gr_operand    = gr_identifier | gr_string;
        gr_string     = lexeme [ '"' >> *("\"\"" | ~char_("\"")) >> '"' ];

        gr_newline = +( char_('\r')
                       |char_('\n')
                      );
                      
        gr_label = gr_identifier >> ':' > gr_newline;

        BOOST_SPIRIT_DEBUG_NODES((start)(function)(gr_instruction)(gr_operands)(gr_identifier)(gr_operand)(gr_string));
    }

  private:
    qi::symbols<char, qi::unused_type> gr_instruction_names;
    qi::rule<It, Skipper> start, function, gr_instruction, gr_operands, gr_operand, gr_string;
    qi::rule<It, qi::unused_type()> gr_newline;
    qi::rule<It, asmast::label(), Skipper> gr_label, gr_identifier;
};

int main()
{
    typedef boost::spirit::istream_iterator It;
    std::cin.unsetf(std::ios::skipws);
    It f(std::cin), l;

    parser<It, qi::blank_type> p;

    try
    {
        bool ok = qi::phrase_parse(f,l,p,qi::blank);
        if (ok)   std::cout << "parse success\n";
        else      std::cerr << "parse failed: '" << std::string(f,l) << "'\n";

        if (f!=l) std::cerr << "trailing unparsed: '" << std::string(f,l) << "'\n";
        return ok;
    } catch(const qi::expectation_failure<It>& e)
    {
        std::string frag(e.first, e.last);
        std::cerr << e.what() << "'" << frag << "'\n";
    }

    return false;
}
