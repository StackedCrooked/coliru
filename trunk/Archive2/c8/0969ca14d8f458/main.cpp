#include <iostream>
#include <sstream>
#include <cassert>

void foo ( std::ostream& output ) {
     // Format specifier: changes integers to be written as 0xn..., where n.. is the hex value
     output << std::hex;
     output << 21 << " | " << 24 << std::endl;
}

int main () {
     // Need to output some decimalhere
     std::cout << "Decimal Number: " << 8181 << '\n';
     foo( std::cout );
     // Alright, back to decimal!
     std::cout << "Another Decimal Number: " << 9292 << '\n';
}