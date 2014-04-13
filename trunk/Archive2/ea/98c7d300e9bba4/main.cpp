#include <iostream>
#include <string>
#include <list>
#include <algorithm>

struct name
{
    std::string firstName;
    std::string middleName;
    std::string lastName;

    name(std::string a, std::string b, std::string c)
        : firstName(a), middleName(b), lastName(c) {}

    void print() const
    { std::cout << firstName << ", " << middleName << ", " << lastName << '\n' ; }
};

//int _tmain(int argc, _TCHAR* argv[])
int main()
{
    // http://www.stroustrup.com/C++11FAQ.html#uniform-init
    // http://www.stroustrup.com/C++11FAQ.html#init-list
    std::list<name> name_list { { "john", "T", "Smith" }, { "Derek", "Charles", "Mito" } } ;

    // http://www.cplusplus.com/reference/list/list/emplace_back/
    name_list.emplace_back( "Alice", "In", "Wonderland" );
    name_list.emplace_back( "Roberto", "Alonze", "Morris" );
    name_list.emplace_back( "Xiang", "chi", "Fu" );

    // http://www.cplusplus.com/reference/list/list/sort/
    name_list.sort( []( const name &a, const name &b ) { return a.lastName < b.lastName; } );

    std::cout << "Name list by last name\n-----------------\n";

    // http://www.stroustrup.com/C++11FAQ.html#for
    for( const name& n : name_list ) n.print() ;

    std::cout << "\n\nhit enter to exit ";
    std::cin.get() ;
}
