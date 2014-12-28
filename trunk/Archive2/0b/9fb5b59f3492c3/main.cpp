#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/adapted.hpp>

namespace qi    = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

namespace ast {
    using module_path = std::vector<std::string>;
    struct value_path {
        module_path module;
        std::string   value_expr;
    };
}

BOOST_FUSION_ADAPT_STRUCT(ast::value_path, (ast::module_path, module)(std::string,value_expr))

template <typename Iter, typename Skipper = ascii::space_type>
struct value_path : qi::grammar<Iter, ast::value_path(), Skipper> {
    value_path() : value_path::base_type(start)
    {
        using namespace ascii;
        using qi::raw;

        lowercase_ident  = raw[ (lower | '_') >> *(alnum | '_' | '\'') ];
        module_path_item = raw[ upper >> *(alnum | '_' | '\'') ];
        module_path_     = module_path_item % '.';

        auto special_char = boost::proto::deep_copy(char_("-+!$%&*./:<=>?@^|~"));

        operator_name = qi::raw [
                  ('!'          >> *special_char)         /* branch 1     */
                | (char_("~?")  >> +special_char)         /* branch 2     */
                | (!char_(".:") >> +special_char)         /* branch 3     */
                | "mod"                                   /* branch 4     */
                | "lor" | "lsl" | "lsr" | "asr" | "or"    /* branch 5-9   */
                | "-."                                    /* branch 10    doesn't match because of branch 3   */
                | "!=" | "||" | "&&" | ":="               /* branch 11-14 doesn't match because of branch 1,3 */
             // | (special_char - char_("!$%./:?@^|~"))   /* "*+=<>&-" cannot match because of branch 3 */
            ]
            ;

        value_name_  = 
              lowercase_ident
            | '(' >> operator_name >> ')'
            ;

        start = -(module_path_ >> '.') >> value_name_;

        BOOST_SPIRIT_DEBUG_NODES((start)(module_path_)(value_name_)(module_path_item)(lowercase_ident)(operator_name))
    }
  private:
    qi::rule<Iter, ast::value_path(),  Skipper> start;
    qi::rule<Iter, ast::module_path(), Skipper> module_path_;

    // lexeme: (no skipper)
    qi::rule<Iter, std::string()> value_name_, module_path_item, lowercase_ident, operator_name;
};

int main()
{
    for (std::string const input : { 
            "Some.Module.Package.ident",
            "ident",
            "A.B.C_.mod",    // as lowercase_ident
            "A.B.C_.(mod)",  // as operator_name (branch 4)
            "A.B.C_.(!=)",   // as operator_name (branch 1)
            "(!)"            // as operator_name (branch 1)
            })
    {
        std::cout << "--------------------------------------------------------------\n";
        std::cout << "Parsing '" << input << "'\n";

        using It = std::string::const_iterator;
        It f(input.begin()), l(input.end());

        value_path<It> g;
        ast::value_path data;
        bool ok = qi::phrase_parse(f, l, g, ascii::space, data);
        if (ok) {
            std::cout << "Parse succeeded\n";
        } else {
            std::cout << "Parse failed\n";
        }

        if (f!=l)
            std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
    }
}
