#include <iostream>
#include <string>
#include <vector>

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>

namespace lex = boost::spirit::lex;

typedef lex::lexertl::token<char const*> LexToken;
typedef lex::lexertl::actor_lexer<LexToken> LexerType;
typedef boost::iterator_range<char const*> IteratorRange;

enum TokenType {
    IntLiteral = boost::spirit::lex::min_token_id
};

std::string const& ToString(TokenType t) {
    static const std::string tokenTypeNames[] = {
        "int literal",
    };

    return tokenTypeNames[t - boost::spirit::lex::min_token_id];
}

template <typename T>
struct Lexer : boost::spirit::lex::lexer<T> {
    Lexer() {
        this->self.add
            // Literals
            ("[1-9][0-9]*", TokenType::IntLiteral);
    }
};

int main() {
    std::cout << "Boost version: " << BOOST_LIB_VERSION << std::endl;
    std::string input = "33";

    char const* inputIt = input.c_str();
    char const* inputEnd = &input[input.size()];

    Lexer<LexerType> tokens;
    LexerType::iterator_type token = tokens.begin(inputIt, inputEnd);
    LexerType::iterator_type end = tokens.end();

    for (; token->is_valid() && token != end; ++token)
    {
        auto range = boost::get<IteratorRange>(token->value());
        std::cout << ToString(static_cast<TokenType>(token->id())) << " (" << std::string(range.begin(), range.end()) << ')' << std::endl;
    }
}
