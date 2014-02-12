#include <iostream>
#include <string>
#include <stack>

int main()
{
    std::stack<std::string> stk ;

    std::string str ;
    char c ;

    while( std::cin.get(c) ) // read char by char
    {
        if( std::isspace(c) ) // if it is a whitespace
        {
            if( !str.empty() ) stk.push(str) ; // end of current string, push it
            str.clear() ; // start afresh with an empty new string

            if( c == '\n' ) break ; // newline, come out of the loop
        }

        else str += c ; // not whitespace, append to current string
    }

    while( !stk.empty() )
    {
        std::cout << stk.top() << ' ' ;
        stk.pop() ;
    }
    std::cout << '\n' ;
}
