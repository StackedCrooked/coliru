#include <iostream>
#include <memory>
#include <tuple>

struct Token {
    std::string lexeme;
    Token(std::string lex) : lexeme{std::move(lex)} {}
};

struct Node {
Node ( Token & token );
};

int main() {
    std::tuple<std::string,std::string,std::string> tuple{"foo","bar","baz"};
    
    // Code from the question:
    std::string type,rel,pred;
    std::tie( type, rel, pred ) = tuple;
    auto supertype = std::make_shared<Node>( Token( type ) ); // This
    auto predicate = std::make_shared<Node>( Token( pred ) ); // and this
}
