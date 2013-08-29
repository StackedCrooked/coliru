#include <vector>
#include <string>
#include <iostream>

using namespace std;

void
print_strings
    ( const vector<string> & v )
{
    unsigned int i = 1;
    for ( const auto & s : v )
        cout << "#" << i++ << "\t: \"" << s << "\"" << endl;
    return;
}

int
main
    ( void )
{
    string base( "hello, this is an example string, I like icescreams" );

    /* Vector to populate with strings */
    vector<string> v;

    /* 1: a copy of 'base' */
    v.emplace_back( base );
    /* 2: a copy of 'base' using iterators */
    v.emplace_back( base.begin() , base.end() );
    /* 3: a string that I think _should_ move from 'base' */

    std::cout << base << '\n';

    v.emplace_back( std::move(base) );

    print_strings( v );
    std::cout << "base: " << base << "/base\n";
    return 0;
}

