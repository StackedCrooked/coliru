#include <iostream>
int f() { return 42; }
int main()
{
    int n = 1;
    int* pn = &n;
 
    int& r = *pn;  // lvalue can be bound to a reference
    int m = *pn;   // indirection + lvalue-to-rvalue conversion
 
    int (*fp)() = &f;
    int (&fr)() = *fp; // function lvalue can be bound to a reference 
}