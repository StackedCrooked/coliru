#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

int main()
{
    unsigned long long line_cnt = 0 ;
    unsigned long long word_cnt = 0 ;
    unsigned long long byte_cnt = 0 ;

    std::string line ;
    while( std::getline( std::cin, line ) )
    {
        ++line_cnt ;
        byte_cnt += line.size() + 1 ;
        std::istringstream stm(line) ;
        std::string word ;
        while( stm >> word ) ++word_cnt ;
    }
    int width = 8 + ( byte_cnt > 9999999 ? 8 : 0 ) ;
    std::cout << line_cnt << std::setw(width)  << word_cnt << std::setw(width) << byte_cnt << '\n' ;
}
