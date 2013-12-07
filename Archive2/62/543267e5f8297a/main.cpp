#include <iostream>

template <typename Func>
void call_function( const Func& func )
{
    func();
}

int main( int, char** )
{
    using namespace std;
    
    // The actual 'type' of the closure object is hidden and a compiler detail.
    // We aren't supposed to know what the type actually is, and we can't
    // declare a closure type. In order to generate a closure, we need to
    // deduce the type using the 'auto' keyword in place for the type.
    auto fn = []
    {
        cout << "You called the lambda function!" << endl;
    };
    
    // Using templates, the compiler can also deduce the type for us.
    // We don't call the closure, just pass it by reference. The call_function
    // template will actually call it.
    call_function( fn );
    
    return 0;
}
