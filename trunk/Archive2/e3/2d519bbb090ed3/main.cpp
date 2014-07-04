#include <iostream>
#include <vector>
#include <functional>

struct room
{
     room( std::size_t f = 0, std::size_t n = 0, bool occ = false )
          : floor(f), number(n), occupied(occ) {}

     std::size_t floor ; // floor numbers start at 0
     std::size_t number ; // room numbers start at 0, 0 == 'A' 
     bool occupied = false ;
     // ...
};

std::ostream& operator<< ( std::ostream& stm, const room& r )
{
    stm << r.floor ;

    static constexpr char room_id[] = "ABCDEFGHIJKLMNPQRSTUVWXYZ" ;
    if( r.number < ( sizeof(room_id) - 1 ) ) stm << room_id[r.number] ;
    else stm << '-' << r.number ;

    if(r.occupied) stm << "(occupied)" ;

    return stm ;
}

struct building
{
    building( std::size_t floors, std::size_t rooms_per_floor )
                        : rooms( floors, std::vector<room>(rooms_per_floor) )
    {
        for( std::size_t f = 0 ; f < floors ; ++f )
            for( std::size_t r = 0 ; r < rooms_per_floor ; ++r ) rooms[f][r] = { f, r } ;
    }

    std::vector<room>& rooms_in_floor( std::size_t f ) { return rooms.at(f) ; }

    const std::vector< std::reference_wrapper<room> > room_across_floors( std::size_t r )
    {
        std::vector< std::reference_wrapper<room> > result ;
        for( auto& v : rooms ) result.push_back( std::ref( v.at(r) ) ) ;
        return result ;
    }

    private: std::vector< std::vector<room> > rooms ;
};

int main()
{
    building b( 8, 17 ) ;
    b.rooms_in_floor(2)[5].occupied = true ;
    b.rooms_in_floor(6)[5].occupied = true ;

    for( auto& r : b.rooms_in_floor(2) ) std::cout << r << ' ' ;
    std::cout << '\n' ;

    for( auto& r : b.room_across_floors(5) ) std::cout << r << ' ' ;
    std::cout << '\n' ;
}
