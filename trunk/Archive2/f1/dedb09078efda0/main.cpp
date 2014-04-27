#include <iostream>

int main () {
    
    struct foo {
        
        int woof () {
            
        }
        
    };
    
    int (foo::* test)();
    // <--- can define one and only one member function
    // So why can't I use types to call a member function, if there's one and only one member function that can match a specific signature?
    int x = foo.*test(); // Doesn't work, test was never initialized -- I get it
    // int y = foo.*( int () ) (); <--- Why doesn't smething like this exist?
    
}