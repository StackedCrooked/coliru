#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <ctime>

struct bunny
{
    bunny() { std::cout << *this << " was born\n" ; }

    bunny( std::string name, int age, std::string clr )
        : name(name), age(age), colour(clr)
    { std::cout << *this << " was born\n" ; }

    ~bunny() noexcept { if( !has_moved_elsewhere ) std::cout << *this << " died\n" ; }

    // bunnies can't be copied
    bunny( const bunny& ) = delete ;
    bunny& operator= ( const bunny& ) = delete ;

    // but thay can be moved
    bunny( bunny&& that ) noexcept
         : name( std::move(that.name) ), age(that.age),
           colour(that.colour), has_moved_elsewhere(that.has_moved_elsewhere)
           { that.has_moved_elsewhere = true ; }

    bunny& operator= ( bunny&& that ) noexcept
    {
        std::swap( name, that.name ) ;
        age = that.age ;
        colour = that.colour ;
        has_moved_elsewhere = that.has_moved_elsewhere ;
        that.has_moved_elsewhere = true ;
        return *this ;
    }

    private:
        static const std::vector<std::string> names ;
        static const std::vector<std::string> colours ;

        std::string name = names[ std::rand() % names.size() ] ;
        int age = std::rand() % 10 ;
        std::string colour = colours[ std::rand() % colours.size() ] ;
        bool has_moved_elsewhere = false ;

    friend std::ostream& operator<< ( std::ostream& stm, const bunny& b )
    { return stm << "bunny{ " << b.name << ", " << b.age << ", " << b.colour << " }" ; }

    friend bool operator< ( const bunny& a, const bunny& b ) { return a.age < b.age ; }
};

const std::vector<std::string> bunny::names =
{
    "Hajra", "Mejra", "Sefika", "Hanifa", "Zulfa", "Wayne Rooney",
    "Cristiano Ronaldo", "Edin Dzeko",  "Robin Van Persie", "Juan Mata",
    "David De Gea", "Luis Nani", "Ryan Giggs", "Paul Scholes", "David Beckham"
};

const std::vector<std::string> bunny::colours =
{
    "white", "brown", "black", "spotted", "agouti", "blue", "cinnamon",
    "lynx", "chinchilla", "sable", "smoke pearl", "fawn", "tan"
};

int main()
{
    std::srand( std::time(nullptr) ) ;

    std::vector<bunny> colony ;

    colony.push_back( bunny( "bugs", 5, "white" ) ) ;
    colony.push_back( bunny( "miyamoto", 7, "dove-grey" ) ) ;
    colony.push_back( bunny( "bre'r", 4, "beige" ) ) ;
    colony.resize(8) ;

    std::sort( std::begin(colony), std::end(colony) ) ;

    std::cout << "---------------------------------------------\n" ;
    for( const bunny& b : colony ) std::cout << b << " is alive\n" ;

    std::cout << "---------------------------------------------\n" ;
}
