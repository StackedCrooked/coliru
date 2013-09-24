#include <iostream>
using std::cout;
using std::endl;

// used as conversion
inline constexpr long double operator"" _deg ( long double deg )
{
    return deg*3.141592/180;
}
int main()
{

    double x = 90.0_deg; // x = 1.570796
    
    cout << x << endl;
}