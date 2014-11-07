#include <string>
#include <vector>
#include <iostream>
#include <sstream>

struct director
{
    director( std::string name = "", int age = 0, std::string country = "" )
        : name(name), age(age), country(country) {}

    std::string name ;
    int age = 0 ;
    std::string country ;
};

std::istream& operator>> ( std::istream& stm, director& dir )
{
    std::string name ;
    int age ;
    std::string country ;
    // read name, read age, throw away the new line, read country
    if( std::getline( stm, name ) && stm >> age && stm.ignore(1000,'\n') && std::getline(stm,country) )
        dir = { name, age, country } ;
    else dir = {} ;

    return stm ;
}

std::ostream& operator<< ( std::ostream& stm, const director& dir )
{ return stm << "name: " << dir.name << "\nage: " << dir.age << "\ncountry: " << dir.country ; }

int main()
{
    std::istringstream file(
                                "John\n"
                                "45\n"
                                "England\n"
                                "Mark\n"
                                "53\n"
                                "Belgium\n"
                           );

    std::vector<director> directors ;

    director d ;
    while( file >> d ) directors.push_back(d) ;

    for( const director& d : directors ) std::cout << d << "\n--------\n" ;
}
