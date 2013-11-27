#include <string>
#include <iostream>
#include <vector>
#include <type_traits>

struct Song
{
    Song( const std::string& name, const std::string& by )
        : title(name), artiste(by) { std::cout << "    Song::two arg constructor\n" ; }

    Song( const Song& that ) : title(that.title), artiste(that.artiste)
    { std::cout << "    Song::copy constructor\n" ; }

    Song( Song&& that ) noexcept
        : title( std::move(that.title) ), artiste( std::move(that.artiste) )
    { std::cout << "    Song::move constructor\n" ; }

    ~Song() noexcept { std::cout << "    Song::destructor\n" ; } ;

    Song& operator= ( const Song& that ) = default ;
    Song& operator= ( Song&& that ) noexcept = default ;

    const std::string title ;
    const std::string artiste ;
};

int main()
{
    std::cout << "is_nothrow_move_constructible? " << std::boolalpha
               << std::is_nothrow_move_constructible<Song>::value << '\n' // true
               << "is_nothrow_destructible? " << std::boolalpha
               << std::is_nothrow_destructible<Song>::value << "\n\n" ; // true

    std::vector<Song> favourites ; // empty sequence
    favourites.reserve(5) ; // reserve space for upto 5 songs

    std::cout << "Song autumn(...) ;\n" ;
    Song autumn( "Autumn in New York", "Billie Holiday" ) ; // Song::two arg constructor

    std::cout << "\nfavourites.push_back(autumn) ;\n" ;
    {
        favourites.push_back(autumn) ; // vector makes a copy: Song::copy constructor
    }

    std::cout << "\nfavourites.push_back( Song(...) ) ;\n" ;
    {
        favourites.push_back( Song( "Summertime", "Sarah Vaughan" ) ) ;
    }


    std::cout << "\nfavourites.emplace_back(...) ;\n" ;
    {
        favourites.emplace_back( "It Might as Well Be Spring", "Astrud Gilberto" ) ;
    }

    std::cout << "\nfavourites.reserve(50) ;\n" ;
    {
        favourites.reserve(50) ; // reserve space for upto 50 songs
    }

    std::cout << "\nend of main: autumn, vector destroyed\n" ;
}
