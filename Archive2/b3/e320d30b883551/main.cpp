#include <iostream>

template <typename Func>
void call_function( const Func& func )
{
    func();
}

int main( int, char** )
{
    using namespace std;
    
    // We can omit creating our own closure and just pass the lambda directly:
    call_function( []{ cout << "You called the lambda function" << endl; } );
    
    return 0;
}
