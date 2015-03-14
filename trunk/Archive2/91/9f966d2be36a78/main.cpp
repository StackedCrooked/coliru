#include <iostream>
#include <vector>
#include <tuple>
#include <string>

void foo( const std::vector< std::tuple< int, bool, double, std::string, double > >& tuples )
{
    for( auto& tup : tuples )
    {
        int a ;
        bool b ;
        double c ;
        std::string d ;
        double e ;
        
        // http://en.cppreference.com/w/cpp/utility/tuple/tie
        std::tie( a, b, c, d, e ) = tup ; // unpack the tuple
        std::cout << std::boolalpha << a << ' ' << b << "  " << c << ' ' << d << ' ' << e  ;

        std::cout << ' ' << std::get<0>(tup)
                  << ' ' << std::get<std::string>(tup) << '\n' ; // C++14
    }

}

int main()
{
    std::vector< std::tuple< int, bool, double, std::string, double > > vec ;

    vec.emplace_back( 1, false, 2.3, "abcd", 4.5 ) ;
    vec.emplace_back( 6, true, 77.8, "efgh", 9.1 ) ;
    vec.emplace_back( 2, false, 3.4, "ijkl", 5.6 ) ;
    vec.emplace_back( 7, true, 88.9, "mnop", 0.1 ) ;

    foo(vec) ;
}
