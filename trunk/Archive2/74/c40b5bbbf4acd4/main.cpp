#include <iostream>
#include <iomanip>

template<class T>
T Add(T a,T b){return a+b;}

int main()
{
   std::cout << std::fixed /* fixed point notation */ << std::setprecision(20) // with 20 digits after the decimal point
             << Add<long double>(-5.553892398912181215,8.238822124218157451258) << '\n' ;
}
