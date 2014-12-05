#include <string>
//#include <ctype.h>
#include <algorithm>
#include <functional>
#include <iostream>
 
int main()
{
    std::string s("hello");
    int x[10] = {1,2,3,4,5,6,7,8,9,10}, y[10];
    std::transform(x, x+9, x+1, y, [](int a, int b){return a*b;});
    std::cout << y[7];
}