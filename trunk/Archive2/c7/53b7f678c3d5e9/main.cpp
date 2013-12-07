#include <iostream>
#include <string>

int main( int, char** )
{
    using namespace std;
    
    // "Closure" objects aren't just functions. They're actually objects with
    // data in them! The two braces aren't just there for looks. They're called
    // the "capture" specification, and tell the compiler to grab items from
    // the enclosing scope and save their values into the resulting closure.
    // The closure is inherently a "snapshot" of its captured values at the
    // time that execution passed over the declaration of the closure.
    
    int myvalue = 99;
    
    auto fn = [myvalue]
    {
        cout << myvalue << endl;
    };
    
    myvalue = 5;
    
    // What will this print?
    fn();
    
    return 0;
}
