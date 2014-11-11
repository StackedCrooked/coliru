#include <iostream>

volatile int bar()
{
    return 1;
}

int main()
{
    const int& i = bar();
}
