#include <iostream>
#include <string>

int main( int, char** )
{
    using namespace std;
    
    int val1 = 0;
    int val2 = 44;
    int val3 = 6;
    int val4 = 3;
    std::string str = "Hello, person";
    
    // Sometimes, if we have many values to capture, we can go the lazy route
    // and say "capture everything that I reference in the lambda body by
    // value!" We do that by putting an equal sign in the brackets:
    auto cap_val = [=]
    {
        cout << "Capture by value" << endl;
        cout << val1 << endl;
        cout << val2 << endl;
        cout << val3 << endl;
        cout << val4 << endl;
        cout << str << endl;
    };
    
    val1 = 2;
    
    cap_val();
    
    // There's an equivalent for reference. Just use '&' instead of '=':
    auto cap_ref = [&]
    {
        cout << "Capture by reference" << endl;
        cout << val1 << endl;
        cout << val2 << endl;
        cout << val3 << endl;
        cout << val4 << endl;
        cout << str << endl;
    };
    
    val4 = 88;
    
    cap_ref();
    
    // We can mix them. You can specify a default then use the earlier notation
    // to capture in whatever crazy ways you want
    auto cap_mix = [&, val1]
    {
        cout << "Capture by value AND reference" << endl;
        cout << val1 << endl; // <-- This one is a snapshot of the value
        cout << val2 << endl; // These are all references...
        cout << val3 << endl;
        cout << val4 << endl;
        cout << str << endl;
    };
    
    val1 = 35;
    
    cap_mix();
    
    return 0;
}
