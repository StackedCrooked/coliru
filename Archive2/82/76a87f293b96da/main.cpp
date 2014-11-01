auto f = [] (bool c1, bool c2) {
    if (c1) return 1;
    if (c2) return 2;
    else    return 3;
};

#include <iostream>

int main()
{
    int a = f(true, false);
    int b = f(false, true);
    int c = f(false, false);
    
    std::cout << a << " " << b << " " << c << std::endl;
}