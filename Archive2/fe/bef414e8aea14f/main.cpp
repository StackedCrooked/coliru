#include <iostream>
#include <string>

int main( int, char** )
{
    using namespace std;
    
    int my_variable = 19;
    
    // There are two types of capture. Capture by value and capture by 
    // reference. Capture by value looks like just putting the variable name
    // write in the two brackets.
    auto cap_value = [my_variable]{ cout << my_variable << endl; };
    
    my_variable = 99;
    
    // Capture by reference is similar, just append '&' to the capture name. In
    // this case, a reference to the capture variable is stored, so the lambda
    // will receive updates on the captured value.
    auto cap_ref = [&my_variable]{ cout << my_variable << endl; };
    
    my_variable = 6;
    
    // What do these print?
    cap_value();
    cap_ref();
    
    return 0;
}
