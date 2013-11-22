#include <iostream>

int main()
{
    int i = 1;
label:
    int a;
    std::cout << a << "\n";
    if(a++, i--) goto label;
}
