#include <iostream>
#include <string>

int main( int, char** )
{
    using namespace std;
    
    // Lambda return types are "deduced", meaning the compiler infers the type
    // that you want to return from the lambda. It infers based on the types
    // attached to your "return" statements.
    auto fn = []{ return 0; }; // <-- Return type will be "int"
    
    // But there's a problem. If the lambda has multiple return types that don't
    // return the _exact_ same type, deduction will fail and code will not
    // compile. This lambda is ill-formed because it returns two different types:
    
//    auto fn = []( bool val )
//    {
//        if ( val ) return "hi"; // <-- Return const char*
//        else return std::string( "Hello" ); // <-- Return std::string
//    };

    // Even though const char* can be implicitly converted to std::string,
    // the compiler will not automatically do that for us. In this case,
    // we must specify the return type explicitly using "arrow" syntax.
    // We place an arrow pointing at the return type after the parameter list,
    // or the two brackets, if we take no parameters.
    auto fn1 = []( bool val ) -> std::string
    {
        if ( val ) return "Hello!"; // <-- A std::string is constructed for us
        else return std::string( "Howdy" );
    };
    
    cout << fn1( true ) << endl;
    cout << fn1( false ) << endl;
    
    return fn(); // <-- Return 0!
}
