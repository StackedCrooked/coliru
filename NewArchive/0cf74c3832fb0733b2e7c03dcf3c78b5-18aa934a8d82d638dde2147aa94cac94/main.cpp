#include <iostream>
#include <thread>

int ParseExpression(lexer);

int ParsePrimaryExpression(lexer l) {
    auto t = l();
    if (t == OpenBracket) {
        auto result = ParseExpression(l);
        t = l();
        if (t != CloseBracket)
            error();
        return result;
    }
    if (t == Number)
        return numfromtoken(t);
    error();
}

int ParseMultiplicativeExpression(lexer l) {
    int i = ParsePrimaryExpression(l);
    auto t = l();
    while(true) {
        if (t == Multiply) {
            int rhs = ParsePrimaryExpression();
            i *= rhs;
            continue;
        }
        if (t == Divide) {
            int rhs = ParsePrimaryExpression();
            i /= rhs;
            continue;
        }
        if (t == Modulo) {
            int rhs = ParsePrimaryExpression();
            i %= rhs;
            continue;
        }
        break;
    }
    return i;
}

// Additive is left-recursive so use a loop.
int ParseAdditiveExpression(lexer l) {
    int i = ParseMultiplicativeExpression(l);
    auto t = l();
    while(true) {
        if (t == Plus) {
            int rhs = ParseMultiplicativeExpression();
            i += rhs;
            continue;
        }
        if (t == Minus) {
            int rhs = ParseMultiplicativeExpression();
            i -= rhs;
            continue;
        }
        break;
    }
    return i;
}

int ParseExpression(lexer l) {
    return ParseAdditiveExpression(l);
}