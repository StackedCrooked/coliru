#define BOOST_SPIRIT_USE_PHOENIX_V3
//#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi  = boost::spirit::qi;
namespace phx = boost::phoenix;

namespace asmast
{
    typedef std::string label;
}

template <typename=void> struct my_error_handler {
    my_error_handler() = default;
    my_error_handler(my_error_handler const&) = delete;

    template<typename...> struct result { typedef void type; };
    template<typename... T> void operator()(T&&...) const { 
        std::cerr << "my_error_handler invoked " << proof++ << "\n";
    }
    mutable int proof = 0;
};

template <typename It, typename Skipper = qi::blank_type>
    struct parser : qi::grammar<It, Skipper>
{
    parser() : 
        parser::base_type(start),
        err_handler(),
        err_handler_(phx::ref(err_handler))
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

#if 0
        on_error<fail>(function,       phx::bind(phx::ref(err_handler), L"Error: Expecting ", _4, _3));
        on_error<fail>(start,          phx::bind(phx::ref(err_handler), L"Error: Expecting ", _4, _3));
        on_error<fail>(gr_instruction, phx::bind(phx::ref(err_handler), L"Error: Expecting ", _4, _3));
#else
        on_error<fail>(function,       err_handler_(L"Error: Expecting ", _4, _3));
        on_error<fail>(start,          err_handler_(L"Error: Expecting ", _4, _3));
        on_error<fail>(gr_instruction, err_handler_(L"Error: Expecting ", _4, _3));
#endif
        // more on_error<fail>s...

        BOOST_SPIRIT_DEBUG_NODES((start)(function)(gr_instruction)(gr_operands)(gr_identifier)(gr_operand)(gr_string));
    }

    my_error_handler<> err_handler;
    phx::function<decltype(phx::ref(err_handler))> err_handler_;
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

        std::cout << "The 'proof' in the err_handler instance is: " << p.err_handler.proof << "\n";
        return ok;
    } catch(const qi::expectation_failure<It>& e)
    {
        std::string frag(e.first, e.last);
        std::cerr << e.what() << "'" << frag << "'\n";
    }

    return false;
}
