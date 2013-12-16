#include <iostream>

int main( int, char** )
{
    using namespace std;
    
    // Lambdas can take parameters. The parameter list looks just like one
    // you'd put on a regular function. It goes after the two brackets:
    auto fn = []( int val ){ cout << "You passed in: " << val << endl; };
    
    fn( 99 );
    
    // Just like a regular function, this line would fail because it expects
    // a parameter:
    //
    // fn();
    //
    // This one would fail because we passed to many:
    //
    // fn( 9, "Hello!" );
    //
    // This one fails because we pass the wrong types:
    //
    // fn( "Hi" );
    
    
    return 0;
}
