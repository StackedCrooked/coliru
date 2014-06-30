#include <iostream>

const int MAX_ELEMENT = 10;

int array[ MAX_ELEMENT ];
unsigned index_ = 0;

void add ( int i ) {
    array[ index_ ] = i;
    index_++;
}

void remove ( int i ) {
    // TODO
}

int main() {
    std::cout << "Before: ";
    for( int i : array )
        std::cout << i << " ";
        
    add( 10 );
    add( 256 );
    add( 312 );
    
    std::cout << '\n';
    
    std::cout << "After: ";
    for( int i : array )
        std::cout << i << " ";
}