#include <iostream>
#include <stack>
#include <math.h>

unsigned char getPriority( char c )
{
    switch ( c )
    {
        case '+':
        case '-':
            return 0;
        case '*':
        case '/':
            return 1;
        case '^':
            return 2;
    }
    
    return 0xFF;
}


bool isDigit( char c )
{
    return c >= '0' && c <= '9';
}


int main()
{    
    std::string expr = "0-1+2*3^4";
    std::stack<char> operators;
    std::stack<double> operands;
    
    auto process = [&]()
    {
        double res = 0.0;
        double op2 = operands.top(); operands.pop();
        double op1 = operands.top(); operands.pop();
        switch( operators.top() )
        {
            case '+':
                res = op1 + op2; break;
            case '-':
                res = op1 - op2; break;
            case '*':
                res = op1 * op2; break;
            case '/':
                res = op1 / op2; break;
            case '^':
                res = exp( op2 * log(op1) ); break;
        }
        operands.push( res );
        operators.pop();
    };
    
    if ( !expr.empty() )
    {
        for ( char c : expr )
        {
            if ( isDigit(c) )
                operands.push( c - '0' );
            else
            {
                if ( !operators.empty() && (getPriority(operators.top()) >= getPriority(c)) )
                    process();
                operators.push( c );
            }
        }
    
        while( !operators.empty() )
            process();
    }
    
    std::cout << operands.top();
}
