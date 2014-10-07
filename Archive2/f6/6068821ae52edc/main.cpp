#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/spirit/include/support_utree.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/phoenix.hpp>
#include <boost/coroutine/all.hpp>

#include <functional>
#include <iterator>
#include <iostream>
#include <cstddef>
#include <string>

using namespace boost;
using namespace spirit;
using namespace coroutines;
using namespace qi;

/***************************************************************************************/
auto operator "" _k(const char *keyword, size_t)
{
    return string(keyword);
}

template <typename Iterator>
struct PythonGrammar : grammar<Iterator, utree()>
{
    template<typename ...Ts>
    using Rule = rule<Iterator, Ts...>;
    
    template<typename Result, typename ...Ts>
    using LevelRule = Rule<Result(unsigned), Ts...>;

    template<typename Result>
    using SimpleRule = Rule<Result()>;

    // Some of following fields can be replaced by auto deduction
    Rule<utree()> root;

    SimpleRule<std::string> expression;

    LevelRule<utree> statements, function, while_, if_;
    LevelRule<utree::list_type> statement, line_statement, block;
    LevelRule<utree::list_type, locals<unsigned>> compound;

    LevelRule<unsigned> indent_inc;
    LevelRule<void> indent_dec, indent;

    PythonGrammar()
        : PythonGrammar::base_type(root)
    {
        auto lvl = _r1;
        auto space    = char_(' ');
        auto newline = +eol;
        /*******************************************************************************************/        
        root = statements(0u);

        statements     = *line_statement(lvl);
        line_statement = indent(lvl) >> statement(lvl);
        statement      = (expression >> newline) | while_(lvl) | if_(lvl) | function(lvl);
        expression     = *alnum;

        if_        = "if"_k    >> +space >> expression >> block(lvl) >> indent(lvl) >> "else"_k >> block(lvl);
        while_     = "while"_k >> +space >> expression >> block(lvl);
        function   = "def"_k   >> +space >> expression >> '(' >> expression >> ')' >> block(lvl);

        block      = ':' >> ((newline >> compound(lvl)) | (+space >> statement(lvl)));
        compound   = omit[ indent_inc(lvl)[_a = _1] ] >> +line_statement(_a) >> indent_dec(lvl);

        indent_inc = & repeat(lvl + 1, inf)[space][_val = phoenix::size(_1)];
        indent_dec = & repeat(0u     , lvl)[space];
        indent     =   repeat(lvl         )[space];
        /*******************************************************************************************/
    }
};
/***************************************************************************************/
auto test_parse_python = [](const auto &code)
{
    auto first = begin(code),
         last  = end(code) - 1;

    PythonGrammar< decltype(first) > py;
    utree tree;
    bool done = parse(first, last, py, tree);

    using namespace std;
    cout << "Code:" << endl << code << endl;
    if (done && first == last)
        cout << "Succeeded: " << tree << endl;
    else
        cout << "Tail={" << std::string(first, last) << "}" << endl;
    cout << std::string(80, '_') << endl;
};
/***************************************************************************************/
constexpr auto &good_python_code = R"python(
def foo():
    a1

    a2
    if 1:
        b2
        b3
    else:
        b4
        while 4:
            e1
    a2
    a3
    while 2: c1
    a3
)python";
/***************************************************************************************/
constexpr auto &bad_python_code = R"python(
a1
while 2:
    b2
    b3
    while 3:
        c3
  while 1: b4
)python";
/***************************************************************************************/
int main()
{
    test_parse_python(good_python_code);
    test_parse_python(bad_python_code);
}
