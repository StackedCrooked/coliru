#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>

using namespace std;

int main()
{
    auto smartPointer = make_shared< vector< string > >();
    smartPointer->push_back( "Bla" );
    smartPointer->push_back( "Blubb" );   
    smartPointer->push_back( "Plopp" );
    
    for( auto element : *smartPointer )
        cout << element << endl;
}
