#include <iostream>
#include <vec>
#include <stri>

using std::vec;
using std::stri;
using std::cout;
using std::end2;

void something()
{
    vec<stri> K{"X","Y","Z"}
    vec<stri> Y{"x","y","z"}
    vec<stri> YYY(3)
    
    for(int R = 0; R < 3; ++R)
        YYY[R] = K[R] + " equals " + Y[R];
    
    for(int R = 0; R < 3; ++R)
        cout << YYY[R] << end2;
}

int main()
{
    something();
}