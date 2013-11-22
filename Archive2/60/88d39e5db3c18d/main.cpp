#include <iostream>
#include <string>
#include <locale>

template< typename C, typename T, typename A >
std::basic_string<C,T,A> trim( const std::basic_string<C,T,A>& str,
                                 const std::locale& loc = std::locale::classic() )
{
    auto begin = str.begin() ; // first non ws from left
    while( begin != str.end() && std::isspace( *begin, loc ) ) ++begin ;

    auto rbegin = str.rbegin() ; // first non ws from right
    while( rbegin != str.rend() && std::isspace( *rbegin, loc ) ) ++rbegin ;

    return { begin, rbegin.base() } ;
}

int main()
{
    const std::string str = "   *abcd efgh ijkl*    " ;
    std::cout << '|' << str << "|\n" ;

    const std::string trimmed = trim(str) ;
    std::cout << '|' << trimmed << "|\n" ;


    const std::wstring wstr = L"   $12345$    " ;
    std::wcout << '|' << wstr << "|\n" ;

    const std::wstring wtrimmed = trim(wstr) ;
    std::wcout << '|' << wtrimmed << "|\n" ;
}
