#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/repository/include/qi.hpp>

namespace qi = boost::spirit::qi;

namespace parsing {
    namespace detail {
        template <typename Iterator>
        struct Skipper : qi::grammar<Iterator> {
            Skipper() : Skipper::base_type(_skip_rule)
            {
                _comment  =
                    boost::spirit::repository::confix("/*", "*/")    [*(qi::char_ - "*/")]     // Multi-line
                | boost::spirit::repository::confix("//", qi::eol) [*(qi::char_ - qi::eol)]  // Single-line
                ;

                _skip_rule = qi::ascii::space | _comment;
            }
        private:
            qi::rule<Iterator> _comment, _skip_rule;
        };

        template <typename Iterator, typename Skipper = Skipper<Iterator> >
        struct Grammar : qi::grammar<Iterator, Skipper> {
            Grammar() : Grammar::base_type(expression)
            {
                scalar_literal = qi::uint_ | qi::int_;
                identifier     = (qi::alpha | '_') >> *(qi::alnum | '_');
                // Rules
                operand        = (scalar_literal | identifier | ('(' >> expression >> ')'));
                expression     = operand;
            }
        private:
            qi::rule<Iterator>          scalar_literal, identifier; // Tokens
            qi::rule<Iterator, Skipper> operand,        expression; // Rules
        };
    }

    template <typename Iterator, typename Skipper = detail::Skipper<Iterator> >
    struct facade {
        template <typename Range> static bool parse(Range const& input) {
            Iterator f = boost::begin(input), l = boost::end(input);
            return qi::phrase_parse(f, l, _parser, _skipper);
        }

      private:
        static const detail::Skipper<Iterator>          _skipper;
        static const detail::Grammar<Iterator, Skipper> _parser;
    };

    template <class I, class S> const detail::Skipper<I>    facade<I,S>::_skipper = {};
    template <class I, class S> const detail::Grammar<I, S> facade<I,S>::_parser  = {};
}

int main() {
    using It = std::string::const_iterator;
    std::string const input = "(123)";

    It f = input.begin(), l = input.end();

    bool ok = parsing::facade<It>::parse(input);

    if (ok)   std::cout << "Parse success\n";
    else      std::cout << "Parse failed\n";
    if (f!=l) std::cout << "Remaining input: '" << std::string(f,l) << "'\n";
}
