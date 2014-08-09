#include <vector>
#include <string>
#include <iostream>

struct A
{
    // see: http://www.stroustrup.com/C++11FAQ.html#uniform-init
    // see: http://www.stroustrup.com/C++11FAQ.html#member-init
    std::vector<std::string> activities {1} ; // vector with initial size 1 (contains one empty string)

    // see: http://www.stroustrup.com/C++11FAQ.html#init-list
    std::vector<std::string> animals { "panda", "lynx", "ibex" } ; // vector with 3 animals (strings)

    std::vector<std::string> colours ;

    // see: http://www.stroustrup.com/C++11FAQ.html#uniform-init
    A() : colours { "cyan", "magenta", "yellow", "black" } {} // colours initialised with 4 colours (strings)
};

template < typename SEQUENCE >
void print( const SEQUENCE& seq, const char* name = "", std::ostream& stm = std::cout )
{
    stm << name << ":  [ " ;

    // see: http://www.stroustrup.com/C++11FAQ.html#auto
    // see: http://www.stroustrup.com/C++11FAQ.html#for
    for( const auto& v : seq ) stm << '"' << v << "\" " ;

    stm << "]\n" ;
}

int main()
{
    A a ;
    print( a.activities, "activities" ) ; // activities:  [ "" ]
    print( a.animals, "animals" ) ; // animals:  [ "panda" "lynx" "ibex" ]
    print( a.colours, "colours" ) ; // colours: [ "cyan" "magenta" "yellow" "black" ]
}
