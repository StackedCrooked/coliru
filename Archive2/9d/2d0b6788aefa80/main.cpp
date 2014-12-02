#include <iostream>
#include <string>
#include <algorithm>
using namespace std ;

bool myuniq( const string& s )
{
    string temp = s;

    sort( temp.begin(), temp.end() );
    auto uniq = unique( temp.begin(), temp.end() );

    if( uniq == temp.end() )
        {
            cout << "string is unique";
            return true ;
        }

    else
        {
            cout << "string is not unique";
            return false ;
        }
}
