#include <iostream>
#include <sstream>
#include <string>

int main()
{
    std::istringstream file // std::ifstream file( "teams.csv" ) ;
    (
         "id,name\n"
         "501,Abilene Chr\n"
         "502,Air Force\n"
         "503,Akron\n"
         "504,Alabama\n"
    );

    file.ignore( 10000, '\n' ) ; // throw away the first line

    int id ;
    char comma ;
    std::string name ;
    int line_number = 0 ;

    while( file >> id >> comma && std::getline( file, name ) )
    {
        std::cout << ++line_number << ". id: " << id << "  name: " << name << '\n' ;
    }
}
