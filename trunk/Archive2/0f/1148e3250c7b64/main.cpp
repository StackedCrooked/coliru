#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

// ignores empty lines, and lines containg only comments or white space
// ignores lines containg only '{' or '}' other than spaces or a trailing comment

// does not take care of c-style /* .... */ comments
// does not take care of digraphs and trigraphs
// does not take care of compile-time optioning (#ifdef)
// does not count lines in included files

int main() // filter; reads from stdin and writes to stdout
{
    int line_cnt = 0 ;
    
    {{{   }}} // hello world!
    
    { // hello
    
    } // world
    
    /* this line is counted
       and this one too */
       
    ??< ??> // this too is counted
    
    #ifdef not_used // counted
        int x = 56 ; // counted
    #endif // not_used (counted)   

    std::string line ;
    while( std::getline( std::cin, line ) )
    {
        static const auto not_space = [] ( char c ) { return std::isspace(c) == 0 ; } ;
        
        // skip over leading white space
        auto iter = std::find_if( line.begin(), line.end(), not_space ) ;
        
        // take care of only '{' or '}'
        while( iter != line.end() && ( *iter == '{' || *iter == '}' || std::isspace(*iter) ) ) ++iter ;
        
        // not empty, and not a line with only a comment
        if( std::search_n( iter, line.end(), 2, '/' ) != iter )
        {
            ++line_cnt ;
            std::cout << line_cnt << ".\t" << line << '\n' ;
        }
    }

    // comment only line

    std::cout << "\n--------------\nline count: " << line_cnt << '\n' ;
}
