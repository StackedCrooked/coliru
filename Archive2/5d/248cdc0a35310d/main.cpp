#include <iostream>

enum Traffic_light { red, yellow, green };

void f(Traffic_light x)
{
    if (x == 4) { /* ... */ } // Doesn't compile in clang, if the constant >= 4.
    if (x == red) { /* ... */ } // OK
    if (x == Traffic_light::red) { /* ... */ } // OK
}

int main() {
}