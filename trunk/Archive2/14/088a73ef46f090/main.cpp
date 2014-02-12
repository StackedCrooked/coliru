#include <iostream>

int main()
{
    struct {int a[10], b;} c;
    c.b = 137;
    
    // This condition is determined by implementation-defined variable alignment...
    if (&c.a[10] == &c.b)
    {
        // ... but if it is true, can I legally access b using:
        c.a[10] = 138;
    }
    
    std::cout << c.b << '\n';
}
