#include <iostream>

void foo()
{
    int i = 0;
    int j = -i;

    if (!(i >= 0) || !(j >= 0))
        return;

    std::cout << "Worked";
}

int main()
{
    foo();    
}