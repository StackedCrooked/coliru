#include <iostream>

int main () {
    
    struct foo {
        
        int woof () {
            return 0;
        }
        
    };
    foo f;
    int (foo::* test)() = &foo::woof;
    // <--- can define one and only one member function
    // So why can't I use types to call a member function, if there's one and only one member function that can match a specific signature?
    int x = (f.*test)(); //This works, sure
    // int y = foo.*( int () ) (); <--- Why doesn't smething like this exist? It can ONLY point to one member function!
    
}