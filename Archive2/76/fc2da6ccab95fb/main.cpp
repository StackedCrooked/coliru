#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
void moveParticles( std::vector< int >& particles, int step )
{
    std::for_each( std::begin( particles ), std::end( particles ), [&step]( int& particle ) { particle += step; } );
}
void filterParticles( std::vector< int >& particles, int rightBound )
{
    particles.erase( std::remove_if( std::begin( particles ), 
                                     std::end( particles ), 
                                     [&rightBound]( const int& particle ) { 
                                         return particle < 0 || particle >= rightBound; } ) );
}

std::string printParticles( const std::vector< int >& left, const std::vector< int >& right, std::size_t length )
{
    std::string result('.', length);
    for ( char idx: left )
        result[idx] = 'X';
    for ( char idx: right )
        result[idx] = 'X';
    return result;
}
std::vector< std::string > generateAnimation( const std::string& in, std::size_t speed )
{
    std::vector< int > left;
    std::vector< int > right;
    std::size_t index = 0;
    for ( char ch: in )
    {
        if ( ch == 'R' )
            right.push_back( index );
        else if ( ch == 'L' )
            left.push_back( index );
        index += 1;
    }
    
    
    std::vector< std::string > result;
    while ( !left.empty() && !right.empty() )
    {
        moveParticles( left, -1 * speed );
        moveParticles( right, speed );
        filterParticles( left, in.size() );
        filterParticles( right, in.size() );
        
        result.push_back( printParticles( left, right, in.size() ) );
    }
    return result;
}


int main()
{
    const std::string in = "RRR............L.R........LLL...R.LL";
    generateAnimation( in, 1 );
}