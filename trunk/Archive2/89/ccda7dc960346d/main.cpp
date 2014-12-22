#include <iostream>

enum struct C { x = 5 };

enum D { y = 0, x = C::x }; // even integral constant expression must have integral
                            // or unscoped enumeration type, not 'C

int main(){ }