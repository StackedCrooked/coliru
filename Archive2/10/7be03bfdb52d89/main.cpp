#include <iostream>


template<typename T>
void print_type()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}


#define _(expr, x) expr ; std::cout << #expr << "; // " << #x << "  is "; print_type<decltype((x))>();


int main()
{   
    _( int a = 1         , a );
    _( int& b = a        , b );
    _( const int& c = 3  , c );
    _( int&& d = 4       , d );
    _( int&& e = 5       , std::move(e) );
}
