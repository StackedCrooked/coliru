//http://stackoverflow.com/questions/21638775/tokenizing-an-arithmetic-expression

#include <iostream>
#include <iterator>
#include <string>
#include <stdexcept>
#include <cctype>
#include <sstream>

struct location {
    unsigned line;
    unsigned col;
    location() :line(1), col(1) {}
};

enum token_type {token_eof, token_double, token_mul, token_div, token_add, token_sub, token_pow, token_oparam, token_cparam};
struct token {
    location loc;
    std::string literal;
    token_type type;
    double value;  

    token() {}
    explicit token(location l) : loc(l), type(token_eof) {}
    explicit token(location l, std::string lit, token_type t) : loc(l), literal(lit), type(t) {}
    explicit token(location l, std::string lit, double v) : loc(l), literal(lit), type(token_double), value(v) {}
};
std::ostream& operator<<(std::ostream& out, const token& t) 
{return out << t.literal;}

struct invalid_character : std::runtime_error {
    invalid_character(location loc, char c) 
        : std::runtime_error("line:"+std::to_string(loc.line)+" col:"+std::to_string(c)+" - invalid character " + std::string(1, c)),
        loc(loc), c(c) 
    {}
    
    location loc;
    char c;
};

struct tokenizer_iterator {
    typedef token value_type;
    typedef token* pointer;
    typedef token& reference;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef std::output_iterator_tag iterator_category;
    
    tokenizer_iterator() : source(nullptr), loc(), cur() {}
    tokenizer_iterator(std::istream& source) :source(&source), loc(), cur() {load();}
    
    const token& operator*() const {return cur;}
    const token* operator->() const {return &cur;}
    tokenizer_iterator& operator++() {load(); return *this;}
    tokenizer_iterator operator++(int) {load(); return *this;}
    friend bool operator==(const tokenizer_iterator& lhs, const tokenizer_iterator& rhs) {return lhs.cur.type==rhs.cur.type;}
    friend bool operator!=(const tokenizer_iterator& lhs, const tokenizer_iterator& rhs) {return lhs.cur.type!=rhs.cur.type;}
private:
    void load();

    std::istream* source;
    location loc;
    token cur;
};

















void tokenizer_iterator::load() {
    if (!*source)
        return;

    char next = source->peek();
    if (next==EOF) {
        cur = token(loc);
        return;        
    }
    while(isspace(next)) {
        if (next=='\n') {
            ++loc.line;
            loc.col = 1;
        } else            
            loc.col += 1;
        next = source->get();
        next = source->peek();
    }
    switch(next) {
    case '+':
        next = source->get();
        loc.col += 1;
        cur = token(loc, "+", token_add);
        return;
    case '-':
        next = source->get();        
        loc.col += 1;
        cur = token(loc, "-", token_sub);
        return;
    case '*':
        next = source->get();
        loc.col += 1;
        cur = token(loc, "*", token_mul);
        return;
    case '/':
        next = source->get();
        loc.col += 1;
        cur = token(loc, "/", token_div);
        return;
    case '^':
        next = source->get();
        loc.col += 1;
        cur = token(loc, "^", token_pow);
        return;
    case '(':
        next = source->get();
        loc.col += 1;
        cur = token(loc, "(", token_oparam);
        return;
    case ')':
        next = source->get();
        loc.col += 1;
        cur = token(loc, ")", token_cparam);
        return;
    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
        {
            std::string num;
            location start = loc;
    
            do {
                num.push_back(next);
                next = source->get();
                loc.col += 1;
                next = source->peek();
            } while(isdigit(next));
            if (next=='.') {
                num.push_back(next);
                next = source->get();
                loc.col += 1;
                next = source->peek();
            }
            while(isdigit(next)) {
                num.push_back(next);
                next = source->get();
                loc.col += 1;
                next = source->peek();
            }             
    
            double value = atof(num.c_str());
            cur = token(start, num, value);
            return;
        }
    default:
        throw invalid_character(loc, next);
    }
}

int main() {
    std::istringstream ss;
    ss.str("3.14 + 3 * (7.7/9.8^32.9  )");
    std::copy(tokenizer_iterator(ss), tokenizer_iterator(), std::ostream_iterator<token>(std::cout, "\n"));
    return 0;
}