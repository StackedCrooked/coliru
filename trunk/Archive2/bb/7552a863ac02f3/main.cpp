#include <type_traits>
#include <iostream>

using namespace std;

float f(float a)
{
    return a*a;
}

using functionPtr1 = std::add_pointer<float(float)>::type; 

using functionPtr2 = decltype(&f);

int main()
{
    
    functionPtr1 p1 = f;
    functionPtr2 p2 = f;
    
    cout << p1(3) << endl;
    cout << p2(3) << endl;
    
    return 0;
    
}
