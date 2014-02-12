#include <iostream>
#include <cmath>

template <typename T, typename U>
T xround(U val) {
    T result;
    if (val >= 0)
        result = (T)(floor(val + (T)(.5)));
    else
        result = (T)(ceil( val - (T)(.5)));
    return result;
}

int main()
{
    int a = xround<int>(5.5); // = 6
    std::cout << a << "\n";       
}    
