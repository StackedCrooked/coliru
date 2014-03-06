#include <iostream>
#include <string>

std::string insert_seperator( std::string str, char sep = '=', std::size_t gap = 5 )
{
    std::string result ;
    std::size_t cnt = 0 ;
    for( char c : str )
    {
        if( cnt > 0 && cnt%gap == 0 ) result += sep ;
        result += c ;
        ++cnt ;
    }

    return result ;
}

int main()
{
    const std::string a = "housesinkbuildings" ;
    std::cout << a << ' ' << insert_seperator(a) << '\n' ;

    const std::string b = "housesinkbuildings45" ;
    std::cout << b << ' ' << insert_seperator(b) << '\n' ;
}
