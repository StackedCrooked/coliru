#include <iostream>

int main(int argc, const char * argv[])
{
    float x = 4.2;
    if( x == 4.2)
       std::cout << "oops"; // Not executed !
       
    if( x == 4.2f)
       std::cout << "ok !"; // executed !
    return 0;
}