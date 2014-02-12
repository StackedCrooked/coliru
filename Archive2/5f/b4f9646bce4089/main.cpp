#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int countNum( int n )
{
   return 1 + ( n /= 10 ? countNum( n ) : 0 );
}

int main() {
    std::cout << countNum(0);
}
