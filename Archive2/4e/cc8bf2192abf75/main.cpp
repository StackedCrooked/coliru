#include <iostream>
void one ( ) { std::cout << "Hello world.\n"; }
int two ( ) { return one ( ); }
int main ( ) { two ( ); }