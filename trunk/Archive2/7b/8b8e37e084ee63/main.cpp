#include <iostream>
// color may be red (value 0), yellow (value 1), green (value 20), or blue (value 21)
enum color {
    red,
    yellow,
    green = 20,
    blue
};
// altitude may be altitude::high or altitude::low
enum class altitude : char { 
     high='h',
     low='l', // C++11 allows the extra comma
}; 
// the constant d is 0, the constant e is 1, the constant f is 3
enum { d, e, f=e+2 };
int main()
{
    color col = red;
    altitude a;
    a = altitude::low;
 
    std::cout << "red = " << col << " blue = " << blue << '\n'
              << "a = " << static_cast<char>(a) << '\n'
              << "f = " << f << '\n';
}