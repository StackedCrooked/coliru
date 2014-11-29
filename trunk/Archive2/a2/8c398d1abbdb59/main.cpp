#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

struct point
{
    std::string name ;
    int x ;
    int y ;

    int square_of_radius() const { return x*x + y*y ; }
};

int main()
{
    // http://www.mochima.com/tutorials/vectors.html
    std::vector<point> seq = { { "B", 6, 8 }, { "A", 9, 12 }, { "D", 3, 4 } } ;

    // http://en.cppreference.com/w/cpp/algorithm/sort
    // https://solarianprogrammer.com/2011/11/01/cpp-11-lambda-tutorial/
    std::sort( seq.begin(), seq.end(),
               [] ( const point& a, const point& b ) { return a.square_of_radius() < b.square_of_radius() ; } );

    // http://www.stroustrup.com/C++11FAQ.html#for
    for( const point& pt : seq ) std::cout << pt.name << ' ' << pt.x << ' ' << pt.y << '\n' ;
}
