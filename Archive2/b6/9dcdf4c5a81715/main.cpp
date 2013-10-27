//#define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/support_line_pos_iterator.hpp>
#include <iomanip>

namespace qi = boost::spirit::qi;
namespace phx= boost::phoenix;

typedef boost::spirit::line_pos_iterator<std::string::const_iterator> pos_iterator_t;

namespace ast
{
    namespace manip { struct LocationInfoPrinter; }

    struct LocationInfo {
        unsigned line, column, length;
        manip::LocationInfoPrinter printLoc() const;
    };

    struct Identifier     : LocationInfo {
        std::string name;
    };

    struct VarAssignment  : LocationInfo {
        Identifier id;
        int value;
    };

    struct SourceCode     : LocationInfo {
        Identifier function;
        std::vector<VarAssignment> assignments;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Completely unnecessary tweak to get a "poor man's" io manipulator going
    // so we can do `std::cout << x.printLoc()` on types of `x` deriving from
    // LocationInfo
    namespace manip {
        struct LocationInfoPrinter {
            LocationInfoPrinter(LocationInfo const& ref) : ref(ref) {}
            LocationInfo const& ref;
            friend std::ostream& operator<<(std::ostream& os, LocationInfoPrinter const& lip) {
                return os << lip.ref.line << ':' << lip.ref.column << ':' << lip.ref.length;
            }
        };
    }

    manip::LocationInfoPrinter LocationInfo::printLoc() const { return { *this }; }
    // feel free to disregard this hack
    ///////////////////////////////////////////////////////////////////////////
}

BOOST_FUSION_ADAPT_STRUCT(ast::Identifier,    (std::string, name))
BOOST_FUSION_ADAPT_STRUCT(ast::VarAssignment, (ast::Identifier, id)(int, value))
BOOST_FUSION_ADAPT_STRUCT(ast::SourceCode,    (ast::Identifier, function)(std::vector<ast::VarAssignment>, assignments))

struct error_handler_f {
    typedef qi::error_handler_result result_type;
    template<typename T1, typename T2, typename T3, typename T4>
        qi::error_handler_result operator()(T1 b, T2 e, T3 where, T4 const& what) const {
            std::cerr << "Error: expecting " << what << " in line " << get_line(where) << ": \n" 
                << std::string(b,e) << "\n"
                << std::setw(std::distance(b, where)) << '^' << "---- here\n";
            return qi::fail;
        }
};

template<typename It>
struct annotation_f {
    typedef void result_type;

    annotation_f(It first) : first(first) {}
    It const first;

    template<typename Val, typename First, typename Last>
    void operator()(Val& v, First f, Last l) const {
        std::cerr << "\nannotating " << typeid(v).name() << " '" << std::string(f,l) << "'\n";
        do_annotate(v, f, l, first);
    }
  private:
    void static do_annotate(ast::LocationInfo& li, It f, It l, It first) {
        using std::distance;
        li.line   = get_line(f);
        li.column = get_column(first, f);
        li.length = distance(f, l);
    }
    static void do_annotate(...) { std::cerr << "(not having LocationInfo)\n"; }
};

template<typename Iterator=pos_iterator_t, typename Skipper=qi::space_type>
struct ParseGrammar: public qi::grammar<Iterator, ast::SourceCode(), Skipper>
{
    ParseGrammar(Iterator first) : 
        ParseGrammar::base_type(SourceCode),
        annotate(first)
    {
        using namespace qi;
        KeywordFunction = lit("function");
        KeywordVar      = lit("var");
        SemiColon       = lit(';');

        Identifier      = as_string [ alpha >> *(alnum | char_("_")) ];
        VarAssignment   = KeywordVar > Identifier > '=' > int_ > SemiColon; // note: expectation points
        SourceCode      = KeywordFunction >> Identifier >> '{' >> *VarAssignment >> '}';

        on_error<fail>(VarAssignment, handler(_1, _2, _3, _4));
        on_error<fail>(SourceCode, handler(_1, _2, _3, _4));

        auto set_location_info = annotate(_val, _1, _3);
        on_success(Identifier,    set_location_info);
        on_success(VarAssignment, set_location_info);
        on_success(SourceCode,    set_location_info);

        BOOST_SPIRIT_DEBUG_NODES((KeywordFunction)(KeywordVar)(SemiColon)(Identifier)(VarAssignment)(SourceCode))
    }

    phx::function<error_handler_f> handler;
    phx::function<annotation_f<Iterator>> annotate;

    qi::rule<Iterator, ast::SourceCode(),    Skipper> SourceCode;
    qi::rule<Iterator, ast::VarAssignment(), Skipper> VarAssignment;
    qi::rule<Iterator, ast::Identifier()>             Identifier;
    // no skipper, no attributes:
    qi::rule<Iterator> KeywordFunction, KeywordVar, SemiColon;
};

int main()
{
    std::string const content = "function FuncName_1 {\n var Var_1 = 3;\n var  Var_2 = 4; }";

    pos_iterator_t first(content.begin()), iter = first, last(content.end());
    ParseGrammar<pos_iterator_t> resolver(first);    //  Our parser

    ast::SourceCode program;
    bool ok = phrase_parse(iter,
            last,
            resolver,
            qi::space,
            program);

    std::cout << std::boolalpha;
    std::cout << "ok  : " << ok << std::endl;
    std::cout << "full: " << (iter == last) << std::endl;
    if(ok && iter == last)
    {
        std::cout << "OK: Parsing fully succeeded\n\n";

        std::cout << "Function name: " << program.function.name << " (see L" << program.printLoc() << ")\n";
        for (auto const& va : program.assignments)
            std::cout << "variable " << va.id.name << " assigned value " << va.value << " at L" << va.printLoc() << "\n";
    }
    else
    {
        int line   = get_line(iter);
        int column = get_column(first, iter);
        std::cout << "-------------------------\n";
        std::cout << "ERROR: Parsing failed or not complete\n";
        std::cout << "stopped at: " << line  << ":" << column << "\n";
        std::cout << "remaining: '" << std::string(iter, last) << "'\n";
        std::cout << "-------------------------\n";
    }
    return 0;
}
