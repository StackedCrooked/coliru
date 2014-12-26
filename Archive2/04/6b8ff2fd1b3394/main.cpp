#include <iostream>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>

typedef std::pair<float,float> position ;

float square_of_distance_from_origin0( float x, float y ) // origin0 is (0.0,0.0)
{ return x*x + y*y ; }

float square_of_distance_from_origin0( position p ) // origin0 is (0.0,0.0)
{ return square_of_distance_from_origin0( p.first, p.second ) ; }

float square_of_distance_from_origin( position p, position origin )
{
    const float  xrange = p.first - origin.first ;
    const float  yrange = p.second - origin.second ;

    return xrange*xrange + yrange*yrange ;
}

/// random direction: delta -1, 0, +1
int random_delta()
{
    static const int N = 3 ;
    static const int delta[N] = { -1, 0, +1 } ;
    return delta[ std::rand() % N ] ;
}

/// Select coordinate change based on random direction
position next_position( position p )
{ return position( p.first + random_delta(), p.second + random_delta() ) ; }

/// Select coordinate change based on random direction
/// such that distance from (0.0,0.0) is not less then current distance from (0.0,0.0)
position next_away_position( position p )
{
    const float old_dist = square_of_distance_from_origin0(p) ;
    while(true)
    {
        position next( p.first + random_delta(), p.second + random_delta() ) ;
        if( square_of_distance_from_origin0(next) >= old_dist ) return next ;
    }
}

/// Select coordinate change based on random direction
/// such that distance from position from is not less then current distance from position from
position next_away_position( position p, position from )
{
    // transform coordinate system such that position from becomes position(0,0)
    p.first -= from.first ;
    p.second -= from.second ;

    // generate next away_position
    position next = next_away_position(p) ;

    // transform coordinate system back
    next.first += from.first ;
    next.second += from.second ;

    return next ;
}

position random_walk_away( position origin, float square_of_max_distance )
{
    position pos = origin ;
    std::cout << std::fixed << std::setprecision(1) << std::showpos
              << '[' << pos.first << ',' << pos.second << "] (origin)\n" ;
    int n = 0 ;
    do
    {
        pos = next_away_position( pos, origin ) ;
        std::cout << '[' << pos.first << ',' << pos.second << "] " ;
        if( ++n == 8 ) { std::cout << '\n' ; n = 0 ; }
    }
    while( square_of_distance_from_origin(pos,origin) < square_of_max_distance ) ;

    return pos ;
}

int main()
{
    const float max_distance = 10.0f;
    const float square_of_max_distance = max_distance*max_distance ;
    std::srand( std::time(0) );

    const position test[] = { position(0.0,0.0), position(3.0,5.0), position( -3.0, 5.0 ), position( -3.0, -5.0 ) } ;
    for( std::size_t i = 0 ; i < sizeof(test) / sizeof( test[0] ) ; ++i )
    {
        const position p = random_walk_away( test[i], square_of_max_distance ) ;
        std::cout << "\n[" << p.first << ',' << p.second << "] (final)\n\n" ; ;
    }
}
