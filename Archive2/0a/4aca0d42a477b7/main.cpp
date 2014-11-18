//#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted/struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/spirit/include/qi.hpp>

namespace qi  = boost::spirit::qi;

struct Operation {
    enum Kind { add, multiply } kind;
    double operand;

    friend std::ostream& operator<<(std::ostream& os, Kind k) {
        switch (k) {
            case add:      return os << "add";
            case multiply: return os << "multiply";
        };
        return os << "??";
    }
};

BOOST_FUSION_ADAPT_STRUCT(Operation, (Operation::Kind,kind)(double,operand))

template <typename It, typename Skipper = qi::space_type> 
   struct expression_grammar : qi::grammar<It, std::vector<Operation>(), Skipper> {
       expression_grammar() : expression_grammar::base_type(start) {
           using namespace qi;

           opkinds.add
               ("add",      Operation::add)
               ("multiply", Operation::multiply)
               ;

           option = opkinds >> double_;

           start  = *(option >> ';');

           BOOST_SPIRIT_DEBUG_NODES((start)(option))
       }
     private:
       qi::symbols<char, Operation::Kind> opkinds;
       qi::rule<It, Operation(), Skipper> option;
       qi::rule<It, std::vector<Operation>(), Skipper> start;
   };

int main(int argc, char const** argv) {
    assert(argc>1);
    std::string const expression(argv[1]);

    typedef std::string::const_iterator It;
    expression_grammar<It> grammar;

    It first(expression.begin()), last(expression.end());
    std::vector<Operation> operations;
    bool ok = qi::phrase_parse(first, last, grammar, qi::space, operations);

    if (ok)
    {
        std::cout << "Parse success\n";
        for (auto const& op : operations)
            std::cout << boost::fusion::as_vector(op) << "\n";
    } else
        std::cout << "Parse failed\n";

    if (first!=last)
       std::cout << "Remaining input: '" << std::string(first,last) << "'\n";
}
