#include <iostream>

void foo( int v ) { std::cout << v << " "; }

[[deprecated("foo with float is deprecated")]]
void foo( float v ) { std::cout << v << " "; }

[[deprecated("you should not use counter anymore")]]
int counter {};

int main() {
  foo( ++counter );
  foo( 3.14f );
}
