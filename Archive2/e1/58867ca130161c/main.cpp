// #define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted/struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/spirit/include/qi.hpp>

namespace qi  = boost::spirit::qi;

struct Operation {
    enum Kind { add, multiply } kind;
    double operand;

    friend std::ostream& operator<<(std::ostream& os, Kind k) {
        switch (k) {
            case add:      return os << "--add";
            case multiply: return os << "--multiply";
        };
        return os << "??";
    }
};

BOOST_FUSION_ADAPT_STRUCT(Operation, (Operation::Kind,kind)(double,operand))

template <typename It, typename Skipper = qi::blank_type> 
   struct expression_grammar : qi::grammar<It, std::vector<Operation>(), Skipper> {
       expression_grammar() : expression_grammar::base_type(start) {
           using namespace qi;

           opkinds.add
               ("-a",         Operation::add)
               ("--add",      Operation::add)
               ("-m",         Operation::multiply)
               ("--multiply", Operation::multiply)
               ;

           option = opkinds > eol > double_;

           start  = *(option > eol);

           BOOST_SPIRIT_DEBUG_NODES((start)(option))
       }
     private:
       qi::symbols<char, Operation::Kind> opkinds;
       qi::rule<It, Operation(), Skipper> option;
       qi::rule<It, std::vector<Operation>(), Skipper> start;
   };

int main(int argc, char const** argv) {
    std::stringstream iss;
    if (argc)
        std::copy(argv+1, argv+argc, std::ostream_iterator<const char*>(iss, "\n"));

    typedef boost::spirit::istream_iterator It;
    expression_grammar<It> grammar;

    It first(iss >> std::noskipws), last;
    std::vector<Operation> operations;
    bool ok = qi::phrase_parse(first, last, grammar, qi::blank, operations);

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
