#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/repository/include/qi_distinct.hpp>

namespace qi = boost::spirit::qi;
namespace sr = boost::spirit::repository::qi;

using It = std::string::const_iterator;
qi::rule<It, std::string()> ident_ = sr::distinct(qi::char_("a-z0-9_")) [ qi::alpha >> *(qi::char_("a-z0-9_")) ];

int main() {
    for(std::string const input : {
            "Execute no_parameter_statement",
            "Execute stmtname using @a,@b;"
            })
    {
        std::cout << "-----------------------------------------\n";
        std::cout << "Parsing '" << input << "'\n";

        std::string statement_name;
        std::vector<std::string> parameters;

        auto f(input.begin()), l(input.end());
        bool ok = qi::phrase_parse(f,l,qi::no_case[ 
                sr::distinct(qi::graph) ["execute"] 
                >> ident_ 
                >> -(sr::distinct(qi::graph) ["using"] >> 
                        ('@' >> ident_) % ','
                    )
                >> -qi::lit(';') >> qi::eoi
            ],
            qi::space,
            statement_name,
            parameters
        );

        if (ok) {
            std::cout << "Parse success\n";

            std::cout << "statement_name: " << statement_name << "\n";
            std::cout << parameters.size() << " parameters:\n";
            for(auto const& p : parameters)
                std::cout << "\t@" << p << "\n";
        } else {
            std::cout << "Parse failed\n"; 
        }

        if (f!=l)
            std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
    }
}
