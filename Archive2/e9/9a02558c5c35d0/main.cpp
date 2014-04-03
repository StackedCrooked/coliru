#include <iostream>

enum MyEnum1 {ZERO = 0, ONE = 1, TWO = 2};
enum MyEnum2 {THREE = 3, FOUR = 4, FIVE = 5};

int blah( MyEnum1 one ){ int i = one; return i; }
int guff( MyEnum2 two ){ int i = two; return i; }

int main()
{   
    int (*pFunc[2]) ( int );
    
    pFunc[0] = blah;
    pFunc[1] = guff;
    
    std::cout << (*pFunc)(ONE) << std::endl;
}
