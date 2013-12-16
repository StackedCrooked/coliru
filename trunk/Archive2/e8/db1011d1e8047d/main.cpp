#include <iostream>
#include <iterator>
#include <sstream>

int main()
{
    {
        std::istringstream stm( "0 1 2 3 4 5 6 7 8 9" ) ;

        // istream iterator iterating over objects of type int
        // use defaults for the remaining three template parameters
        std::istream_iterator<int> iter(stm), end ;
        for( ; iter != end ; ++iter ) std::cout << *iter << ' ' ;
        std::cout << '\n' ;
    }

    {
        // istream iterator iterating over objects of type int
        // the character type of the stream is wchar_t
        // use defaults for the remaining two template parameters
        std::wistringstream stm( L"10 11 12 13 14 15 16 17 18 19" ) ;
        std::istream_iterator<int,wchar_t> iter(stm), end ;
        for( ; iter != end ; ++iter ) std::wcout << *iter << L' ' ;
        std::wcout << L'\n' ;
    }
}
