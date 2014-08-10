#include <iostream>

int main(int argc, const char * argv[])
{
    float x = 4.2;
    if( x == 4.2)
       std::cout << "oops"; // Not executed !
    return 0;
}