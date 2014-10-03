#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/spirit/include/support_utree.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/coroutine/all.hpp>

#include <functional>
#include <iterator>
#include <iostream>
#include <string>
#include <stack>

using namespace boost;
using namespace spirit;
using namespace coroutines;
using namespace qi;

/***************************************************************************************/
template <typename Iterator>
struct PythonGrammar : grammar<Iterator, utree()>
{
    template<typename Result>
    using Rule = rule<Iterator, Result()>;

    // Some of following fields can be replaced by auto deduction
    Rule<utree> statements, function, while_, if_;
    Rule<utree::list_type> statement, block;
    Rule<std::string> expression;

    PythonGrammar()
        : PythonGrammar::base_type(statements)
    {
        auto space = qi::ascii::space;
        /*******************************************************************************************/
        function   = string("def")   >> +space >> expression >> '(' >> expression >> ')' >> block;
        while_     = string("while") >> +space >> expression >> block;
        if_        = string("if")    >> +space >> expression >> block >> string("else") >> block;

        block      = ':' >> ((eol >> '{' >> statements >> '}') | (+space >> statement));
        statement  = (expression >> eol) | while_ | if_ | function;
        expression = *alnum;
        statements = *statement;
        /*******************************************************************************************/
    }
};
/***************************************************************************************/
auto identation_preprocessor = [](auto it, auto &yield)
{
    std::stack<unsigned> levels({0u});
    while(*it)
    {
        auto level = 0u;
        while(*it == ' ')
        {
            ++level;
            ++it;
        }

        if(level > levels.top())
        {
            yield('{');
            levels.push(level);
        }
        else while(level < levels.top())
        {
            yield('}');
            levels.pop();
            if(level > levels.top())
                for_each("<$indentation error$>", std::ref(yield));
        }

        while(*it)
        {
            auto x = *it++;
            yield(x);
            if(x == '\n') break;
        }
    }

    auto n = levels.size();
    while(--n) yield('}');
};
/***************************************************************************************/
auto test_parse_python = [](const auto &code)
{
    coroutine<char>::pull_type coro([&](auto &yield)
    {
        identation_preprocessor(begin(code), yield);
    });
    auto first = make_default_multi_pass(begin(coro)),
         last = make_default_multi_pass(end(coro));

    PythonGrammar< decltype(first) > py;
    utree tree;
    bool done = parse(first, last, py, tree);
    
    using namespace std;

    cout << "Code:" << endl << code << endl;
    
    if (done && first == last)
        cout << "Succeeded: " << tree << endl;
    else
        cout << "Failed at: " << std::string(first, last) << endl;
    cout << std::string(80, '_') << endl;
};
/***************************************************************************************/
constexpr auto &good_python_code = R"python(
def foo():
    a1
    if 1:
        b2
        b3
    else:
        b4
    a2
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
