#include <iostream>
#include <string>
#include <cmath>
#include <utility>
#include <vector>
#include <set>

using canvas_type = std::vector<std::string> ;
using point_type = std::pair<double,double> ;
using xy_pos_type = std::pair<int,int> ;

// determine the points that form a heart shape 
// for instance: from the paremetic equation
//               x = sin(t) * cost(t) * ln (abs(t) )
//               y = pow( abs(t), 0.3 ) * sqrt( cos(t) )
//               for t in [-1, +1 ]
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
// scale to integers in an N * N grid
// invert the y values (in our grid, y increases downwards)
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
    
    // get the normalized x, y co-ordinates
    const auto points = normalize( make_heart(), N ) ;
    
    // create a grid filled with spaces
    const std::string blanks( N, ' ' ) ;
    canvas_type canvas( N, blanks ) ;
    
    // place a * at each point that is a part of the curve 
    for( auto& pt : points ) canvas[pt.second][pt.first] = '*' ;
    
    // print the grid
    std::cout << "Heart:\n" ;
    for( const std::string& str : canvas )
        if( str != blanks ) std::cout << str << '\n' ;
}
