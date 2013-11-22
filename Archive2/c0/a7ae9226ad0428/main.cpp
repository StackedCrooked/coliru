#include <vector>

#define NOP return {};

/// stubs
namespace qi { 
    template <typename...> struct rule { template<typename...T> rule(T&&...){} operator int(){NOP} }; 
    struct space_type { int operator*(){NOP} } int_;
    space_type lit(const char*) {NOP}

    template <typename T, typename U> int operator<<(T&&,U&&) {NOP}
}

/// demo
template <typename It>
struct mygrammar {
    qi::rule<It, int()>                              value  = qi::int_;
    qi::rule<It, std::vector<int>(), qi::space_type> values = value;
    qi::rule<It, std::vector<int>(), qi::space_type> start  = qi::lit("ints") << '{' << values << '}'; 
};

/// this could be a template variable in c++1y
static mygrammar<const char*>                       char_grammar;
static mygrammar<std::vector<char>::const_iterator> cvec_grammar;

int main() {
}
