#include <iostream>
#include <string>
#include <cmath>
#include <utility>
#include <vector>
#include <set>

using canvas_type = std::vector<std::string> ;
using point_type = std::pair<double,double> ;
using xy_pos_type = std::pair<int,int> ;

// points that form a hear shape from the paremetic equation
// x = sin(t) * cost(t) * ln (abs(t) )
// y = pow( abs(t), 0.3 ) * sqrt( cos(t) )
// for t in [-1, +1 ]
std::set<point_type> make_heart( double delta = 0.001 )
{
    std::set<point_type> points ;

    for( double t = -1.0 + delta ; t < +1.0 - delta ; t += delta )
    {
        const double x = std::sin(t) * std::cos(t) * std::log( std::abs(t) ) ;
        const double y = std::pow( std::abs(t), 0.3 ) * std::sqrt( std::cos(t) ) ;
        points.emplace(x,y) ;
    }

    return points ;
}

// normalize the x values so that min x == 0
// invert the y values
// scale to integers in an N * N grid
std::set<xy_pos_type> normalize( std::set<point_type> points, std::size_t N )
{
    std::set<xy_pos_type> result ;
    const double minx = points.begin()->first ;

    for( auto& pt : points )
    {
        int ix = std::lround( ( pt.first + ( 0 - minx ) ) * N ) ;
        int iy = std::lround( pt.second * N ) ;
        iy = N - iy - 1 ;
        result.emplace( ix, iy ) ;
    }

    return result ;
}

int main()
{
    constexpr int N = 100 ;

    const auto points = normalize( make_heart(), N ) ;
    
    const std::string blanks( N, ' ' ) ;
    canvas_type canvas( N, blanks ) ;
    for( auto& pt : points ) canvas[pt.second][pt.first] = '*' ;
    
    std::cout << "\n-------------------------------------------------------------------------\n" ;
    for( const std::string& str : canvas )
        if( str != blanks ) std::cout << str << '\n' ;
}
